#include "djui.h"
#include "djui_panel.h"
#include "djui_panel_menu.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"
#include "pc/lua/utils/smlua_audio_utils.h"
#include "game/sound_init.h"

static void djui_panel_sound_value_change(UNUSED struct DjuiBase* caller) {
    audio_custom_update_volume();
}

static void djui_panel_sound_output_change(UNUSED struct DjuiBase* caller) {
    set_sound_mode(configSoundOutput);
}

void djui_panel_sound_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(SOUND, SOUND), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
        char* outputChoices[3] = { DLANG(SOUND, STEREO), DLANG(SOUND, MONO), DLANG(SOUND, HEADSET) };
        djui_selectionbox_create(body, DLANG(SOUND, SOUND_OUTPUT), outputChoices, 3, &configSoundOutput, djui_panel_sound_output_change);

        djui_slider_create(body, DLANG(SOUND, MASTER_VOLUME), &configMasterVolume, 0, 127, djui_panel_sound_value_change);
        djui_slider_create(body, DLANG(SOUND, MUSIC_VOLUME), &configMusicVolume, 0, 127, djui_panel_sound_value_change);
        djui_slider_create(body, DLANG(SOUND, SFX_VOLUME), &configSfxVolume, 0, 127, djui_panel_sound_value_change);
        djui_slider_create(body, DLANG(SOUND, ENV_VOLUME), &configEnvVolume, 0, 127, djui_panel_sound_value_change);

        djui_checkbox_create(body, DLANG(SOUND, FADEOUT), &configFadeoutDistantSounds, NULL);
        djui_checkbox_create(body, DLANG(SOUND, MUTE_FOCUS_LOSS), &configMuteFocusLoss, NULL);

        djui_button_create(body, DLANG(MENU, BACK), DJUI_BUTTON_STYLE_BACK, djui_panel_menu_back);
    }

    djui_panel_add(caller, panel, NULL);
}
