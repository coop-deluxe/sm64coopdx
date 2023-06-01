#include <stdio.h>
#include "../network.h"
#include "pc/debuglog.h"
#include "pc/djui/djui.h"

void network_send_global_popup(const char* message, int lines) {
    // get message length
    u16 messageLength = strlen(message);

    // make message mutable
    char mutableMessage[messageLength];
    strcpy(mutableMessage, message);

    // configure packet
    struct Packet p = { 0 };
    packet_init(&p, PACKET_GLOBAL_POPUP, true, PLMT_NONE);
    packet_write(&p, &lines, sizeof(int));
    packet_write(&p, &messageLength, sizeof(u16));
    packet_write(&p, mutableMessage, messageLength * sizeof(u8));
    
    // send the packet
    network_send(&p);
}

void network_receive_global_popup(struct Packet* p) {
    
    u16 messageLength = 0;
    char message[256] = { 0 };
    int lines;

    // read data
    packet_read(p, &lines, sizeof(int));
    packet_read(p, &messageLength, sizeof(u16));
    if (messageLength >= 255) { messageLength = 255; }
    packet_read(p, &message, messageLength * sizeof(u8));
    // show popup
    djui_popup_create(&message, lines);
}