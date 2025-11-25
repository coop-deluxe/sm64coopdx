#include <stdio.h>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <wininet.h>
#else
#include <curl/curl.h>
#endif

#include "update_checker.h"
#include "pc/djui/djui.h"
#include "pc/network/version.h"
#include "pc/loading.h"

#define URL "https://raw.githubusercontent.com/coop-deluxe/sm64coopdx/refs/heads/main/src/pc/network/version.h"
#define VERSION_IDENTIFIER "#define SM64COOPDX_VERSION \""

/*

NOTE: This entire update checker process should be replaced with one that uses GitHub's API
to check for the latest release version. This would be more reliable and efficient than
downloading and parsing a source file.

*/

static char sVersionUpdateTextBuffer[256] = { 0 };
static char sRemoteVersion[8] = { 0 };

bool gUpdateMessage = false;

void show_update_popup(void) {
    if (sVersionUpdateTextBuffer[0] == '\0') { return; }
    djui_popup_create(sVersionUpdateTextBuffer, 3);
}

#if !(defined(_WIN32) || defined(_WIN64))
typedef struct { char *str; size_t size; } Buffer;
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t realsize = size * nmemb;
    Buffer *buf = (Buffer *) userdata;

    // allocate memory for the received data and copy it into the buffer
    char *data = realloc(buf->str, buf->size + realsize + 1);
    if (data == NULL) { return 0; }

    memcpy(&data[buf->size], ptr, realsize);
    buf->size += realsize;
    buf->str = data;
    buf->str[buf->size] = '\0'; // null-terminate the string

    return realsize;
}
#endif

void parse_version(const char *data) {
    const char *version = strstr(data, VERSION_IDENTIFIER);
    if (version == NULL) { return; }
    size_t len = strlen(VERSION_IDENTIFIER);
    version += len;
    const char *end = strchr(version, '"');
    size_t versionLength = (size_t)(end - version);
    if (versionLength > sizeof(sRemoteVersion) - 1) { return; }
    memcpy(sRemoteVersion, version, versionLength);
    sRemoteVersion[versionLength] = '\0';
}

// function to download a text file from the internet
void get_version_remote(void) {
    sRemoteVersion[0] = '\0';

#if defined(_WIN32) || defined(_WIN64)
    char buffer[0xFF] = { 0 };

    // initialize WinINet
    HINTERNET hInternet = InternetOpenA("sm64coopdx", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        printf("Failed to check for updates!\n");
        InternetCloseHandle(hInternet);
        return;
    }

    // open the URL
    HINTERNET hUrl = InternetOpenUrlA(hInternet, URL, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hUrl) {
        printf("Failed to check for updates!\n");
        InternetCloseHandle(hInternet);
        InternetCloseHandle(hUrl);
        return;
    }

    // calculate the size of the file
    DWORD contentLength;
    DWORD dwSize = sizeof(contentLength);
    HttpQueryInfo(hUrl, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, &contentLength, &dwSize, NULL);

    // read data from the URL, making room in the buffer for the null-terminator
    DWORD bytesRead;
    if (!InternetReadFile(hUrl, buffer, sizeof(buffer) - 1, &bytesRead)) {
        printf("Failed to check for updates!\n");
        InternetCloseHandle(hInternet);
        InternetCloseHandle(hUrl);
        return;
    }

    buffer[bytesRead] = '\0';

    // close handles
    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);
#else
    Buffer data = { .str = NULL, .size = 0 };

    // initialize libcurl
    CURL *curl = curl_easy_init();
    if (!curl || curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
        printf("Failed to check for updates!\n");
        return;
    }

    // set properties
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3); // only allow 3 seconds
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_URL, URL);

    // perform the request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        printf("Failed to check for updates!\n");
        curl_easy_cleanup(curl);
        return;
    }
    char* buffer = data.str;

    // Clean up
    curl_easy_cleanup(curl);
#endif
    parse_version(buffer);
#if !(defined(_WIN32) || defined(_WIN64))
    free(buffer);
#endif
}

void check_for_updates(void) {
    LOADING_SCREEN_MUTEX(loading_screen_set_segment_text("Checking For Updates"));

    get_version_remote();
    if (sRemoteVersion[0] == 'v' && strcmp(sRemoteVersion, get_version())) {
        snprintf(
            sVersionUpdateTextBuffer, 256,
            "\\#ffffa0\\%s\n\\#dcdcdc\\%s: %s\n%s: %s",
            DLANG(NOTIF, UPDATE_AVAILABLE),
            DLANG(NOTIF, LATEST_VERSION),
            sRemoteVersion,
            DLANG(NOTIF, YOUR_VERSION),
            get_version()
        );
        gUpdateMessage = true;
    }
}
