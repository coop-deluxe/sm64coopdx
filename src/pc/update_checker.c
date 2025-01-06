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

static char sVersionUpdateTextBuffer[256] = { 0 };
static char sRemoteVersion[8] = { 0 };

bool gUpdateMessage = false;

void show_update_popup(void) {
    if (sVersionUpdateTextBuffer[0] == '\0') { return; }
    djui_popup_create(sVersionUpdateTextBuffer, 3);
}

#if !(defined(_WIN32) || defined(_WIN64))
size_t write_callback(char *ptr, size_t size, size_t nmemb, char **data) {
    size_t realsize = size * nmemb;

    // allocate memory for the received data and copy it into the buffer
    *data = realloc(*data, realsize + 1);
    if (*data == NULL) { return 0; }

    memcpy(*data, ptr, realsize);
    (*data)[realsize] = '\0'; // null-terminate the string

    return realsize;
}
#endif

void parse_version(const char *data) {
    const char *version = strstr(data, VERSION_IDENTIFIER);
    if (version == NULL) { return; }
    u8 len = strlen(VERSION_IDENTIFIER);
    version += len;
    const char *end = strchr(version, '"');
    memcpy(sRemoteVersion, version, end - version);
    sRemoteVersion[end - version] = '\0';
}

// function to download a text file from the internet
void get_version_remote(void) {
#if defined(_WIN32) || defined(_WIN64)
    char buffer[0xFF];

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

    // read data from the URL
    DWORD bytesRead;
    if (!InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead)) {
        printf("Failed to check for updates!\n");
        InternetCloseHandle(hInternet);
        InternetCloseHandle(hUrl);
        return;
    }

    buffer[bytesRead] = '\0';
    snprintf(sRemoteVersion, 8, "%s", buffer);

    // close handles
    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);
#else
    char* buffer = NULL;

    // initialize libcurl
    CURL *curl = curl_easy_init();
    if (!curl || curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
        printf("Failed to check for updates!\n");
        return;
    }

    // set properties
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
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

    if (!buffer) { return; }

    snprintf(sRemoteVersion, 8, "%s", buffer);

    // Clean up
    curl_easy_cleanup(curl);
#endif
    parse_version(buffer);
}

void check_for_updates(void) {
    LOADING_SCREEN_MUTEX(loading_screen_set_segment_text("Checking For Updates"));

    get_version_remote();
    if (sRemoteVersion[0] != '\0' && strcmp(sRemoteVersion, get_version())) {
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
