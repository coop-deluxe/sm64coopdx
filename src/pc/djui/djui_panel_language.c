#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "djui_panel_main.h"
#include "djui_panel_options.h"
#include "djui_panel_misc.h"
#include "djui_panel_pause.h"
#include "pc/debuglog.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"

extern bool directory_sanity_check(struct dirent* dir, char* dirPath, char* outPath);
static bool sTrue = true;
static bool sFalse = false;
static bool sLanguageChanged = false;
static struct DjuiBase* sLayoutBase = NULL;
bool gPanelLanguageOnStartup = false;

static void select_language(struct DjuiBase* caller) {
    // god this is so hacky and terrible
    struct DjuiCheckbox* checkbox = (struct DjuiCheckbox*) caller;
    sTrue = true;
    sFalse = false;

    struct DjuiBaseChild* child = sLayoutBase->child;
    while (child) {
        struct DjuiCheckbox* tmp = (struct DjuiCheckbox*)child->base;
        tmp->value = &sFalse;
        tmp->base.interactable->update_style(&tmp->base);
        child = child->next;
    }

    if (strcmp(configLanguage, checkbox->text->message)) {
        snprintf(configLanguage, MAX_CONFIG_STRING, "%s", checkbox->text->message);
        sLanguageChanged = true;
    }

    checkbox->value = &sTrue;
    checkbox->base.interactable->update_style(caller);
}

static void djui_panel_language_destroy(UNUSED struct DjuiBase* caller) {
    // god this is so hacky and terrible
    if (sLanguageChanged) {
        sLanguageChanged = false;
        if (!djui_language_init(configLanguage)) {
            snprintf(configLanguage, MAX_CONFIG_STRING, "%s", "");
        }

        if (gPanelLanguageOnStartup) {
            djui_panel_shutdown();
            gDjuiInMainMenu = true;
            djui_panel_main_create(NULL);
        } else if (gDjuiInMainMenu) {
            djui_panel_shutdown();
            gDjuiInMainMenu = true;
            djui_panel_main_create(NULL);
            djui_panel_options_create(NULL);
            djui_panel_misc_create(NULL);
        } else if (gDjuiPanelPauseCreated) {
            djui_panel_shutdown();
            djui_panel_pause_create(NULL);
            djui_panel_options_create(NULL);
            djui_panel_misc_create(NULL);
        } else {
            djui_panel_shutdown();
        }
    }
    if (configLanguage[0] == '\0') {
        snprintf(configLanguage, MAX_CONFIG_STRING, "%s", "English");
    }
    gPanelLanguageOnStartup = false;
}

void djui_panel_language_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(LANGUAGE, LANGUAGE));
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    sLanguageChanged = false;

    {
        struct DjuiPaginated* paginated = djui_paginated_create(body, 8);
        sLayoutBase = &paginated->layout->base;

        // construct lang path
        char lpath[SYS_MAX_PATH] = "";
        snprintf(lpath, SYS_MAX_PATH, "%s/lang", sys_exe_path());

        // open directory
        struct dirent* dir = NULL;
        DIR* d = opendir(lpath);
        if (!d) {
            LOG_ERROR("Could not open directory '%s'", lpath);
            return;
        }

        struct DjuiCheckbox* chkEnglish = NULL;
        bool foundMatch = false;

        // iterate
        char path[SYS_MAX_PATH] = { 0 };
        while ((dir = readdir(d)) != NULL) {
            // sanity check / fill path[]
            if (!directory_sanity_check(dir, lpath, path)) { continue; }
            snprintf(path, SYS_MAX_PATH, "%s", dir->d_name);

            // strip the name before the .
            char* c = path;
            while (*c != '\0') {
                if (*c == '.') { *c = '\0'; break;}
                c++;
            }
            if (strlen(path) == 0) { continue; }

            bool match = !strcmp(path, configLanguage);
            if (match) { foundMatch = true; }
            struct DjuiCheckbox* checkbox = djui_checkbox_create(sLayoutBase, path, match ? &sTrue : &sFalse, select_language);
            if (!strcmp(path, "English")) { chkEnglish = checkbox; }
        }

        closedir(d);

        if (!foundMatch && chkEnglish) {
            chkEnglish->value = &sTrue;
            chkEnglish->base.interactable->update_style(&chkEnglish->base);
        }

        djui_paginated_calculate_height(paginated);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);

        panel->bodySize.value = paginated->base.height.value + 16 + 64;
    }

    struct DjuiPanel* p = djui_panel_add(caller, panel, NULL);
    p->on_panel_destroy = djui_panel_language_destroy;
}
