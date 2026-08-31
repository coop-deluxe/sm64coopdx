#include <stdio.h>
#include "../network.h"
#include "PR/os_eeprom.h"
#include "game/save_file.h"
#include "pc/debuglog.h"

// subtract 8 from packet length for the startingSaveFile and endSaveFile integers (an integer is 4 bytes)
#define NUM_CHUNKS ((NUM_SAVE_FILES * EEPROM_SIZE + (PACKET_LENGTH - 8) - 1) / (PACKET_LENGTH - 8))

static u8 sEeprom[NUM_SAVE_FILES][EEPROM_SIZE] = { 0 };
static bool sReceivedSaveFile[NUM_SAVE_FILES] = { 0 };
static int sFilledEepromData = 0;

void network_send_download_save_files_request(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    sFilledEepromData = 0;
    memset(sReceivedSaveFile, 0, sizeof(sReceivedSaveFile));

    struct Packet p = { 0 };
    packet_init(&p, PACKET_DOWNLOAD_SAVE_REQUEST, true, PLMT_NONE);

    network_send_to((gNetworkPlayerServer != NULL) ? gNetworkPlayerServer->localIndex : 0, &p);
    LOG_INFO("sending download save files request");
}

void network_receive_download_saves_request(UNUSED struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    for (int i = 0; i < NUM_CHUNKS; i++) {
        network_send_download_save(i);
    }

    LOG_INFO("sending save info");
}

void network_send_download_save(int chunk) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    int startingSaveFile = chunk * (NUM_SAVE_FILES + NUM_CHUNKS - 1) / NUM_CHUNKS;
    int endSaveFile = (chunk + 1) * (NUM_SAVE_FILES + NUM_CHUNKS - 1) / NUM_CHUNKS;
    if (endSaveFile > NUM_SAVE_FILES) endSaveFile = NUM_SAVE_FILES;

    struct Packet p = { 0 };
    packet_init(&p, PACKET_DOWNLOAD_SAVE_FILE, true, PLMT_NONE);
    packet_write(&p, &startingSaveFile, sizeof(startingSaveFile));
    packet_write(&p, &endSaveFile, sizeof(endSaveFile));

    for (int i = startingSaveFile; i < endSaveFile; i++) {
        u8 content[EEPROM_SIZE] = { 0 };
        char filePath[256];
        save_file_get_dir(i, filePath, 256, NULL);
        fs_file_t* fp = fs_open(filePath);
        if (fp != NULL) {
            fs_read(fp, content, EEPROM_SIZE);
            fs_close(fp);
        }
        packet_write(&p, content, sizeof(content));
    }

    network_send_to(0, &p);
}

void network_receive_download_save(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    // make sure it was sent by the server
    if (p->localIndex != UNKNOWN_LOCAL_INDEX) {
        if (gNetworkPlayerServer == NULL || gNetworkPlayerServer->localIndex != p->localIndex) {
            LOG_ERROR("Received download from known local index '%d'", p->localIndex);
            return;
        }
    }

    if (sFilledEepromData >= NUM_SAVE_FILES * EEPROM_SIZE) {
        LOG_ERROR("Received eeprom data after eeprom was filled");
        djui_popup_create(DLANG(NOTIF, DISCONNECT_CLOSED), 1);
        network_shutdown(false, false, false, false);
        return;
    }

    int startingSaveFile = 0;
    int endSaveFile = 0;
    packet_read(p, &startingSaveFile, sizeof(startingSaveFile));
    packet_read(p, &endSaveFile, sizeof(endSaveFile));

    if (startingSaveFile < 0 || endSaveFile < startingSaveFile || endSaveFile > NUM_SAVE_FILES) {
        LOG_ERROR("Received invalid start and end file");
        djui_popup_create(DLANG(NOTIF, DISCONNECT_CLOSED), 1);
        network_shutdown(false, false, false, false);
    }

    for (int i = startingSaveFile; i < endSaveFile; i++) {
        packet_read(p, &sEeprom[i], sizeof(sEeprom[i]));
        if (!sReceivedSaveFile[i]) {
            sReceivedSaveFile[i] = true;
            sFilledEepromData += EEPROM_SIZE;
        }
    }

    if (sFilledEepromData == NUM_SAVE_FILES * EEPROM_SIZE) {
        for (int i = 0; i < NUM_SAVE_FILES; i++) {
            gOverrideEeprom[i] = sEeprom[i];
        }
        sFilledEepromData = 0;
        network_send_join_request();
    } else if (sFilledEepromData > NUM_SAVE_FILES * EEPROM_SIZE) {
        LOG_ERROR("Filled eeprom data too much! Should be %d, but is %d", NUM_SAVE_FILES * EEPROM_SIZE, sFilledEepromData);
        djui_popup_create(DLANG(NOTIF, DISCONNECT_CLOSED), 1);
        network_shutdown(false, false, false, false);
        return;
    }
}
