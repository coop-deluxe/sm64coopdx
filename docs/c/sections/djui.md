## [:rewind: C Reference](../c.md)

# DJUI

DJUI, or djoslin0 User Interface, is a custom UI framework for making panels, buttons, and other elements easy to work with.

## How it works

Before we get into a list of elements, first we need to clear something up:

- The DJUI found in Lua is not necessarily the same you will be working with in C. Lua is much more barebones, whereas C mainly uses panels. This documentation does not apply to Lua.

Now getting back on track, DJUI panels and elements aren't used directly, they're used via DJUI functions. There's quite the list of them, with each element having it's own unique list of functions if necessary. Thankfully, DJUI removes a lot of headache by unifying all elements to contain a `DjuiBase`.

Every DJUI element has a `DjuiBase`. This base contains properties such as the width, height, position, anchor, color, and more. You can configure a base with it's list of functions. A list of functions can be found in `djui_base.h`, which is found in `src/pc/djui`, along with all the other DJUI files, you'll see this functions pop up.

There's a few key constants to keep in mind.

- `DjuiScreenValueType` is a size type. You can make it relative, `DJUI_SVT_RELATIVE`, so a multiplier of the parent's size, or absolute, `DJUI_SVT_ABSOLUTE`, so it's the pixel size set.
- `DjuiHAlign` and `DjuiVAlign`, which is the alignment of a base.

```c
enum DjuiScreenValueType { DJUI_SVT_ABSOLUTE, DJUI_SVT_RELATIVE, DJUI_SVT_ASPECT_RATIO };
enum DjuiHAlign { DJUI_HALIGN_LEFT, DJUI_HALIGN_CENTER, DJUI_HALIGN_RIGHT };
enum DjuiVAlign { DJUI_VALIGN_TOP, DJUI_VALIGN_CENTER, DJUI_VALIGN_BOTTOM };
```

## DJUI Elements

Working with DJUI elements is easy. Let's take `DjuiText` as an example.

```c
struct DjuiText {
    struct DjuiBase base;
    char* message;
    const struct DjuiFont* font;
    f32 fontScale;
    struct DjuiColor dropShadow;
    enum DjuiHAlign textHAlign;
    enum DjuiVAlign textVAlign;
};
```

Every DJUI element always has a `DjuiBase`, and it's always the first field of the element. In this element there are multiple custom options, but most of it is still configured with functions.

```c
...
void djui_text_set_text(struct DjuiText* text, const char* message);
void djui_text_set_font(struct DjuiText* text, const struct DjuiFont* font);
void djui_text_set_font_scale(struct DjuiText* text, f32 fontScale);
void djui_text_set_drop_shadow(struct DjuiText* text, f32 r, f32 g, f32 b, f32 a);
void djui_text_set_alignment(struct DjuiText* text, enum DjuiHAlign hAlign, enum DjuiVAlign vAlign);
...
struct DjuiText* djui_text_create(struct DjuiBase* parent, const char* message);
```

I didn't show all the functions, but as you can see an element can have quite the amount of functions to configure itself.

Each element has a dedicated creation function. For text, it's `djui_text_create`. A create function allocates memory for the element and adds it's base as a child of the base it was created from. Parent and children management is done through bases. All create functions take in a parent, along with element specific parameters.

Let's analyze one of these panels.

```c
static void djui_panel_sound_value_change(UNUSED struct DjuiBase* caller) {
    audio_custom_update_volume();
}

void djui_panel_sound_create(struct DjuiBase* caller) {
    struct DjuiThreePanel* panel = djui_panel_menu_create(DLANG(SOUND, SOUND), false);
    struct DjuiBase* body = djui_three_panel_get_body(panel);
    {
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
```

Let's look at the `djui_panel_sound_create`.

- First, a three panel is created by using the `djui_panel_menu_create` function. This is a custom create function specifically designed for creating panels in the main menu or the pause menu. Not all panels require it, some use `djui_three_panel_create`, which is the original panel create function.
- `DjuiThreePanel` is a panel containing 3 sections, the header, the body, and the footer. Most of the time the footer is unused, but the header and body are almost always used.
- We get the body that is created from the three panel using the `djui_three_panel_get_body` function. This gets the body section of the three panel.
- Multiple different elements are created.
- `djui_slider_create` takes in it's parent, the name of the slider, a reference to the value (unsigned int) so it can be changed, which typically points to somewhere in the config, the ranges, so a minimum range and a maximum range, and a function for what happens when it's changed.
- The on change functions can always be `NULL`, but they are very useful. In this scenario, `djui_panel_sound_value_change` is called, which calls `audio_custom_update_volume`, so the volume is updated to match the slider.
- `DLANG` is the language system, it takes in a header key and a normal key. You can see a list of language keys and values in `lang/English.ini`, or any language of your choosing.
- `djui_checkbox_create` takes in it's parent, the name of the checkbox, a reference to a boolean, and an on change function call.
- As you can see, the on change function call is set to `NULL`, since there's no need for one.
- `djui_button_create` takes in it's parent, a name, the style of the button, and a on press function.
- To add a panel to the pause menu the `djui_panel_add` function is used, the caller being the previous panel, panel being the current panel, and the last argument being the base that the cursor should go to by default.

This gets a lot of the basics out of the way, but you can configure a base even more using the base functions. Let's go over some important flow elements.

### Flow Layout

`DjuiFlowLayout` allows you to decide how new elements are added. It's actually used by the panel created using `djui_panel_menu_create` internally. A flow layout handles margins, and decides how elements flow. You can have elements flow up, down, left, right, any direction, and you can define the exact size of the margin.

```c
enum DjuiFlowDirection { DJUI_FLOW_DIR_DOWN, DJUI_FLOW_DIR_UP, DJUI_FLOW_DIR_RIGHT, DJUI_FLOW_DIR_LEFT };

void djui_flow_layout_set_flow_direction(struct DjuiFlowLayout* layout, enum DjuiFlowDirection flowDirection);
void djui_flow_layout_set_margin(struct DjuiFlowLayout* layout, f32 margin);
void djui_flow_layout_set_margin_type(struct DjuiFlowLayout* layout, enum DjuiScreenValueType marginType);

struct DjuiFlowLayout* djui_flow_layout_create(struct DjuiBase* parent);
```

You can configure it's size and position via it's base, like any other element.

When configuring children inside the flow layout, if you scale the base by the relative, only the amount of space currently available is up for sale. So if you create 2 side by side in a flow layout, you would need to calculate it expecting that room not being available. So the first button would take up half the space, or 0.5, and then the next button would need to take up the rest of that space, or 1.0.

### Rect Container

A rect container is just an invisible `DjuiRect`. It's just an empty container, so unlike a flow layout, it's children need to behave, and it doesn't hold your hand. The space is not shared between them, so if you use a relative size and tell 2 buttons to use half the space, the full space will be used.