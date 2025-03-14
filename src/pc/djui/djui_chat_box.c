#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pc/network/network.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/chat_commands.h"
#include "pc/configfile.h"
#include "djui.h"

struct DjuiChatBox* gDjuiChatBox = NULL;
bool gDjuiChatBoxFocus = false;
static bool sDjuiChatBoxClearText = false;

#define MAX_HISTORY_SIZE 256

typedef struct {
    s32 initialized;
    s32 size;
    char messages[MAX_HISTORY_SIZE][MAX_CHAT_MSG_LENGTH];
    s32 currentIndex;
    char currentMessage[MAX_CHAT_MSG_LENGTH];
} ArrayList;

ArrayList sentHistory;

static s32 sCommandsTabCompletionIndex = -1;
static char sCommandsTabCompletionOriginalText[MAX_CHAT_MSG_LENGTH];
static s32 sPlayersTabCompletionIndex = -1;
static char sPlayersTabCompletionOriginalText[MAX_CHAT_MSG_LENGTH];

void reset_tab_completion_commands(void) {
    sCommandsTabCompletionIndex = -1;
    snprintf(sCommandsTabCompletionOriginalText, MAX_CHAT_MSG_LENGTH, "%s", "");
}
void reset_tab_completion_players(void) {
    sPlayersTabCompletionIndex = -1;
    snprintf(sPlayersTabCompletionOriginalText, MAX_CHAT_MSG_LENGTH, "%s", "");
}
void reset_tab_completion_all(void) {
    reset_tab_completion_commands();
    reset_tab_completion_players();
}

void sent_history_init(ArrayList *arrayList) {
    if (!arrayList->initialized) {
        arrayList->size = 0;
        arrayList->initialized = 1;
        arrayList->currentIndex = -1;
        snprintf(arrayList->currentMessage, MAX_CHAT_MSG_LENGTH, "%s", "");
    }
}

void sent_history_add_message(ArrayList *arrayList, const char *newMessage) {
    if (!configUseStandardKeyBindingsChat && (!newMessage || newMessage[0] != '/')) { return; }

    if (arrayList->size == MAX_HISTORY_SIZE) {
        for (s32 i = 1; i < MAX_HISTORY_SIZE; i++) {
            snprintf(arrayList->messages[i-1], MAX_CHAT_MSG_LENGTH, "%s", arrayList->messages[i]);
        }
        arrayList->size--;
    }

    snprintf(arrayList->messages[arrayList->size], MAX_CHAT_MSG_LENGTH, "%s", newMessage);
    arrayList->messages[arrayList->size][MAX_CHAT_MSG_LENGTH - 1] = '\0';
    arrayList->size++;
}

void sent_history_update_current_message(ArrayList *arrayList, const char *message) {
    if (arrayList->currentIndex == -1) {
        snprintf(arrayList->currentMessage, MAX_CHAT_MSG_LENGTH, "%s", message);
    }
}

void sent_history_navigate(ArrayList *arrayList, bool navigateUp) {
    if (navigateUp) {
        if (arrayList->currentIndex == -1) {
            arrayList->currentIndex = arrayList->size - 1;
        } else if (arrayList->currentIndex > 1) {
            arrayList->currentIndex = arrayList->currentIndex - 1;
        } else {
            arrayList->currentIndex = 0;
        }
    } else {
        if (arrayList->currentIndex == -1 || arrayList->currentIndex == arrayList->size - 1) {
            arrayList->currentIndex = -1;
        } else if (arrayList->currentIndex > -1) {
            arrayList->currentIndex = arrayList->currentIndex + 1;
        }
    }
    djui_inputbox_set_text(gDjuiChatBox->chatInput, arrayList->currentIndex == -1 ? arrayList->currentMessage : arrayList->messages[arrayList->currentIndex]);
    djui_inputbox_move_cursor_to_end(gDjuiChatBox->chatInput);
}

void sent_history_reset_navigation(ArrayList *arrayList) {
    snprintf(arrayList->currentMessage, MAX_CHAT_MSG_LENGTH, "%s", "");
    arrayList->currentIndex = -1;
}

bool djui_chat_box_render(struct DjuiBase* base) {
    struct DjuiChatBox* chatBox = (struct DjuiChatBox*)base;
    struct DjuiBase* ccBase = &chatBox->chatContainer->base;
    djui_base_set_size(ccBase, 1.0f, chatBox->base.comp.height - 32 - 8);
    if (sDjuiChatBoxClearText) {
        sDjuiChatBoxClearText = false;
        djui_inputbox_set_text(gDjuiChatBox->chatInput, "");
        djui_inputbox_select_all(gDjuiChatBox->chatInput);
    }
    return true;
}

static void djui_chat_box_destroy(struct DjuiBase* base) {
    struct DjuiChatBox* chatBox = (struct DjuiChatBox*)base;
    free(chatBox);
}

static void djui_chat_box_set_focus_style(void) {
    djui_base_set_visible(&gDjuiChatBox->chatInput->base, gDjuiChatBoxFocus);
    if (gDjuiChatBoxFocus) {
        djui_interactable_set_input_focus(&gDjuiChatBox->chatInput->base);
    }

    djui_base_set_color(&gDjuiChatBox->chatFlow->base, 0, 0, 0, gDjuiChatBoxFocus ? 128 : 0);
}

static void djui_chat_box_input_enter(struct DjuiInputbox* chatInput) {
    djui_interactable_set_input_focus(NULL);

    if (strlen(chatInput->buffer) != 0) {
        sent_history_add_message(&sentHistory, chatInput->buffer);
        if (chatInput->buffer[0] == '/') {
            if (strcmp(chatInput->buffer, "/help") == 0 || strcmp(chatInput->buffer, "/?") == 0 || strcmp(chatInput->buffer, "/") == 0) {
                display_chat_commands();
            } else if (!exec_chat_command(chatInput->buffer)) {
                char extendedUnknownCommandMessage[MAX_CHAT_MSG_LENGTH];
                snprintf(extendedUnknownCommandMessage, sizeof(extendedUnknownCommandMessage), "%s (/help)", DLANG(CHAT, UNRECOGNIZED));
                djui_chat_message_create(extendedUnknownCommandMessage);
            }
        } else {
            djui_chat_message_create_from(gNetworkPlayerLocal->globalIndex, chatInput->buffer);
            network_send_chat(chatInput->buffer, gNetworkPlayerLocal->globalIndex);
        }
    }

    djui_inputbox_set_text(chatInput, "");
    djui_inputbox_select_all(chatInput);
    if (gDjuiChatBoxFocus) { djui_chat_box_toggle(); }
}

static void djui_chat_box_input_escape(struct DjuiInputbox* chatInput) {
    djui_interactable_set_input_focus(NULL);
    djui_inputbox_set_text(chatInput, "");
    djui_inputbox_select_all(chatInput);
    if (gDjuiChatBoxFocus) { djui_chat_box_toggle(); }
}

static char* get_main_command_from_input(const char* input) {
    char* spacePos = strrchr(input, ' ');
    if (spacePos == NULL) {
        return NULL;
    }
    size_t len = spacePos - input;
    char* command = (char*) malloc(len + 1);
    snprintf(command, len + 1, "%s", input);
    command[len] = '\0';
    return command;
}

static bool complete_subcommand(const char* mainCommand, const char* subCommandPrefix) {
    char** subcommands = smlua_get_chat_subcommands_list(mainCommand);

    if (!subcommands || !subcommands[0]) {
        return false;
    }

    s32 foundSubCommandsCount = 0;
    for (s32 i = 0; subcommands[i] != NULL; i++) {
        if (strncmp(subcommands[i], subCommandPrefix, strlen(subCommandPrefix)) == 0) {
            foundSubCommandsCount++;
        }
    }

    bool completionSuccess = false;
    if (foundSubCommandsCount > 0) {
        sCommandsTabCompletionIndex = (sCommandsTabCompletionIndex + 1) % foundSubCommandsCount;
        s32 currentIndex = 0;

        for (s32 i = 0; subcommands[i] != NULL; i++) {
            if (strncmp(subcommands[i], subCommandPrefix, strlen(subCommandPrefix)) == 0) {
                if (currentIndex == sCommandsTabCompletionIndex) {
                    char completion[MAX_CHAT_MSG_LENGTH];
                    snprintf(completion, MAX_CHAT_MSG_LENGTH, "/%s %s", mainCommand, subcommands[i]);
                    djui_inputbox_set_text(gDjuiChatBox->chatInput, completion);
                    djui_inputbox_move_cursor_to_end(gDjuiChatBox->chatInput);
                    completionSuccess = true;
                    break;
                }
                currentIndex++;
            }
        }
    }

    for (s32 i = 0; subcommands[i] != NULL; i++) {
        free(subcommands[i]);
    }
    free(subcommands);

    return completionSuccess;
}

typedef struct {
    char word[MAX_CHAT_MSG_LENGTH];
    s32 index;
} CurrentWordInfo;

CurrentWordInfo get_current_word_info(char* buffer, s32 position) {
    CurrentWordInfo info;
    memset(info.word, 0, MAX_CHAT_MSG_LENGTH);
    info.index = -1;

    s32 currentWordStart = position;
    s32 currentWordEnd = position;

    while (currentWordStart > 0 && buffer[currentWordStart - 1] != ' ') {
        currentWordStart--;
    }

    while (buffer[currentWordEnd] != '\0' && buffer[currentWordEnd] != ' ') {
        currentWordEnd++;
    }

    s32 wordLength = currentWordEnd - currentWordStart;
    if (wordLength > MAX_CHAT_MSG_LENGTH - 1) {
        wordLength = MAX_CHAT_MSG_LENGTH - 1;
    }

    snprintf(info.word, wordLength + 1, "%.*s", wordLength, &buffer[currentWordStart]);

    s32 wordCount = 0;
    for (s32 i = 0; i <= currentWordStart; i++) {
        if (buffer[i] == ' ' || i == 0) {
            wordCount++;
        }
    }
    info.index = wordCount;

    return info;
}

void djui_inputbox_replace_current_word(struct DjuiInputbox* inputbox, char* text) {
    if (!inputbox || !text) { return; }

    s32 currentWordStart = inputbox->selection[0];
    s32 currentWordEnd = inputbox->selection[0];

    while (currentWordStart > 0 && inputbox->buffer[currentWordStart - 1] != ' ') { currentWordStart--; }
    while (inputbox->buffer[currentWordEnd] != '\0' && inputbox->buffer[currentWordEnd] != ' ') { currentWordEnd++; }

    char newBuffer[MAX_CHAT_MSG_LENGTH];
    snprintf(newBuffer, MAX_CHAT_MSG_LENGTH, "%.*s%s%s", currentWordStart, inputbox->buffer, text, &inputbox->buffer[currentWordEnd]);

    djui_inputbox_set_text(inputbox, newBuffer);
    djui_inputbox_move_cursor_to_position(inputbox, currentWordStart + strlen(text));
}

static bool complete_player_name(const char* namePrefix) {
    char** playerNames = smlua_get_chat_player_list();
    if (!playerNames || !playerNames[0]) {
        if (playerNames) {
            free(playerNames);
        }
        return false;
    }

    s32 foundNamesCount = 0;
    for (s32 i = 0; playerNames[i] != NULL; i++) {
        if (strncmp(playerNames[i], namePrefix, strlen(namePrefix)) == 0) {
            foundNamesCount++;
        }
    }

    bool completionSuccess = false;
    if (foundNamesCount > 0) {
        sPlayersTabCompletionIndex = (sPlayersTabCompletionIndex + 1) % foundNamesCount;
        s32 currentIndex = 0;

        for (s32 i = 0; playerNames[i] != NULL; i++) {
            if (strncmp(playerNames[i], namePrefix, strlen(namePrefix)) == 0) {
                if (currentIndex == sPlayersTabCompletionIndex) {
                    djui_inputbox_replace_current_word(gDjuiChatBox->chatInput, playerNames[i]);
                    completionSuccess = true;
                    break;
                }
                currentIndex++;
            }
        }
    }

    for (s32 i = 0; playerNames[i] != NULL; i++) {
        free(playerNames[i]);
    }
    free(playerNames);

    return completionSuccess;
}

static void handle_tab_completion(void) {
    bool alreadyTabCompleted = false;
    if (gDjuiChatBox->chatInput->buffer[0] == '/') {
        char* spacePosition = strrchr(sCommandsTabCompletionOriginalText, ' ');
        if (spacePosition != NULL) {
            char* mainCommand = get_main_command_from_input(sCommandsTabCompletionOriginalText);
            if (mainCommand) {
                if (!complete_subcommand(mainCommand + 1, spacePosition + 1)) {
                    reset_tab_completion_all();
                } else {
                    alreadyTabCompleted = true;
                }
                free(mainCommand);
            }
        } else {
            if (sCommandsTabCompletionIndex == -1) {
                snprintf(sCommandsTabCompletionOriginalText, MAX_CHAT_MSG_LENGTH, "%s", gDjuiChatBox->chatInput->buffer);
            }

            char* bufferWithoutSlash = sCommandsTabCompletionOriginalText + 1;
            char** commands = smlua_get_chat_maincommands_list();
            s32 foundCommandsCount = 0;

            for (s32 i = 0; commands[i] != NULL; i++) {
                if (strncmp(commands[i], bufferWithoutSlash, strlen(bufferWithoutSlash)) == 0) {
                    foundCommandsCount++;
                }
            }

            if (foundCommandsCount > 0) {
                sCommandsTabCompletionIndex = (sCommandsTabCompletionIndex + 1) % foundCommandsCount;
                s32 currentIndex = 0;

                for (s32 i = 0; commands[i] != NULL; i++) {
                    if (strncmp(commands[i], bufferWithoutSlash, strlen(bufferWithoutSlash)) == 0) {
                        if (currentIndex == sCommandsTabCompletionIndex) {
                            char completion[MAX_CHAT_MSG_LENGTH];
                            snprintf(completion, MAX_CHAT_MSG_LENGTH, "/%s", commands[i]);
                            djui_inputbox_set_text(gDjuiChatBox->chatInput, completion);
                            djui_inputbox_move_cursor_to_end(gDjuiChatBox->chatInput);
                            alreadyTabCompleted = true;
                        }
                        currentIndex++;
                    }
                }
            } else {
                char* spacePositionB = strrchr(sCommandsTabCompletionOriginalText, ' ');
                if (spacePositionB != NULL) {
                    char* mainCommandB = get_main_command_from_input(sCommandsTabCompletionOriginalText);
                    if (mainCommandB) {
                        if (!complete_subcommand(mainCommandB + 1, spacePositionB + 1)) {
                            reset_tab_completion_all();
                        } else {
                            alreadyTabCompleted = true;
                        }
                        free(mainCommandB);
                    }
                }
            }

            for (s32 i = 0; commands[i] != NULL; i++) {
                free(commands[i]);
            }
            free(commands);
        }
    }
    if (!alreadyTabCompleted) {
        if (gDjuiChatBox->chatInput->selection[0] != gDjuiChatBox->chatInput->selection[1]) {
            alreadyTabCompleted = true;
        }
    }
    if (!alreadyTabCompleted) {
        CurrentWordInfo wordCurrent = get_current_word_info(gDjuiChatBox->chatInput->buffer, gDjuiChatBox->chatInput->selection[0]);
        if (gDjuiChatBox->chatInput->buffer[0] == '/') {
            if (wordCurrent.index == 1 && smlua_maincommand_exists(wordCurrent.word + 1)) {
                alreadyTabCompleted = true;
            } else if (wordCurrent.index == 2) {
                CurrentWordInfo worldMainCommand = get_current_word_info(gDjuiChatBox->chatInput->buffer, 0);
                if (smlua_maincommand_exists(worldMainCommand.word + 1) && smlua_subcommand_exists(worldMainCommand.word + 1, wordCurrent.word)) {
                    alreadyTabCompleted = true;
                }
            }
        }
    }
    if (!alreadyTabCompleted) {
        CurrentWordInfo wordInfo = get_current_word_info(gDjuiChatBox->chatInput->buffer, gDjuiChatBox->chatInput->selection[0]);
        if (wordInfo.index != -1) {
            if (sPlayersTabCompletionIndex == -1) {
                snprintf(sPlayersTabCompletionOriginalText, MAX_CHAT_MSG_LENGTH, "%s", wordInfo.word);
            }
            if (!complete_player_name(sPlayersTabCompletionOriginalText)) {
                reset_tab_completion_players();
            } else {
                alreadyTabCompleted = true;
            }
        }
    }
}

static bool djui_chat_box_input_on_key_down(struct DjuiBase* base, int scancode) {
    sent_history_init(&sentHistory);

    if (gDjuiChatBox == NULL) { return false; }
    f32 yMax = gDjuiChatBox->chatContainer->base.elem.height - gDjuiChatBox->chatFlow->base.height.value;

    f32* yValue = &gDjuiChatBox->chatFlow->base.y.value;
    bool canScrollUp   = (*yValue > yMax);
    bool canScrollDown = (*yValue < 0);
    f32 pageAmount = gDjuiChatBox->chatContainer->base.elem.height * 3.0f / 4.0f;

    char previousText[MAX_CHAT_MSG_LENGTH];
    snprintf(previousText, MAX_CHAT_MSG_LENGTH, "%s", gDjuiChatBox->chatInput->buffer);

    switch (scancode) {
        case SCANCODE_UP:
            if (!configUseStandardKeyBindingsChat && (gDjuiChatBox->chatInput && gDjuiChatBox->chatInput->buffer && gDjuiChatBox->chatInput->buffer[0] != '/')) {
                gDjuiChatBox->scrolling = true;
                if (canScrollDown) { *yValue = fmin(*yValue + 15, 0); }
            } else {
                sent_history_update_current_message(&sentHistory, gDjuiChatBox->chatInput->buffer);
                sent_history_navigate(&sentHistory, true);
                if (strcmp(previousText, gDjuiChatBox->chatInput->buffer) != 0) { reset_tab_completion_all(); }
            }
            return true;
        case SCANCODE_DOWN:
            if (!configUseStandardKeyBindingsChat && (gDjuiChatBox->chatInput && gDjuiChatBox->chatInput->buffer && gDjuiChatBox->chatInput->buffer[0] != '/')) {
                gDjuiChatBox->scrolling = true;
                if (canScrollUp) { *yValue = fmax(*yValue - 15, yMax); }
            } else {
                sent_history_update_current_message(&sentHistory, gDjuiChatBox->chatInput->buffer);
                sent_history_navigate(&sentHistory, false);
                if (strcmp(previousText, gDjuiChatBox->chatInput->buffer) != 0) { reset_tab_completion_all(); }
            }
            return true;
        case SCANCODE_PAGE_UP:
            gDjuiChatBox->scrolling = true;
            if (canScrollDown) {
                if (configUseStandardKeyBindingsChat) {
                    *yValue = fmin(*yValue + 15, 0);
                } else {
                    *yValue = fmin(*yValue + pageAmount, 0);
                }
            }
            return true;
        case SCANCODE_PAGE_DOWN:
            gDjuiChatBox->scrolling = true;
            if (canScrollUp) {
                if (configUseStandardKeyBindingsChat) {
                    *yValue = fmax(*yValue - 15, yMax);
                } else {
                    *yValue = fmax(*yValue - pageAmount, yMax);
                }
            }
            return true;
        case SCANCODE_POS1:
            gDjuiChatBox->scrolling = true;
            if (canScrollDown) { *yValue = fmin(*yValue + pageAmount, 0); }
            return true;
        case SCANCODE_END:
            gDjuiChatBox->scrolling = true;
            if (canScrollUp) { *yValue = fmax(*yValue - pageAmount, yMax); }
            return true;
        case SCANCODE_TAB:
            handle_tab_completion();
            return true;
        case SCANCODE_ENTER:
            reset_tab_completion_all();
            sent_history_reset_navigation(&sentHistory);
            djui_chat_box_input_enter(gDjuiChatBox->chatInput);
            return true;
        case SCANCODE_ESCAPE:
            reset_tab_completion_all();
            sent_history_reset_navigation(&sentHistory);
            djui_chat_box_input_escape(gDjuiChatBox->chatInput);
            return true;
        default:
            {
                bool returnValueOnOtherKeyDown = djui_inputbox_on_key_down(base, scancode);
                if (strcmp(previousText, gDjuiChatBox->chatInput->buffer) != 0) {
                    reset_tab_completion_all();
                }
                return returnValueOnOtherKeyDown;
            }
    }
}

static void djui_chat_box_input_on_text_input(struct DjuiBase *base, char* text) {
    size_t expectedIndex = strlen(gDjuiChatBox->chatInput->buffer);
    bool isTextDifferent = (expectedIndex >= MAX_CHAT_MSG_LENGTH) || (gDjuiChatBox->chatInput->buffer[expectedIndex] != text[0]);
    djui_inputbox_on_text_input(base, text);
    if (isTextDifferent) {
        reset_tab_completion_all();
    }
}

static void djui_chat_box_input_on_text_editing(struct DjuiBase *base, char* text, int cursorPos) {
    djui_inputbox_on_text_editing(base, text, cursorPos);
}

void djui_chat_box_toggle(void) {
    if (gDjuiChatBox == NULL) { return; }
    if (!gDjuiChatBoxFocus) { sDjuiChatBoxClearText = true; }
    gDjuiChatBoxFocus = !gDjuiChatBoxFocus;
    djui_chat_box_set_focus_style();
    gDjuiChatBox->scrolling = false;
    gDjuiChatBox->chatFlow->base.y.value = gDjuiChatBox->chatContainer->base.elem.height - gDjuiChatBox->chatFlow->base.height.value;
}

struct DjuiChatBox* djui_chat_box_create(void) {
    if (gDjuiChatBox != NULL) {
        djui_base_destroy(&gDjuiChatBox->base);
        gDjuiChatBox = NULL;
    }

    struct DjuiChatBox* chatBox = calloc(1, sizeof(struct DjuiChatBox));
    struct DjuiBase* base = &chatBox->base;

    djui_base_init(&gDjuiRoot->base, base, djui_chat_box_render, djui_chat_box_destroy);
    djui_base_set_size_type(base, DJUI_SVT_ABSOLUTE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(base, 600, 400);
    djui_base_set_alignment(base, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);
    djui_base_set_color(base, 0, 0, 0, 0);
    djui_base_set_padding(base, 0, 8, 8, 8);

    struct DjuiRect* chatContainer = djui_rect_create(base);
    struct DjuiBase* ccBase = &chatContainer->base;
    djui_base_set_size_type(ccBase, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(ccBase, 1.0f, 0);
    djui_base_set_color(ccBase, 0, 0, 0, 0);
    chatBox->chatContainer = chatContainer;

    struct DjuiFlowLayout* chatFlow = djui_flow_layout_create(ccBase);
    struct DjuiBase* cfBase = &chatFlow->base;
    djui_base_set_location(cfBase, 0, 0);
    djui_base_set_size_type(cfBase, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(cfBase, 1.0f, 2);
    djui_base_set_color(cfBase, 0, 0, 0, 128);
    djui_base_set_padding(cfBase, 2, 2, 2, 2);
    djui_flow_layout_set_margin(chatFlow, 2);
    djui_flow_layout_set_flow_direction(chatFlow, DJUI_FLOW_DIR_UP);
    cfBase->addChildrenToHead = true;
    cfBase->abandonAfterChildRenderFail = true;
    chatBox->chatFlow = chatFlow;

    struct DjuiInputbox* chatInput = djui_inputbox_create(base, MAX_CHAT_MSG_LENGTH);
    struct DjuiBase* ciBase = &chatInput->base;
    djui_base_set_size_type(ciBase, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
    djui_base_set_size(ciBase, 1.0f, 32);
    djui_base_set_alignment(ciBase, DJUI_HALIGN_LEFT, DJUI_VALIGN_BOTTOM);
    djui_interactable_hook_key(&chatInput->base, djui_chat_box_input_on_key_down, djui_inputbox_on_key_up);
    djui_interactable_hook_text_input(&chatInput->base, djui_chat_box_input_on_text_input);
    djui_interactable_hook_text_editing(&chatInput->base, djui_chat_box_input_on_text_editing);
    chatBox->chatInput = chatInput;

    gDjuiChatBox = chatBox;
    djui_chat_box_set_focus_style();
    return chatBox;
}