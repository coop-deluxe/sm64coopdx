#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "pc/thread.h"
#include "pc/platform.h"
#include "pc/configfile.h"
#include "pc/debuglog.h"
#include "pc/utils/misc.h"
#include "pc/utils/md5.h"
#include "pc/fs/fs.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"
#include "pc/mods/mod_cache.h"
#include "pc/mods/mod_fastdl.h"
#include "pc/djui/djui.h"
#include "pc/djui/djui_language.h"
#include "pc/djui/djui_panel.h"
#include "pc/djui/djui_panel_menu.h"
#include "pc/djui/djui_panel_join_message.h"
#include "pc/lua/utils/smlua_misc_utils.h"
#include "pc/network/network.h"
#include "pc/network/packets/packet.h"

#if defined(_WIN32)
#include <windows.h>
#include <wininet.h>
#else
#include <curl/curl.h>
#endif

#define FASTDL_HTTP_BUFFER       (16 * 1024)
#define FASTDL_TIMEOUT_MS        5000

enum FastDlState {
    FDLS_IDLE,
    FDLS_POPUP,
    FDLS_DOWNLOADING,
};

enum FastDlJobResult {
    FDR_PENDING = 0,
    FDR_OK,
    FDR_FAIL,
};

enum FastDlFetchResult {
    FETCH_OK = 0,
    FETCH_FILE_FAILED, // file-level problems (bad status/hash/size) fall back per file
    FETCH_SERVER_FAILED, // server-level problems (not started, wrong addr, dropped, etc.) abort FastDL and go back to in-game path entirely
};

struct FastDlJob {
    // filled by the main thread
    u16 modIndex;
    u16 fileIndex;
    u64 size;
    u8 dataHash[16];
    char* url;
    char* destPath;
    // written by the worker, read by the main thread after ctx->done
    volatile enum FastDlJobResult result;
};

struct FastDlCtx {
    u32 generation;
    struct FastDlJob* jobs;
    u32 jobCount;
    f32 startTime;
    volatile u64 totalBytes;
    volatile u64 doneBytes;
    volatile u32 jobsSucceeded;
    volatile bool unreachable;
    volatile bool aborted;     // set by the main thread to stop the worker
    volatile bool done;        // set by the worker as its very last write
};

static char sFastDlUrl[FASTDL_URL_MAX] = { 0 };
static enum FastDlState sFastDlState = FDLS_IDLE;
static struct FastDlCtx* sFastDlCtx = NULL;
static struct FastDlCtx* sFastDlPendingFree = NULL; // aborted transfer awaiting its worker's done signal
static volatile u32 sFastDlGeneration = 0;
static struct ThreadHandle sFastDlThread = { 0 };

static bool sFastDlAnswerYes = false;

// sticky answer for "let me choose": ask once per connection attempt, then
// reuse the answer across the join flow's reconnect cycles
static bool sFastDlAskedSession = false;
static bool sFastDlSessionAnswer = false;

///////////////////////////////////////////////////////////
// URL helpers
///////////////////////////////////////////////////////////

bool fastdl_set_url(const char* url) {
    sFastDlUrl[0] = '\0';
    if (url == NULL || url[0] == '\0') { return true; }

    size_t len = strlen(url);
    if (len == 0 || len >= FASTDL_URL_MAX) { return false; }
    if (strncmp(url, "http://", 7) != 0 && strncmp(url, "https://", 8) != 0) { return false; }

    for (size_t i = 0; i < len; i++) {
        char c = url[i];
        if (c < 0x21 || c > 0x7E || c == '\\' || c == '"') { return false; }
    }

    snprintf(sFastDlUrl, FASTDL_URL_MAX, "%s", url);
    size_t dstLen = strlen(sFastDlUrl);
    while (dstLen > 0 && sFastDlUrl[dstLen - 1] == '/') {
        sFastDlUrl[--dstLen] = '\0';
    }
    // require a non-empty host part after the scheme
    const char* schemeSep = strstr(sFastDlUrl, "://");
    if (schemeSep == NULL || schemeSep[3] == '\0') {
        sFastDlUrl[0] = '\0';
        return false;
    }
    return true;
}

void fastdl_clear_url(void) {
    sFastDlUrl[0] = '\0';
}

static void fastdl_url_encode(const char* in, char* out, size_t outSize) {
    static const char* hex = "0123456789ABCDEF";
    size_t o = 0;
    for (const char* p = in; *p != '\0' && o + 4 < outSize; p++) {
        char c = *p;
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') ||
            c == '-' || c == '.' || c == '_' || c == '~' || c == '/') {
            out[o++] = c;
        } else {
            out[o++] = '%';
            out[o++] = hex[((u8)c >> 4) & 0xF];
            out[o++] = hex[(u8)c & 0xF];
        }
    }
    out[o] = '\0';
}

// builds "<base>/<mod relative path>/<file relative path>", mirroring the host's mods/ folder layout
static bool fastdl_build_file_url(char* out, size_t outSize, const struct Mod* mod, const struct ModFile* file) {
    char relPath[SYS_MAX_PATH] = { 0 };
    if (mod->isDirectory) {
        if (snprintf(relPath, SYS_MAX_PATH, "%s/%s", mod->relativePath, file->relativePath) < 0) { return false; }
    } else {
        if (snprintf(relPath, SYS_MAX_PATH, "%s", file->relativePath) < 0) { return false; }
    }

    if (path_has_traversal(mod->relativePath) || path_has_traversal(file->relativePath)) {
        LOG_ERROR("FastDL: refusing to traverse '%s'", relPath);
        return false;
    }

    for (char* p = relPath; *p != '\0'; p++) {
        if (*p == '\\') { *p = '/'; }
    }

    char encoded[SYS_MAX_PATH] = { 0 };
    fastdl_url_encode(relPath, encoded, SYS_MAX_PATH);

    int written = snprintf(out, outSize, "%s/%s", sFastDlUrl, encoded);
    return (written > 0 && (size_t)written < outSize);
}

static void fastdl_format_size(u64 bytes, char* out, size_t outSize) {
    if (bytes >= (1024 * 1024)) {
        snprintf(out, outSize, "%.1f MB", (f64)bytes / (1024.0 * 1024.0));
    } else if (bytes >= 1024) {
        snprintf(out, outSize, "%.1f KB", (f64)bytes / 1024.0);
    } else {
        snprintf(out, outSize, "%u B", (u32)bytes);
    }
}

///////////////////////////////////////////////////////////
// HTTP fetch (WinINet on Windows, libcurl elsewhere)
///////////////////////////////////////////////////////////

#if defined(_WIN32)

static enum FastDlFetchResult fastdl_http_fetch(const char* url, FILE* fp, MD5_CTX* md5, u64 maxBytes, u64 startBytes, volatile u64* progressBytes, volatile bool* abortFlag) {
    HINTERNET hInternet = NULL;
    HINTERNET hUrl = NULL;
    enum FastDlFetchResult ret = FETCH_FILE_FAILED;
    u64 total = 0;

    hInternet = InternetOpenA("sm64coopdx-fastdl", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) { return FETCH_SERVER_FAILED; }

    DWORD timeout = FASTDL_TIMEOUT_MS;
    InternetSetOptionA(hInternet, INTERNET_OPTION_CONNECT_TIMEOUT, &timeout, sizeof(timeout));
    InternetSetOptionA(hInternet, INTERNET_OPTION_SEND_TIMEOUT, &timeout, sizeof(timeout));
    InternetSetOptionA(hInternet, INTERNET_OPTION_RECEIVE_TIMEOUT, &timeout, sizeof(timeout));
    DWORD retries = 1; // don't let WinINet stack its own connect retries on top of the timeout
    InternetSetOptionA(hInternet, INTERNET_OPTION_CONNECT_RETRIES, &retries, sizeof(retries));

    hUrl = InternetOpenUrlA(hInternet, url, NULL, 0,
        INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_PRAGMA_NOCACHE, 0);
    if (hUrl == NULL) {
        LOG_ERROR("FastDL: failed to open '%s' (%lu)", url, GetLastError());
        ret = FETCH_SERVER_FAILED;
        goto cleanup;
    }

    DWORD status = 0;
    DWORD statusSize = sizeof(status);
    if (!HttpQueryInfoA(hUrl, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &status, &statusSize, NULL) || status != 200) {
        LOG_ERROR("FastDL: '%s' answered status %lu", url, status);
        goto cleanup;
    }

    {
        u8 buffer[FASTDL_HTTP_BUFFER];
        while (true) {
            if (abortFlag != NULL && *abortFlag) { goto cleanup; }
            DWORD bytesRead = 0;
            if (!InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead)) {
                LOG_ERROR("FastDL: read failed for '%s' (%lu)", url, GetLastError());
                ret = FETCH_SERVER_FAILED;
                goto cleanup;
            }
            if (bytesRead == 0) { break; }
            total += bytesRead;
            if (total > maxBytes) { // maxBytes == 0 means the file should be empty
                LOG_ERROR("FastDL: '%s' sent more bytes than expected", url);
                goto cleanup;
            }
            if (fwrite(buffer, sizeof(u8), bytesRead, fp) != bytesRead) {
                LOG_ERROR("FastDL: write failed for '%s' (%s)", url, strerror(errno));
                goto cleanup;
            }
            MD5_Update(md5, buffer, bytesRead);
            if (progressBytes != NULL) { *progressBytes = startBytes + total; }
        }
    }

    ret = FETCH_OK;

cleanup:
    if (hUrl != NULL) { InternetCloseHandle(hUrl); }
    if (hInternet != NULL) { InternetCloseHandle(hInternet); }
    return ret;
}

#else

static bool sFastDlInited = false;

static void fastdl_curl_init(void) {
    // must be called from the main thread
    if (!sFastDlInited) {
        curl_global_init(CURL_GLOBAL_ALL);
        sFastDlInited = true;
    }
}

struct FastDlCurlData {
    FILE* fp;
    MD5_CTX* md5;
    u64 maxBytes;
    u64 startBytes;
    volatile u64* progressBytes;
    volatile bool* abortFlag;
    u64 total;
    bool overflow;
};

static size_t fastdl_curl_write_cb(char* ptr, size_t size, size_t nmemb, void* userdata) {
    struct FastDlCurlData* data = userdata;
    size_t bytes = size * nmemb;

    if (data->abortFlag != NULL && *data->abortFlag) { return 0; }

    data->total += bytes;
    if (data->total > data->maxBytes) { // maxBytes == 0 means the file should be empty
        data->overflow = true;
        return 0;
    }
    if (fwrite(ptr, sizeof(u8), bytes, data->fp) != bytes) { return 0; }
    MD5_Update(data->md5, ptr, bytes);
    if (data->progressBytes != NULL) { *data->progressBytes = data->startBytes + data->total; }
    return bytes;
}

static enum FastDlFetchResult fastdl_http_fetch(const char* url, FILE* fp, MD5_CTX* md5, u64 maxBytes, u64 startBytes, volatile u64* progressBytes, volatile bool* abortFlag) {
    struct FastDlCurlData data = { 0 };
    data.fp = fp;
    data.md5 = md5;
    data.maxBytes = maxBytes;
    data.startBytes = startBytes;
    data.progressBytes = progressBytes;
    data.abortFlag = abortFlag;

    CURL* curl = curl_easy_init();
    if (curl == NULL) { return FETCH_FILE_FAILED; }

    long timeout = FASTDL_TIMEOUT_MS / 1000;
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fastdl_curl_write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, timeout);
    curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 1L);
    curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 15L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "");

    CURLcode res = curl_easy_perform(curl);

    long status = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        if (!data.overflow && !(abortFlag != NULL && *abortFlag)) {
            LOG_ERROR("FastDL: request failed for '%s' (%s)", url, curl_easy_strerror(res));
        }
        // connection-level failures mean the whole phase is pointless
        switch (res) {
            case CURLE_COULDNT_RESOLVE_HOST:
            case CURLE_COULDNT_CONNECT:
            case CURLE_OPERATION_TIMEDOUT:
            case CURLE_RECV_ERROR:
                return FETCH_SERVER_FAILED;
            default:
                return FETCH_FILE_FAILED;
        }
    }
    if (data.overflow) {
        LOG_ERROR("FastDL: '%s' sent more bytes than expected", url);
        return FETCH_FILE_FAILED;
    }
    if (status != 200) {
        LOG_ERROR("FastDL: '%s' answered status %ld", url, status);
        return FETCH_FILE_FAILED;
    }
    return FETCH_OK;
}

#endif

///////////////////////////////////////////////////////////
// download worker
///////////////////////////////////////////////////////////

static enum FastDlFetchResult fastdl_download_file(struct FastDlCtx* ctx, struct FastDlJob* job) {
    enum FastDlFetchResult ret = FETCH_FILE_FAILED;
    FILE* fp = NULL;

    char partPath[SYS_MAX_PATH] = { 0 };
    int partPathLen = snprintf(partPath, SYS_MAX_PATH, "%s.part", job->destPath);
    if (partPathLen < 0 || partPathLen >= SYS_MAX_PATH) { return FETCH_FILE_FAILED; }

    fp = fopen(partPath, "wb");
    if (fp == NULL) {
        LOG_ERROR("FastDL: unable to open '%s' for write (%s)", partPath, strerror(errno));
        return FETCH_FILE_FAILED;
    }

    MD5_CTX md5 = { 0 };
    MD5_Init(&md5);

    u64 startBytes = ctx->doneBytes;
    ret = fastdl_http_fetch(job->url, fp, &md5, job->size, startBytes, &ctx->doneBytes, &ctx->aborted);
    if (ret != FETCH_OK) {
        goto cleanup;
    }
    fclose(fp);
    fp = NULL;

    u64 fetched = ctx->doneBytes - startBytes;
    if (fetched != job->size) {
        LOG_ERROR("FastDL: '%s' sent %llu bytes, expected %llu", job->url, (u64)fetched, (u64)job->size);
        goto cleanup;
    }

    // verify against the hash the host advertised in the mod list
    {
        u8 hash[16] = { 0 };
        MD5_Final(hash, &md5);
        if (memcmp(hash, job->dataHash, 16) != 0) {
            LOG_ERROR("FastDL: hash mismatch for '%s'", job->url);
            goto cleanup;
        }
    }

    remove(job->destPath);
    if (rename(partPath, job->destPath) != 0) {
        LOG_ERROR("FastDL: failed to move '%s' to '%s' (%s)", partPath, job->destPath, strerror(errno));
        goto cleanup;
    }

    LOG_INFO("FastDL: downloaded and verified '%s'", job->url);
    ret = FETCH_OK;

cleanup:
    if (fp != NULL) { fclose(fp); }
    if (ret != FETCH_OK) { remove(partPath); }
    return ret;
}

// display side only: the worker just bumps ctx->doneBytes, all UI math
// happens here on the main thread
static void fastdl_update_progress(struct FastDlCtx* ctx) {
    if (ctx->totalBytes > 0) {
        gDownloadProgress = (f32)ctx->doneBytes / (f32)ctx->totalBytes;
    } else {
        gDownloadProgress = 1.0f;
    }

    f32 elapsed = clock_elapsed() - ctx->startTime;
    u64 remaining = (ctx->doneBytes < ctx->totalBytes) ? (ctx->totalBytes - ctx->doneBytes) : 0;
    if (ctx->doneBytes > 0 && remaining > 0 && elapsed > 0.1f) {
        f32 bytesPerSecond = (f32)ctx->doneBytes / elapsed;
        u32 seconds = (u32)((remaining / bytesPerSecond) + 1);
        u32 minutes = seconds / 60;
        u32 hours = minutes / 60;
        seconds %= 60;
        minutes %= 60;
        if (hours) {
            snprintf(gDownloadEstimate, DOWNLOAD_ESTIMATE_LENGTH, "FastDL %uh %um", hours, minutes);
        } else if (minutes) {
            snprintf(gDownloadEstimate, DOWNLOAD_ESTIMATE_LENGTH, "FastDL %um %us", minutes, seconds);
        } else {
            snprintf(gDownloadEstimate, DOWNLOAD_ESTIMATE_LENGTH, "FastDL %us", seconds);
        }
    }
}

static void* fastdl_worker(void* arg) {
    struct FastDlCtx* ctx = arg;

    for (u32 i = 0; i < ctx->jobCount; i++) {
        struct FastDlJob* job = &ctx->jobs[i];
        if (ctx->aborted || ctx->generation != sFastDlGeneration) {
            break; // the main thread moved on; it owns the context again
        }
        if (job->url == NULL || job->destPath == NULL) {
            // job was never built; the file just stays on the chunk path
            continue;
        }

        enum FastDlFetchResult res = fastdl_download_file(ctx, job);
        if (res == FETCH_OK) {
            job->result = FDR_OK;
            ctx->jobsSucceeded++;
        } else {
            job->result = FDR_FAIL;
            if (res == FETCH_SERVER_FAILED) {
                // server unreachable (not started, wrong address, dropped):
                // likely to repeat - go back to in-game download path
                ctx->unreachable = true;
                break;
            }
        }
    }

    // make every prior write visible before signaling completion; done is
    // this thread's very last write, after which it never touches ctx again
    // and the main thread is free to apply the results and free the context
    __sync_synchronize();
    ctx->done = true;
    return NULL;
}

///////////////////////////////////////////////////////////
// job building + result application (main thread)
///////////////////////////////////////////////////////////

static void fastdl_free_ctx(struct FastDlCtx* ctx) {
    for (u32 i = 0; i < ctx->jobCount; i++) {
        if (ctx->jobs[i].url != NULL) { free(ctx->jobs[i].url); }
        if (ctx->jobs[i].destPath != NULL) { free(ctx->jobs[i].destPath); }
    }
    free(ctx->jobs);
    free(ctx);
}

static struct FastDlCtx* fastdl_build_ctx(void) {
    u32 jobCount = 0;
    u64 totalBytes = 0;
    for (u16 i = 0; i < gRemoteMods.entryCount; i++) {
        struct Mod* mod = gRemoteMods.entries[i];
        if (mod == NULL) { continue; }
        for (u16 j = 0; j < mod->fileCount; j++) {
            struct ModFile* file = &mod->files[j];
            if (file->cachedPath != NULL) { continue; }
            jobCount++;
            totalBytes += file->size;
        }
    }
    if (jobCount == 0) { return NULL; }

    struct FastDlCtx* ctx = calloc(1, sizeof(struct FastDlCtx));
    struct FastDlJob* jobs = calloc(jobCount, sizeof(struct FastDlJob));
    if (ctx == NULL || jobs == NULL) {
        free(ctx);
        free(jobs);
        return NULL;
    }

    ctx->jobs = jobs;
    ctx->jobCount = jobCount;
    ctx->totalBytes = totalBytes;

    u32 jobIndex = 0;
    for (u16 i = 0; i < gRemoteMods.entryCount; i++) {
        struct Mod* mod = gRemoteMods.entries[i];
        if (mod == NULL) { continue; }
        for (u16 j = 0; j < mod->fileCount; j++) {
            struct ModFile* file = &mod->files[j];
            if (file->cachedPath != NULL) { continue; }

            struct FastDlJob* job = &jobs[jobIndex];
            job->modIndex = i;
            job->fileIndex = j;
            job->size = file->size;
            memcpy(job->dataHash, file->dataHash, sizeof(u8) * 16);

            char destPath[SYS_MAX_PATH] = { 0 };
            if (!mod_file_full_path(destPath, mod, file)) {
                LOG_ERROR("FastDL: could not build destination path for '%s'", file->relativePath);
                jobIndex++;
                continue;
            }
            mod_file_create_directories(mod, file);
            job->destPath = strdup(destPath);

            char url[SYS_MAX_PATH] = { 0 };
            if (job->destPath == NULL || !fastdl_build_file_url(url, SYS_MAX_PATH, mod, file)) {
                LOG_ERROR("FastDL: could not build URL for '%s', falling back", file->relativePath);
                jobIndex++;
                continue;
            }
            job->url = strdup(url);
            jobIndex++;
        }
    }

    // jobs that failed to build fall back to the chunk path; don't count their bytes
    for (u32 i = 0; i < ctx->jobCount; i++) {
        if (ctx->jobs[i].url == NULL || ctx->jobs[i].destPath == NULL) {
            ctx->totalBytes -= ctx->jobs[i].size;
        }
    }

    return ctx;
}

static void fastdl_apply_results(struct FastDlCtx* ctx) {
    u32 failed = 0;

    for (u32 i = 0; i < ctx->jobCount; i++) {
        struct FastDlJob* job = &ctx->jobs[i];
        if (job->url == NULL || job->destPath == NULL) {
            // job was never built; the file just stays on the chunk path
            continue;
        }
        if (job->result != FDR_OK) {
            if (job->result == FDR_FAIL) { failed++; }
            continue;
        }
        if (job->modIndex >= gRemoteMods.entryCount) { continue; }
        struct Mod* mod = gRemoteMods.entries[job->modIndex];
        if (mod == NULL || job->fileIndex >= mod->fileCount) { continue; }
        struct ModFile* file = &mod->files[job->fileIndex];
        if (file->cachedPath == NULL && mod_should_cache(mod)) {
            // mod_cache_add hashes the verified file and registers it in mod.cache
            mod_cache_add(mod, file, false);
        } else if (file->cachedPath == NULL) {
            // WIP mods are never cached; just mark the file as present
            char modFilePath[SYS_MAX_PATH] = { 0 };
            if (concat_path(modFilePath, mod->basePath, file->relativePath)) {
                normalize_path(modFilePath);
                file->cachedPath = strdup(modFilePath);
            }
        }
    }

    if (ctx->unreachable) {
        LOG_ERROR("FastDL: could not connect to '%s', using in-game transfer", sFastDlUrl);
        char message[FASTDL_URL_MAX + 128] = { 0 };
        djui_language_replace(DLANG(NOTIF, FASTDL_UNREACHABLE), message, sizeof(message), '@', sFastDlUrl);
        djui_popup_create(message, 2);
    } else if (failed > 0) {
        LOG_INFO("FastDL: %u file(s) failed, using in-game transfer for them", failed);
        char countStr[16] = { 0 };
        snprintf(countStr, sizeof(countStr), "%u", failed);
        char message[160] = { 0 };
        djui_language_replace(DLANG(NOTIF, FASTDL_FAILED), message, sizeof(message), '@', countStr);
        djui_popup_create(message, 2);
    }

    network_start_download_requests();
}

///////////////////////////////////////////////////////////
// "let me choose" popup
///////////////////////////////////////////////////////////

static void fastdl_begin(void);

static bool fastdl_popup_back(UNUSED struct DjuiBase* base) {
    if (sFastDlState != FDLS_POPUP) {
        return false; // stale popup (the connection went away); just close it
    }

    bool accept = sFastDlAnswerYes;
    sFastDlAnswerYes = false;
    sFastDlSessionAnswer = accept;
    sFastDlState = FDLS_IDLE;

    if (accept) {
        fastdl_begin();
    } else {
        network_start_download_requests();
    }
    return false; // let the default back logic close the popup
}

static void fastdl_popup_yes(struct DjuiBase* caller) {
    sFastDlAnswerYes = true;
    djui_panel_menu_back(caller);
}

static void fastdl_popup_no(struct DjuiBase* caller) {
    sFastDlAnswerYes = false;
    djui_panel_menu_back(caller);
}

static void fastdl_popup_create(u32 fileCount, u64 totalBytes) {
    static char sMessage[1024];

    sFastDlAnswerYes = false;

    char filesStr[16] = { 0 };
    char sizeStr[32] = { 0 };
    snprintf(filesStr, sizeof(filesStr), "%u", fileCount);
    fastdl_format_size(totalBytes, sizeStr, sizeof(sizeStr));

    char body[384] = { 0 };
    djui_language_replace2(DLANG(FASTDL, POPUP_BODY), body, sizeof(body), '@', filesStr, '#', sizeStr);
    snprintf(sMessage, sizeof(sMessage), "%s\n\\#a0a0ff\\%s\\#\\\n\n%s", body, sFastDlUrl, DLANG(FASTDL, CONTINUE));

    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(FASTDL, TITLE), false);
    panel->on_back = fastdl_popup_back;
    struct DjuiBase* bodyBase = djui_three_panel_get_body(panel);
    {
        struct DjuiText* text = djui_text_create(bodyBase, sMessage);
        djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);

        djui_base_set_size(&text->base, 1.0f, 64);
        djui_base_compute_tree(&text->base);
        u16 lines = djui_text_count_lines(text, 12);
        f32 textHeight = 32 * 0.8125f * lines + 8;
        djui_base_set_size(&text->base, 1.0f, textHeight);
        djui_base_set_color(&text->base, 220, 220, 220, 255);
        djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_TOP);

        struct DjuiRect* rect = djui_rect_container_create(bodyBase, 64);
        {
            djui_button_left_create(&rect->base, DLANG(MENU, NO), DJUI_BUTTON_STYLE_NORMAL, fastdl_popup_no);
            djui_button_right_create(&rect->base, DLANG(MENU, YES), DJUI_BUTTON_STYLE_NORMAL, fastdl_popup_yes);
        }
    }

    djui_panel_add(NULL, panel, NULL);
    sFastDlState = FDLS_POPUP;
}

///////////////////////////////////////////////////////////
// public flow
///////////////////////////////////////////////////////////

// stops the current transfer, if any: the worker is told to stop starting new
// work; its context is freed right away when it already signaled done, and
// parked in sFastDlPendingFree for fastdl_update to free once it does
// (the worker never frees the context itself)
static void fastdl_stop_transfer(void) {
    sFastDlGeneration++;
    struct FastDlCtx* ctx = sFastDlCtx;
    if (ctx == NULL) { return; }

    ctx->aborted = true;
    if (ctx->done) {
        fastdl_free_ctx(ctx);
    } else if (sFastDlPendingFree == NULL || sFastDlPendingFree->done) {
        if (sFastDlPendingFree != NULL) { fastdl_free_ctx(sFastDlPendingFree); }
        sFastDlPendingFree = ctx;
    }
    // (in the remaining case - an earlier transfer still in flight - this one
    // is leaked rather than risk freeing a context its worker may still touch)

    sFastDlCtx = NULL;
    sFastDlState = FDLS_IDLE;
}

static void fastdl_begin(void) {
    if (sFastDlUrl[0] == '\0') {
        // the connection went away while the popup was up; let the chunk path wrap up
        network_start_download_requests();
        return;
    }

    struct FastDlCtx* ctx = fastdl_build_ctx();
    if (ctx == NULL) {
        // nothing left to fetch; let the chunk path wrap up (it will skip straight to the join)
        network_start_download_requests();
        return;
    }

#ifndef _WIN32
    fastdl_curl_init();
#endif

    // safety: stop any transfer that is somehow still around before replacing it
    fastdl_stop_transfer();

    ctx->generation = sFastDlGeneration;
    sFastDlCtx = ctx;
    sFastDlState = FDLS_DOWNLOADING;

    gDownloadProgress = 0;
    gDownloadProgressInf = 0;
    snprintf(gDownloadEstimate, DOWNLOAD_ESTIMATE_LENGTH, "FastDL");
    ctx->startTime = clock_elapsed();

    LOG_INFO("FastDL: downloading %u file(s), %llu bytes from '%s'", ctx->jobCount, (u64)ctx->totalBytes, sFastDlUrl);

    if (init_thread(&sFastDlThread, fastdl_worker, ctx, NULL, 0) != 0) {
        LOG_ERROR("FastDL: failed to spawn worker thread");
        sFastDlCtx = NULL;
        sFastDlState = FDLS_IDLE;
        fastdl_free_ctx(ctx);
        network_start_download_requests();
        return;
    }
    detach_thread(&sFastDlThread);
}

bool fastdl_on_mod_list_done(void) {
    if (gNetworkType != NT_CLIENT) { return false; }
    if (sFastDlState != FDLS_IDLE) { return true; } // already took over the flow
    if (sFastDlUrl[0] == '\0') { return false; }    // host doesn't offer FastDL

    u32 uncached = 0;
    u64 totalBytes = 0;
    for (u16 i = 0; i < gRemoteMods.entryCount; i++) {
        struct Mod* mod = gRemoteMods.entries[i];
        if (mod == NULL) { continue; }
        for (u16 j = 0; j < mod->fileCount; j++) {
            struct ModFile* file = &mod->files[j];
            if (file->cachedPath != NULL) { continue; }
            uncached++;
            totalBytes += file->size;
        }
    }
    if (uncached == 0) { return false; }

    switch (configFastDlMode) {
        case FDLM_ALWAYS_ON:
            fastdl_begin();
            return true;

        case FDLM_ALWAYS_OFF:
            return false;

        case FDLM_LET_ME_CHOOSE:
        default: {
            if (sFastDlAskedSession) {
                if (sFastDlSessionAnswer) {
                    fastdl_begin();
                    return true;
                }
                return false;
            }

            if (djui_is_popup_disabled()) {
                LOG_INFO("FastDL: popups disabled, defaulting to in-game transfer");
                return false;
            }
            sFastDlAskedSession = true;
            fastdl_popup_create(uncached, totalBytes);
            return true;
        }
    }
}

void fastdl_update(void) {
    // an aborted transfer's worker stops touching its context after signaling
    // done; that is the cue to free it
    if (sFastDlPendingFree != NULL && sFastDlPendingFree->done) {
        struct FastDlCtx* ctx = sFastDlPendingFree;
        sFastDlPendingFree = NULL;
        __sync_synchronize(); // pair with the worker's barrier before ->done
        fastdl_free_ctx(ctx);
    }

    if (sFastDlState != FDLS_DOWNLOADING || sFastDlCtx == NULL) { return; }

    fastdl_update_progress(sFastDlCtx);

    if (sFastDlCtx->done) {
        struct FastDlCtx* ctx = sFastDlCtx;
        sFastDlCtx = NULL;
        sFastDlState = FDLS_IDLE;
        if (ctx->generation == sFastDlGeneration) {
            fastdl_apply_results(ctx);
        }
        fastdl_free_ctx(ctx);
    }
}

void fastdl_shutdown(bool reconnecting) {
    fastdl_stop_transfer();
    fastdl_clear_url();

    // the sticky answer only survives auto-reconnects, not full disconnects
    if (!reconnecting) {
        sFastDlAskedSession = false;
        sFastDlSessionAnswer = false;
    }
}
