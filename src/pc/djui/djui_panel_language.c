#include <stdio.h>
#include <string.h>

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
#include "pc/os/os.h"

extern bool directory_sanity_check(struct dirent* dir, char* dirPath, char* outPath);
static bool sTrue = true;
static bool sFalse = false;
static bool sLanguageChanged = false;
static struct DjuiBase* sLayoutBase = NULL;
bool gPanelLanguageOnStartup = false;

// HACK: this is abysmal, replace soon or god so help me
static const char* lang_native_name(const char* lang_name) {
    if (!strcmp(lang_name, "German")) return "Deutsch";
    else if (!strcmp(lang_name, "Czech")) return "čeština";
    else if (!strcmp(lang_name, "Dutch")) return "Nederlands";
    else if (!strcmp(lang_name, "French")) return "Français";
    else if (!strcmp(lang_name, "Italian")) return "Italiano";
    else if (!strcmp(lang_name, "Polish")) return "język polski";
    else if (!strcmp(lang_name, "Portuguese")) return "português";
    else if (!strcmp(lang_name, "Russian")) return "русский";
    else if (!strcmp(lang_name, "Spanish")) return "Español";

    return lang_name;
}

// HACK: you thought the above func was bad? Well this is even fucking worse
static const char* lang_native_to_orig(const char* lang_name) {
    if (!strcmp(lang_name, "Deutsch (German)")) return "German";
    else if (!strcmp(lang_name, "čeština (Czech)")) return "Czech";
    else if (!strcmp(lang_name, "Nederlands (Dutch)")) return "Dutch";
    else if (!strcmp(lang_name, "Français (French)")) return "French";
    else if (!strcmp(lang_name, "Italiano (Italian)")) return "Italian";
    else if (!strcmp(lang_name, "język polski (Polish)")) return "Polish";
    else if (!strcmp(lang_name, "português (Portuguese)")) return "Portuguese";
    else if (!strcmp(lang_name, "русский (Russian)")) return "Russian";
    else if (!strcmp(lang_name, "Español (Spanish)")) return "Spanish";

    return lang_name;
}

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

    const char* orig_text = lang_native_to_orig(checkbox->text->message);

    if (strcmp(configLanguage, orig_text)) {
        snprintf(configLanguage, MAX_CONFIG_STRING, "%s", orig_text);
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
        // construct lang path
        char lpath[SYS_MAX_PATH] = "";
        snprintf(lpath, SYS_MAX_PATH, "%s/lang", sys_exe_path());

        // open directory
        os_dirent* dir = NULL;

        OS_DIR* d = os_opendir(lpath);
        if (!d) {
            LOG_ERROR("Could not open directory '%s'", lpath);

            char buffer[512] = "";
            sys_swap_backslashes(lpath);
            snprintf(buffer, 512, "\\#ffa0a0\\Failed to load language folder:\n\\#dcdcdc\\%s", lpath);
            struct DjuiText* text = djui_text_create(body, buffer);
            djui_text_set_alignment(text, DJUI_HALIGN_CENTER, DJUI_VALIGN_CENTER);
            djui_base_set_size_type(&text->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&text->base, 1.0f, 128.0f);

            goto skip_langs;
        }

        struct DjuiPaginated* paginated = djui_paginated_create(body, 8);
        sLayoutBase = &paginated->layout->base;

        struct DjuiCheckbox* chkEnglish = NULL;
        bool foundMatch = false;

        // iterate
        char path[SYS_MAX_PATH] = { 0 };
        while ((dir = os_readdir(d)) != NULL) {
            // sanity check / fill path[]
            //if (!directory_sanity_check(dir, lpath, path)) { continue; }
            snprintf(path, SYS_MAX_PATH, "%s", os_get_dir_name(dir));

            // strip the name before the .
            char* c = path;
            while (*c != '\0') {
                if (*c == '.') { *c = '\0'; break; }
                c++;
            }
            if (strlen(path) == 0) { continue; }

            char* fmtPath;

            // This is actually shit but it works
            if (strcmp(path, "English") != 0) asprintf(&fmtPath, "%s (%s)", lang_native_name(path), path);
            else asprintf(&fmtPath, "%s", path);

            bool match = !strcmp(path, configLanguage);
            if (match) { foundMatch = true; }
            struct DjuiCheckbox* checkbox = djui_checkbox_create(sLayoutBase, fmtPath, match ? &sTrue : &sFalse, select_language);
            if (!strcmp(path, "English")) { chkEnglish = checkbox; }

            free(fmtPath);
        }

        os_closedir(d);

        if (!foundMatch && chkEnglish) {
            chkEnglish->value = &sTrue;
            chkEnglish->base.interactable->update_style(&chkEnglish->base);
        }

        djui_paginated_calculate_height(paginated);
        panel->bodySize.value = paginated->base.height.value + 16 + 64;

skip_langs:
        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);

    }

    struct DjuiPanel* p = djui_panel_add(caller, panel, NULL);
    p->on_panel_destroy = djui_panel_language_destroy;

}
