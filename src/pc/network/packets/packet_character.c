#include <stdio.h>
#include "../network.h"
#include "pc/djui/djui.h"
#include "pc/debuglog.h"
#include "game/object_list_processor.h"

void network_send_character() {
    struct Character* character = gMarioStates[0].character;
    if (!character) {
        LOG_ERROR("network_send_character: Character is NULL, could not send packet");
        return;
    }

    for (int i = 1; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected) { continue; }

        network_send_character_to(np->globalIndex);
    }
}

void network_request_all_characters() {
    for (int i = 1; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected) { continue; }

        network_request_character_from(np->globalIndex);
    }
}

void network_request_character_from(u8 requestGlobalIndex) {
    struct Packet p = { 0 };
    packet_init(&p, PACKET_CHARACTER_REQUEST, true, PLMT_NONE);
    packet_write(&p, &gNetworkPlayerLocal->globalIndex, sizeof(u8));

    network_send_to(network_local_index_from_global(requestGlobalIndex), &p);
}

void network_receive_character_request(struct Packet* p) {
    u8 globalIndex;
    packet_read(p, &globalIndex, sizeof(u8));
    struct NetworkPlayer* np = network_player_from_global_index(globalIndex);
    if (!np->connected) { return; }

    network_send_character_to(np->localIndex);
}

void network_send_character_to(u8 sendToGlobalIndex) {
    if (sendToGlobalIndex < 0 || sendToGlobalIndex >= MAX_PLAYERS) {
        LOG_ERROR("network_send_character_to: sendToGlobalIndex is invalid, could not send packet");
        return;
    }
    struct Character* character = gMarioStates[0].character;
    if (!character) {
        LOG_ERROR("network_send_character_to: Character is NULL, could not send packet");
        return;
    }
    struct Packet p = { 0 };
    packet_init(&p, PACKET_CHARACTER, true, PLMT_NONE);
    packet_write(&p, &gNetworkPlayerLocal->globalIndex, sizeof(u8));

    packet_write(&p, &character->type, sizeof(enum CharacterType));
    packet_write(&p, &character->name, sizeof(character->name));

    u16 nameLen = strlen(character->hudHeadTexture.name);
    packet_write(&p, &nameLen, sizeof(u16));
    packet_write(&p, (void*)character->hudHeadTexture.name, sizeof(u8) * nameLen);

    packet_write(&p, &character->modelId, sizeof(u32));
    packet_write(&p, &character->capModelId, sizeof(u32));
    packet_write(&p, &character->capMetalModelId, sizeof(u32));
    packet_write(&p, &character->capWingModelId, sizeof(u32));
    packet_write(&p, &character->capMetalWingModelId, sizeof(u32));
    packet_write(&p, &character->capEnemyLayer, sizeof(u8));

    packet_write(&p, &character->torsoRotMult, sizeof(f32));
    packet_write(&p, &character->animOffsetEnabled, sizeof(u8));
    packet_write(&p, &character->animOffsetLowYPoint, sizeof(f32));
    packet_write(&p, &character->animOffsetFeet, sizeof(f32));
    packet_write(&p, &character->animOffsetHand, sizeof(f32));

    packet_write(&p, &character->anims, sizeof(character->anims));
    packet_write(&p, &character->moddedAnims, sizeof(character->moddedAnims));
    packet_write(&p, &character->soundFreqScale, sizeof(f32));
    packet_write(&p, &character->sounds, sizeof(character->sounds));
    packet_write(&p, &character->modAudioSounds, sizeof(character->modAudioSounds));
    packet_write(&p, &character->modIndexForAudio, sizeof(character->modIndexForAudio));

    network_send_to(network_local_index_from_global(sendToGlobalIndex), &p);
}

void network_receive_character(struct Packet* p) {
    u8 globalIndex;
    packet_read(p, &globalIndex, sizeof(u8));
    struct Character* character = gMarioStates[network_local_index_from_global(globalIndex)].character;
    if (!character) {
        LOG_ERROR("network_receive_character: Character is NULL for globalIndex %d", globalIndex);
        return;
    }

    packet_read(p, &character->type, sizeof(enum CharacterType));
    packet_read(p, &character->name, sizeof(character->name));

    u16 texNameLength = 0;
    packet_read(p, &texNameLength, sizeof(u16));
    if (texNameLength > 256) {
        LOG_ERROR("Received texture name with length higher than 256!");
        return;
    }
    char texName[256 + 1] = { 0 };
    packet_read(p, texName, sizeof(u8) * texNameLength);
    if (!dynos_texture_get(texName, &character->hudHeadTexture)) {
        LOG_ERROR("network_receive_character: Texture info for %s does not exist, setting hud texture to mario's head", texName);
        character->hudHeadTexture = gOriginalCharacters[0].hudHeadTexture;
    }

    packet_read(p, &character->modelId, sizeof(u32));
    packet_read(p, &character->capModelId, sizeof(u32));
    packet_read(p, &character->capMetalModelId, sizeof(u32));
    packet_read(p, &character->capWingModelId, sizeof(u32));
    packet_read(p, &character->capMetalWingModelId, sizeof(u32));
    packet_read(p, &character->capEnemyLayer, sizeof(u8));

    packet_read(p, &character->torsoRotMult, sizeof(f32));
    packet_read(p, &character->animOffsetEnabled, sizeof(u8));
    packet_read(p, &character->animOffsetLowYPoint, sizeof(f32));
    packet_read(p, &character->animOffsetFeet, sizeof(f32));
    packet_read(p, &character->animOffsetHand, sizeof(f32));

    packet_read(p, &character->anims, sizeof(character->anims));
    packet_read(p, &character->moddedAnims, sizeof(character->moddedAnims));
    packet_read(p, &character->soundFreqScale, sizeof(f32));
    packet_read(p, &character->sounds, sizeof(character->sounds));
    packet_read(p, &character->modAudioSounds, sizeof(character->modAudioSounds));
    packet_read(p, &character->modIndexForAudio, sizeof(character->modIndexForAudio));
}