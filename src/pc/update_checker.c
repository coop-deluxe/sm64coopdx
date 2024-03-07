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

#define URL "https://sm64coopdx.com/download/version.txt"

static char sVersionUpdateTextBuffer[256] = { 0 };
static char sRemoteVersion[8];

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

// function to download a text file from the internet
const char* get_version_remote(void) {
#if defined(_WIN32) || defined(_WIN64)
    HINTERNET hInternet, hUrl;
    DWORD bytesRead;
    char buffer[8];

    // initialize WinINet
    hInternet = InternetOpenA("sm64coopdx", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        printf("Failed to check for updates!\n");
        InternetCloseHandle(hInternet);
        InternetCloseHandle(hUrl);
        return NULL;
    }

    // open the URL
    hUrl = InternetOpenUrlA(hInternet, URL, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hUrl) {
        printf("Failed to check for updates!\n");
        InternetCloseHandle(hInternet);
        InternetCloseHandle(hUrl);
        return NULL;
    }

    // calculate the size of the file
    DWORD contentLength;
    DWORD dwSize = sizeof(contentLength);
    HttpQueryInfo(hUrl, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, &contentLength, &dwSize, NULL);

    // read data from the URL
    if (!InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead)) {
        printf("Failed to check for updates!\n");
        InternetCloseHandle(hInternet);
        InternetCloseHandle(hUrl);
        return NULL;
    }

    strncpy(sRemoteVersion, buffer, 8);

    // close handles
    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);
#else
    CURL *curl;
    CURLcode res;
    char *data = NULL;
    
    // initialize libcurl
    curl = curl_easy_init();
    if (!curl) {
        printf("Failed to check for updates!\n");
        return NULL;
    }

    // set the URL to retrieve data from
    curl_easy_setopt(curl, CURLOPT_URL, URL);

    // set the write callback function to store received data into the buffer
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

    // perform the request
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        printf("Failed to check for updates!\n");
        curl_easy_cleanup(curl);
        return NULL;
    }

    strncpy(sRemoteVersion, data, 8);

    // Clean up
    curl_easy_cleanup(curl);
#endif

    return sRemoteVersion;
}

void check_for_updates(void) {
    REFRESH_MUTEX(
        gCurrLoadingSegment.percentage = 0;
        snprintf(gCurrLoadingSegment.str, 256, "Checking For Updates");
    );

#if defined(_WIN32) || defined(_WIN64)
    const char* remoteVersion = get_version_remote();
    if (strcmp(get_version_remote(), SM64COOPDX_VERSION)) {
        snprintf(
            sVersionUpdateTextBuffer, 256,
            "\\#ffffa0\\%s\n\\#dcdcdc\\%s: v%s\n%s: v%s",
            DLANG(NOTIF, UPDATE_AVAILABLE),
            DLANG(NOTIF, LATEST_VERSION),
            remoteVersion,
            DLANG(NOTIF, YOUR_VERSION),
            SM64COOPDX_VERSION
        );
        gUpdateMessage = true;
    }
#else

#endif
}
