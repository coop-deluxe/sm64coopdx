#include "pc/rom_assets.h"
#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "config.h"
#include "macros.h"
#include "types.h"
#include "game/ingame_menu.h"

#include "make_const_nonconst.h"

// SM64 (US/JP/EU/SH) Segment 02

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_0, "textures/segment2/segment2.00000.rgba16.inc.c", 0x00108a40, 48390, 0x00000000, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_1, "textures/segment2/segment2.00200.rgba16.inc.c", 0x00108a40, 48390, 0x00000200, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_2, "textures/segment2/segment2.00400.rgba16.inc.c", 0x00108a40, 48390, 0x00000400, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_3, "textures/segment2/segment2.00600.rgba16.inc.c", 0x00108a40, 48390, 0x00000600, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_4, "textures/segment2/segment2.00800.rgba16.inc.c", 0x00108a40, 48390, 0x00000800, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_5, "textures/segment2/segment2.00A00.rgba16.inc.c", 0x00108a40, 48390, 0x00000a00, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_6, "textures/segment2/segment2.00C00.rgba16.inc.c", 0x00108a40, 48390, 0x00000c00, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_7, "textures/segment2/segment2.00E00.rgba16.inc.c", 0x00108a40, 48390, 0x00000e00, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_8, "textures/segment2/segment2.01000.rgba16.inc.c", 0x00108a40, 48390, 0x00001000, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_9, "textures/segment2/segment2.01200.rgba16.inc.c", 0x00108a40, 48390, 0x00001200, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_A, "textures/segment2/segment2.01400.rgba16.inc.c", 0x00108a40, 48390, 0x00001400, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_B, "textures/segment2/segment2.01600.rgba16.inc.c", 0x00108a40, 48390, 0x00001600, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_C, "textures/segment2/segment2.01800.rgba16.inc.c", 0x00108a40, 48390, 0x00001800, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_D, "textures/segment2/segment2.01A00.rgba16.inc.c", 0x00108a40, 48390, 0x00001a00, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_E, "textures/segment2/segment2.01C00.rgba16.inc.c", 0x00108a40, 48390, 0x00001c00, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_F, "textures/segment2/segment2.01E00.rgba16.inc.c", 0x00108a40, 48390, 0x00001e00, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_G, "textures/segment2/segment2.02000.rgba16.inc.c", 0x00108a40, 48390, 0x00002000, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_H, "textures/segment2/segment2.02200.rgba16.inc.c", 0x00108a40, 48390, 0x00002200, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_I, "textures/segment2/segment2.02400.rgba16.inc.c", 0x00108a40, 48390, 0x00002400, 512);

ALIGNED8 const Texture texture_hud_char_J[] = {
#include "textures/segment2/custom_hud_j.rgba16.inc.c"
};

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_K, "textures/segment2/segment2.02800.rgba16.inc.c", 0x00108a40, 48390, 0x00002600, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_L, "textures/segment2/segment2.02A00.rgba16.inc.c", 0x00108a40, 48390, 0x00002800, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_M, "textures/segment2/segment2.02C00.rgba16.inc.c", 0x00108a40, 48390, 0x00002a00, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_N, "textures/segment2/segment2.02E00.rgba16.inc.c", 0x00108a40, 48390, 0x00002c00, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_O, "textures/segment2/segment2.03000.rgba16.inc.c", 0x00108a40, 48390, 0x00002e00, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_P, "textures/segment2/segment2.03200.rgba16.inc.c", 0x00108a40, 48390, 0x00003000, 512);

ALIGNED8 const Texture texture_hud_char_Q[] = {
#include "textures/segment2/custom_hud_q.rgba16.inc.c"
};

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_R, "textures/segment2/segment2.03600.rgba16.inc.c", 0x00108a40, 48390, 0x00003200, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_S, "textures/segment2/segment2.03800.rgba16.inc.c", 0x00108a40, 48390, 0x00003400, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_T, "textures/segment2/segment2.03A00.rgba16.inc.c", 0x00108a40, 48390, 0x00003600, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_U, "textures/segment2/segment2.03C00.rgba16.inc.c", 0x00108a40, 48390, 0x00003800, 512);

ALIGNED8 const Texture texture_hud_char_V[] = {
#include "textures/segment2/custom_hud_v.rgba16.inc.c"
};

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_W, "textures/segment2/segment2.04000.rgba16.inc.c", 0x00108a40, 48390, 0x00003a00, 512);

ALIGNED8 const Texture texture_hud_char_X[] = {
#include "textures/segment2/custom_hud_x.rgba16.inc.c"
};

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_Y, "textures/segment2/segment2.04400.rgba16.inc.c", 0x00108a40, 48390, 0x00003c00, 512);

ALIGNED8 const Texture texture_hud_char_Z[] = {
#include "textures/segment2/custom_hud_z.rgba16.inc.c"
};

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_apostrophe, "textures/segment2/segment2.04800.rgba16.inc.c", 0x00108a40, 48390, 0x00003e00, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_double_quote, "textures/segment2/segment2.04A00.rgba16.inc.c", 0x00108a40, 48390, 0x00004000, 512);

#ifdef VERSION_EU
ALIGNED8 const Texture texture_hud_char_umlaut[] = {
#include "textures/segment2/segment2.umlaut.rgba16.inc.c"// EU ¨
};
#endif

ALIGNED8 const Texture texture_hud_char_exclamation[] = {
#include "textures/segment2/custom_hud_exclamation.rgba16.inc.c" // beta ! no longer in use, new non beta ! was made for all versions
};

ALIGNED8 const Texture texture_hud_char_hashtag[] = {
#include "textures/segment2/custom_hud_hashtag.rgba16.inc.c" // originally JP !!
};

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_question, "textures/segment2/segment2.05000.rgba16.inc.c", 0x002a65b0, 22255, 0x0000a1d0, 512);

ALIGNED8 const Texture texture_hud_char_ampersand[] = {
#include "textures/segment2/custom_hud_ampersand.rgba16.inc.c" // beta & no longer in use, new non beta & was made for all versions
};

ALIGNED8 const Texture texture_hud_char_percent[] = {
#include "textures/segment2/custom_hud_percent.rgba16.inc.c" // beta % no longer in use, new non beta % was made for all versions
};

ALIGNED8 const Texture texture_hud_char_slash[] = {
#include "textures/segment2/custom_hud_slash.rgba16.inc.c"
};

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_multiply, "textures/segment2/segment2.05600.rgba16.inc.c", 0x00108a40, 48390, 0x00004200, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_coin, "textures/segment2/segment2.05800.rgba16.inc.c", 0x00108a40, 48390, 0x00004400, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_mario_head, "textures/segment2/segment2.05A00.rgba16.inc.c", 0x00108a40, 48390, 0x00004600, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_star, "textures/segment2/segment2.05C00.rgba16.inc.c", 0x00108a40, 48390, 0x00004800, 512);

ALIGNED8 const Texture texture_hud_char_period[] = {
#include "textures/segment2/custom_hud_period.rgba16.inc.c"
};

ALIGNED8 const Texture texture_hud_char_comma[] = {
#include "textures/segment2/custom_hud_comma.rgba16.inc.c"
};

ALIGNED8 const Texture texture_hud_char_key[] = {
#include "textures/segment2/custom_hud_key.rgba16.inc.c"
};

ALIGNED8 const Texture texture_hud_char_dash[] = {
#include "textures/segment2/custom_hud_dash.rgba16.inc.c"
};

ALIGNED8 const Texture texture_hud_char_divide[] = {
#include "textures/segment2/custom_hud_divide.rgba16.inc.c"
};

ALIGNED8 const Texture texture_hud_char_plus[] = {
#include "textures/segment2/custom_hud_plus.rgba16.inc.c"
};

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_3, "textures/segment2/segment2.06200.rgba16.inc.c", 0x00108a40, 48390, 0x00004a00, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_4, "textures/segment2/segment2.06280.rgba16.inc.c", 0x00108a40, 48390, 0x00004a80, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_6, "textures/segment2/segment2.06300.rgba16.inc.c", 0x00108a40, 48390, 0x00004b00, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_A, "textures/segment2/segment2.06380.rgba16.inc.c", 0x00108a40, 48390, 0x00004b80, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_B, "textures/segment2/segment2.06400.rgba16.inc.c", 0x00108a40, 48390, 0x00004c00, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_C, "textures/segment2/segment2.06480.rgba16.inc.c", 0x00108a40, 48390, 0x00004c80, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_D, "textures/segment2/segment2.06500.rgba16.inc.c", 0x00108a40, 48390, 0x00004d00, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_E, "textures/segment2/segment2.06580.rgba16.inc.c", 0x00108a40, 48390, 0x00004d80, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_F, "textures/segment2/segment2.06600.rgba16.inc.c", 0x00108a40, 48390, 0x00004e00, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_G, "textures/segment2/segment2.06680.rgba16.inc.c", 0x00108a40, 48390, 0x00004e80, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_H, "textures/segment2/segment2.06700.rgba16.inc.c", 0x00108a40, 48390, 0x00004f00, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_I, "textures/segment2/segment2.06780.rgba16.inc.c", 0x00108a40, 48390, 0x00004f80, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_J, "textures/segment2/segment2.06800.rgba16.inc.c", 0x00108a40, 48390, 0x00005000, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_K, "textures/segment2/segment2.06880.rgba16.inc.c", 0x00108a40, 48390, 0x00005080, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_L, "textures/segment2/segment2.06900.rgba16.inc.c", 0x00108a40, 48390, 0x00005100, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_M, "textures/segment2/segment2.06980.rgba16.inc.c", 0x00108a40, 48390, 0x00005180, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_N, "textures/segment2/segment2.06A00.rgba16.inc.c", 0x00108a40, 48390, 0x00005200, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_O, "textures/segment2/segment2.06A80.rgba16.inc.c", 0x00108a40, 48390, 0x00005280, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_P, "textures/segment2/segment2.06B00.rgba16.inc.c", 0x00108a40, 48390, 0x00005300, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_Q, "textures/segment2/segment2.06B80.rgba16.inc.c", 0x00108a40, 48390, 0x00005380, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_R, "textures/segment2/segment2.06C00.rgba16.inc.c", 0x00108a40, 48390, 0x00005400, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_S, "textures/segment2/segment2.06C80.rgba16.inc.c", 0x00108a40, 48390, 0x00005480, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_T, "textures/segment2/segment2.06D00.rgba16.inc.c", 0x00108a40, 48390, 0x00005500, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_U, "textures/segment2/segment2.06D80.rgba16.inc.c", 0x00108a40, 48390, 0x00005580, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_V, "textures/segment2/segment2.06E00.rgba16.inc.c", 0x00108a40, 48390, 0x00005600, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_W, "textures/segment2/segment2.06E80.rgba16.inc.c", 0x00108a40, 48390, 0x00005680, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_X, "textures/segment2/segment2.06F00.rgba16.inc.c", 0x00108a40, 48390, 0x00005700, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_Y, "textures/segment2/segment2.06F80.rgba16.inc.c", 0x00108a40, 48390, 0x00005780, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_Z, "textures/segment2/segment2.07000.rgba16.inc.c", 0x00108a40, 48390, 0x00005800, 128);

ROM_ASSET_LOAD_TEXTURE(texture_credits_char_period, "textures/segment2/segment2.07080.rgba16.inc.c", 0x00108a40, 48390, 0x00005880, 128);

// JP Small Font
#if defined(VERSION_JP) || defined(VERSION_SH)
ALIGNED8 const Texture texture_font_char_jp_0[] = {
#include "textures/segment2/segment2.07100.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_1[] = {
#include "textures/segment2/segment2.07110.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_2[] = {
#include "textures/segment2/segment2.07120.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_3[] = {
#include "textures/segment2/segment2.07130.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_4[] = {
#include "textures/segment2/segment2.07140.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_5[] = {
#include "textures/segment2/segment2.07150.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_6[] = {
#include "textures/segment2/segment2.07160.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_7[] = {
#include "textures/segment2/segment2.07170.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_8[] = {
#include "textures/segment2/segment2.07180.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_9[] = {
#include "textures/segment2/segment2.07190.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_A[] = {
#include "textures/segment2/segment2.071A0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_B[] = {
#include "textures/segment2/segment2.071B0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_C[] = {
#include "textures/segment2/segment2.071C0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_D[] = {
#include "textures/segment2/segment2.071D0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_E[] = {
#include "textures/segment2/segment2.071E0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_F[] = {
#include "textures/segment2/segment2.071F0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_G[] = {
#include "textures/segment2/segment2.07200.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_H[] = {
#include "textures/segment2/segment2.07210.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_I[] = {
#include "textures/segment2/segment2.07220.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_J[] = {
#include "textures/segment2/segment2.07230.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_K[] = {
#include "textures/segment2/segment2.07240.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_L[] = {
#include "textures/segment2/segment2.07250.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_M[] = {
#include "textures/segment2/segment2.07260.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_N[] = {
#include "textures/segment2/segment2.07270.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_O[] = {
#include "textures/segment2/segment2.07280.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_P[] = {
#include "textures/segment2/segment2.07290.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_Q[] = {
#include "textures/segment2/segment2.072A0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_R[] = {
#include "textures/segment2/segment2.072B0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_S[] = {
#include "textures/segment2/segment2.072C0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_T[] = {
#include "textures/segment2/segment2.072D0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_U[] = {
#include "textures/segment2/segment2.072E0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_V[] = {
#include "textures/segment2/segment2.072F0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_W[] = {
#include "textures/segment2/segment2.07300.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_X[] = {
#include "textures/segment2/segment2.07310.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_Y[] = {
#include "textures/segment2/segment2.07320.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_Z[] = {
#include "textures/segment2/segment2.07330.ia1.inc.c"
};

ROM_ASSET_LOAD_TEXTURE(texture_font_char_jp_long_vowel, "textures/segment2/segment2.07340.ia1.inc.c", 0x00108a40, 48390, 0x00005df2, 16);

ALIGNED8 const Texture texture_font_char_jp_exclamation[] = {
#include "textures/segment2/segment2.07350.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_dakuten[] = {
#include "textures/segment2/segment2.07360.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_handakuten[] = {
#include "textures/segment2/segment2.07370.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_percent[] = {
#include "textures/segment2/segment2.07380.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_question[] = {
#include "textures/segment2/segment2.07390.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_left_right_arrow[] = {
#include "textures/segment2/segment2.073A0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_open_parentheses[] = {
#include "textures/segment2/segment2.073B0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_close_open_parentheses[] = {
#include "textures/segment2/segment2.073C0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_close_parentheses[] = {
#include "textures/segment2/segment2.073D0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_coin[] = {
#include "textures/segment2/segment2.073E0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_multiply[] = {
#include "textures/segment2/segment2.073F0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_star_filled[] = {
#include "textures/segment2/segment2.07400.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_star_hollow[] = {
#include "textures/segment2/segment2.07410.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_a[] = {
#include "textures/segment2/segment2.07420.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_i[] = {
#include "textures/segment2/segment2.07430.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_u[] = {
#include "textures/segment2/segment2.07440.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_c[] = {
#include "textures/segment2/segment2.07450.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_o[] = {
#include "textures/segment2/segment2.07460.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ka[] = {
#include "textures/segment2/segment2.07470.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ki[] = {
#include "textures/segment2/segment2.07480.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ku[] = {
#include "textures/segment2/segment2.07490.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ke[] = {
#include "textures/segment2/segment2.074A0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ko[] = {
#include "textures/segment2/segment2.074B0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_sa[] = {
#include "textures/segment2/segment2.074C0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_shi[] = {
#include "textures/segment2/segment2.074D0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_su[] = {
#include "textures/segment2/segment2.074E0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_se[] = {
#include "textures/segment2/segment2.074F0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_so[] = {
#include "textures/segment2/segment2.07500.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ta[] = {
#include "textures/segment2/segment2.07510.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_chi[] = {
#include "textures/segment2/segment2.07520.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_tsu[] = {
#include "textures/segment2/segment2.07530.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_te[] = {
#include "textures/segment2/segment2.07540.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_to[] = {
#include "textures/segment2/segment2.07550.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_na[] = {
#include "textures/segment2/segment2.07560.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ni[] = {
#include "textures/segment2/segment2.07570.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_nu[] = {
#include "textures/segment2/segment2.07580.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ne[] = {
#include "textures/segment2/segment2.07590.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_no[] = {
#include "textures/segment2/segment2.075A0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ha[] = {
#include "textures/segment2/segment2.075B0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_hi[] = {
#include "textures/segment2/segment2.075C0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_hu[] = {
#include "textures/segment2/segment2.075D0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_he[] = {
#include "textures/segment2/segment2.075E0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ho[] = {
#include "textures/segment2/segment2.075F0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ma[] = {
#include "textures/segment2/segment2.07600.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_mi[] = {
#include "textures/segment2/segment2.07610.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_mu[] = {
#include "textures/segment2/segment2.07620.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_me[] = {
#include "textures/segment2/segment2.07630.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_mo[] = {
#include "textures/segment2/segment2.07640.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ya[] = {
#include "textures/segment2/segment2.07650.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_yu[] = {
#include "textures/segment2/segment2.07660.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_yo[] = {
#include "textures/segment2/segment2.07670.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ra[] = {
#include "textures/segment2/segment2.07680.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ri[] = {
#include "textures/segment2/segment2.07690.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ru[] = {
#include "textures/segment2/segment2.076A0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_re[] = {
#include "textures/segment2/segment2.076B0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_ro[] = {
#include "textures/segment2/segment2.076C0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_wa[] = {
#include "textures/segment2/segment2.076D0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_wo[] = {
#include "textures/segment2/segment2.076E0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_n[] = {
#include "textures/segment2/segment2.076F0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_small_e[] = {
#include "textures/segment2/segment2.07700.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_small_tsu[] = {
#include "textures/segment2/segment2.07710.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_small_ya[] = {
#include "textures/segment2/segment2.07720.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_small_yu[] = {
#include "textures/segment2/segment2.07730.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_small_yo[] = {
#include "textures/segment2/segment2.07740.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_small_a[] = {
#include "textures/segment2/segment2.07750.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_small_i[] = {
#include "textures/segment2/segment2.07760.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_small_o[] = {
#include "textures/segment2/segment2.07770.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_hiragana_small_u[] = {
#include "textures/segment2/segment2.07780.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_interpunct[] = {
#include "textures/segment2/segment2.07790.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_comma[] = {
#include "textures/segment2/segment2.077A0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_a[] = {
#include "textures/segment2/segment2.077B0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_i[] = {
#include "textures/segment2/segment2.077C0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_u[] = {
#include "textures/segment2/segment2.077D0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_e[] = {
#include "textures/segment2/segment2.077E0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_o[] = {
#include "textures/segment2/segment2.077F0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ka[] = {
#include "textures/segment2/segment2.07800.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ki[] = {
#include "textures/segment2/segment2.07810.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ku[] = {
#include "textures/segment2/segment2.07820.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ke[] = {
#include "textures/segment2/segment2.07830.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ko[] = {
#include "textures/segment2/segment2.07840.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_sa[] = {
#include "textures/segment2/segment2.07850.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_shi[] = {
#include "textures/segment2/segment2.07860.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_su[] = {
#include "textures/segment2/segment2.07870.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_se[] = {
#include "textures/segment2/segment2.07880.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_so[] = {
#include "textures/segment2/segment2.07890.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ta[] = {
#include "textures/segment2/segment2.078A0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_chi[] = {
#include "textures/segment2/segment2.078B0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_tsu[] = {
#include "textures/segment2/segment2.078C0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_te[] = {
#include "textures/segment2/segment2.078D0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_to[] = {
#include "textures/segment2/segment2.078E0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_na[] = {
#include "textures/segment2/segment2.078F0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ni[] = {
#include "textures/segment2/segment2.07900.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_nu[] = {
#include "textures/segment2/segment2.07910.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ne[] = {
#include "textures/segment2/segment2.07920.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_no[] = {
#include "textures/segment2/segment2.07930.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ha[] = {
#include "textures/segment2/segment2.07940.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_hi[] = {
#include "textures/segment2/segment2.07950.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_hu[] = {
#include "textures/segment2/segment2.07960.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_he[] = {
#include "textures/segment2/segment2.07970.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ho[] = {
#include "textures/segment2/segment2.07980.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ma[] = {
#include "textures/segment2/segment2.07990.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_mi[] = {
#include "textures/segment2/segment2.079A0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_mu[] = {
#include "textures/segment2/segment2.079B0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_me[] = {
#include "textures/segment2/segment2.079C0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_mo[] = {
#include "textures/segment2/segment2.079D0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ya[] = {
#include "textures/segment2/segment2.079E0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_yu[] = {
#include "textures/segment2/segment2.079F0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_yo[] = {
#include "textures/segment2/segment2.07A00.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ra[] = {
#include "textures/segment2/segment2.07A10.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ri[] = {
#include "textures/segment2/segment2.07A20.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ru[] = {
#include "textures/segment2/segment2.07A30.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_re[] = {
#include "textures/segment2/segment2.07A40.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_ro[] = {
#include "textures/segment2/segment2.07A50.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_wa[] = {
#include "textures/segment2/segment2.07A60.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_n[] = {
#include "textures/segment2/segment2.07A70.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_small_e[] = {
#include "textures/segment2/segment2.07A80.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_small_tsu[] = {
#include "textures/segment2/segment2.07A90.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_small_ya[] = {
#include "textures/segment2/segment2.07AA0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_small_yu[] = {
#include "textures/segment2/segment2.07AB0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_small_yo[] = {
#include "textures/segment2/segment2.07AC0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_small_a[] = {
#include "textures/segment2/segment2.07AD0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_small_i[] = {
#include "textures/segment2/segment2.07AE0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_small_u[] = {
#include "textures/segment2/segment2.07AF0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_katakana_small_o[] = {
#include "textures/segment2/segment2.07B00.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_double_quotation_open[] = {
#include "textures/segment2/segment2.07B10.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_double_quotation_close[] = {
#include "textures/segment2/segment2.07B20.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_wave_dash[] = {
#include "textures/segment2/segment2.07B30.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_jp_ellipsis[] = {
#include "textures/segment2/segment2.07B40.ia1.inc.c"
};

// EU Small Font
#elif defined(VERSION_EU)

ALIGNED8 const Texture texture_font_char_eu_0[] = {
#include "textures/segment2/font_graphics.05F00.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_1[] = {
#include "textures/segment2/font_graphics.05F10.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_2[] = {
#include "textures/segment2/font_graphics.05F20.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_3[] = {
#include "textures/segment2/font_graphics.05F30.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_4[] = {
#include "textures/segment2/font_graphics.05F40.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_5[] = {
#include "textures/segment2/font_graphics.05F50.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_6[] = {
#include "textures/segment2/font_graphics.05F60.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_7[] = {
#include "textures/segment2/font_graphics.05F70.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_8[] = {
#include "textures/segment2/font_graphics.05F80.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_9[] = {
#include "textures/segment2/font_graphics.05F90.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_A[] = {
#include "textures/segment2/font_graphics.05FA0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_B[] = {
#include "textures/segment2/font_graphics.05FB0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_C[] = {
#include "textures/segment2/font_graphics.05FC0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_D[] = {
#include "textures/segment2/font_graphics.05FD0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_E[] = {
#include "textures/segment2/font_graphics.05FE0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_F[] = {
#include "textures/segment2/font_graphics.05FF0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_G[] = {
#include "textures/segment2/font_graphics.06000.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_H[] = {
#include "textures/segment2/font_graphics.06010.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_I[] = {
#include "textures/segment2/font_graphics.06020.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_J[] = {
#include "textures/segment2/font_graphics.06030.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_K[] = {
#include "textures/segment2/font_graphics.06040.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_L[] = {
#include "textures/segment2/font_graphics.06050.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_M[] = {
#include "textures/segment2/font_graphics.06060.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_N[] = {
#include "textures/segment2/font_graphics.06070.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_O[] = {
#include "textures/segment2/font_graphics.06080.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_P[] = {
#include "textures/segment2/font_graphics.06090.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_Q[] = {
#include "textures/segment2/font_graphics.060A0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_R[] = {
#include "textures/segment2/font_graphics.060B0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_S[] = {
#include "textures/segment2/font_graphics.060C0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_T[] = {
#include "textures/segment2/font_graphics.060D0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_U[] = {
#include "textures/segment2/font_graphics.060E0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_V[] = {
#include "textures/segment2/font_graphics.060F0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_W[] = {
#include "textures/segment2/font_graphics.06100.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_X[] = {
#include "textures/segment2/font_graphics.06110.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_Y[] = {
#include "textures/segment2/font_graphics.06120.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_Z[] = {
#include "textures/segment2/font_graphics.06130.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_a[] = {
#include "textures/segment2/font_graphics.06140.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_b[] = {
#include "textures/segment2/font_graphics.06150.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_c[] = {
#include "textures/segment2/font_graphics.06160.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_d[] = {
#include "textures/segment2/font_graphics.06170.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_e[] = {
#include "textures/segment2/font_graphics.06180.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_f[] = {
#include "textures/segment2/font_graphics.06190.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_g[] = {
#include "textures/segment2/font_graphics.061A0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_h[] = {
#include "textures/segment2/font_graphics.061B0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_i[] = {
#include "textures/segment2/font_graphics.061C0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_j[] = {
#include "textures/segment2/font_graphics.061D0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_k[] = {
#include "textures/segment2/font_graphics.061E0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_l[] = {
#include "textures/segment2/font_graphics.061F0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_m[] = {
#include "textures/segment2/font_graphics.06200.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_n[] = {
#include "textures/segment2/font_graphics.06210.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_o[] = {
#include "textures/segment2/font_graphics.06220.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_p[] = {
#include "textures/segment2/font_graphics.06230.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_q[] = {
#include "textures/segment2/font_graphics.06240.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_r[] = {
#include "textures/segment2/font_graphics.06250.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_s[] = {
#include "textures/segment2/font_graphics.06260.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_t[] = {
#include "textures/segment2/font_graphics.06270.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_u[] = {
#include "textures/segment2/font_graphics.06280.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_v[] = {
#include "textures/segment2/font_graphics.06290.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_w[] = {
#include "textures/segment2/font_graphics.062A0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_x[] = {
#include "textures/segment2/font_graphics.062B0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_y[] = {
#include "textures/segment2/font_graphics.062C0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_z[] = {
#include "textures/segment2/font_graphics.062D0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_left_right_arrow[] = {
#include "textures/segment2/font_graphics.062E0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_ampersand[] = {
#include "textures/segment2/font_graphics.062F0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_exclamation[] = {
#include "textures/segment2/font_graphics.06300.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_coin[] = {
#include "textures/segment2/font_graphics.06310.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_multiply[] = {
#include "textures/segment2/font_graphics.06320.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_open_parentheses[] = {
#include "textures/segment2/font_graphics.06330.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_close_open_parentheses[] = {
#include "textures/segment2/font_graphics.06340.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_close_parentheses[] = {
#include "textures/segment2/font_graphics.06350.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_tilde[] = {
#include "textures/segment2/font_graphics.06360.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_period[] = {
#include "textures/segment2/font_graphics.06370.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_percent[] = {
#include "textures/segment2/font_graphics.06380.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_interpunct[] = {
#include "textures/segment2/font_graphics.06390.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_comma[] = {
#include "textures/segment2/font_graphics.063A0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_apostrophe[] = {
#include "textures/segment2/font_graphics.063B0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_question[] = {
#include "textures/segment2/font_graphics.063C0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_star_filled[] = {
#include "textures/segment2/font_graphics.063D0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_star_hollow[] = {
#include "textures/segment2/font_graphics.063E0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_double_quote_open[] = {
#include "textures/segment2/font_graphics.063F0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_double_quote_close[] = {
#include "textures/segment2/font_graphics.06400.ia1.inc.c"
};

ROM_ASSET_LOAD_TEXTURE(texture_font_char_eu_colon, "textures/segment2/font_graphics.06410.ia1.inc.c", 0x00188440, 199722, 0x00014676, 16);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_EU_slash, "textures/segment2/font_graphics.06420.ia1.inc.c", 0x001c4230, 80474, 0x00020b5b, 16);

ALIGNED8 const Texture texture_font_char_eu_button_A[] = {
#include "textures/segment2/font_graphics.06430.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_button_B[] = {
#include "textures/segment2/font_graphics.06440.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_button_C[] = {
#include "textures/segment2/font_graphics.06450.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_button_Z[] = {
#include "textures/segment2/font_graphics.06460.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_button_R[] = {
#include "textures/segment2/font_graphics.06470.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_button_C_up[] = {
#include "textures/segment2/font_graphics.06480.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_button_C_down[] = {
#include "textures/segment2/font_graphics.06490.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_button_C_left[] = {
#include "textures/segment2/font_graphics.064A0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_button_C_right[] = {
#include "textures/segment2/font_graphics.064B0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_umlaut[] = {
#include "textures/segment2/font_graphics.064C0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_circumflex[] = {
#include "textures/segment2/font_graphics.064D0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_grave[] = {
#include "textures/segment2/font_graphics.064E0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_acute[] = {
#include "textures/segment2/font_graphics.064F0.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_cedilla[] = {
#include "textures/segment2/font_graphics.06500.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_unknown[] = {
#include "textures/segment2/font_graphics.06510.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_Cedilla[] = {
#include "textures/segment2/font_graphics.06520.ia1.inc.c"
};

ALIGNED8 const Texture texture_font_char_eu_eszeet[] = {
#include "textures/segment2/font_graphics.06530.ia1.inc.c"
};

// US Small Font
#else
ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_0, "textures/segment2/font_graphics.05900.ia4.inc.c", 0x00108a40, 48390, 0x00005900, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_1, "textures/segment2/font_graphics.05940.ia4.inc.c", 0x00108a40, 48390, 0x00005940, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_2, "textures/segment2/font_graphics.05980.ia4.inc.c", 0x00108a40, 48390, 0x00005980, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_3, "textures/segment2/font_graphics.059C0.ia4.inc.c", 0x00108a40, 48390, 0x000059c0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_4, "textures/segment2/font_graphics.05A00.ia4.inc.c", 0x00108a40, 48390, 0x00005a00, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_5, "textures/segment2/font_graphics.05A40.ia4.inc.c", 0x00108a40, 48390, 0x00005a40, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_6, "textures/segment2/font_graphics.05A80.ia4.inc.c", 0x00108a40, 48390, 0x00005a80, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_7, "textures/segment2/font_graphics.05AC0.ia4.inc.c", 0x00108a40, 48390, 0x00005ac0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_8, "textures/segment2/font_graphics.05B00.ia4.inc.c", 0x00108a40, 48390, 0x00005b00, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_9, "textures/segment2/font_graphics.05B40.ia4.inc.c", 0x00108a40, 48390, 0x00005b40, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_A, "textures/segment2/font_graphics.05B80.ia4.inc.c", 0x00108a40, 48390, 0x00005b80, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_B, "textures/segment2/font_graphics.05BC0.ia4.inc.c", 0x00108a40, 48390, 0x00005bc0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_C, "textures/segment2/font_graphics.05C00.ia4.inc.c", 0x00108a40, 48390, 0x00005c00, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_D, "textures/segment2/font_graphics.05C40.ia4.inc.c", 0x00108a40, 48390, 0x00005c40, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_E, "textures/segment2/font_graphics.05C80.ia4.inc.c", 0x00108a40, 48390, 0x00005c80, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_F, "textures/segment2/font_graphics.05CC0.ia4.inc.c", 0x00108a40, 48390, 0x00005cc0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_G, "textures/segment2/font_graphics.05D00.ia4.inc.c", 0x00108a40, 48390, 0x00005d00, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_H, "textures/segment2/font_graphics.05D40.ia4.inc.c", 0x00108a40, 48390, 0x00005d40, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_I, "textures/segment2/font_graphics.05D80.ia4.inc.c", 0x00108a40, 48390, 0x00005d80, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_J, "textures/segment2/font_graphics.05DC0.ia4.inc.c", 0x00108a40, 48390, 0x00005dc0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_K, "textures/segment2/font_graphics.05E00.ia4.inc.c", 0x00108a40, 48390, 0x00005e00, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_L, "textures/segment2/font_graphics.05E40.ia4.inc.c", 0x00108a40, 48390, 0x00005e40, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_M, "textures/segment2/font_graphics.05E80.ia4.inc.c", 0x00108a40, 48390, 0x00005e80, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_N, "textures/segment2/font_graphics.05EC0.ia4.inc.c", 0x00108a40, 48390, 0x00005ec0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_O, "textures/segment2/font_graphics.05F00.ia4.inc.c", 0x00108a40, 48390, 0x00005f00, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_P, "textures/segment2/font_graphics.05F40.ia4.inc.c", 0x00108a40, 48390, 0x00005f40, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_Q, "textures/segment2/font_graphics.05F80.ia4.inc.c", 0x00108a40, 48390, 0x00005f80, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_R, "textures/segment2/font_graphics.05FC0.ia4.inc.c", 0x00108a40, 48390, 0x00005fc0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_S, "textures/segment2/font_graphics.06000.ia4.inc.c", 0x00108a40, 48390, 0x00006000, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_T, "textures/segment2/font_graphics.06040.ia4.inc.c", 0x00108a40, 48390, 0x00006040, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_U, "textures/segment2/font_graphics.06080.ia4.inc.c", 0x00108a40, 48390, 0x00006080, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_V, "textures/segment2/font_graphics.060C0.ia4.inc.c", 0x00108a40, 48390, 0x000060c0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_W, "textures/segment2/font_graphics.06100.ia4.inc.c", 0x00108a40, 48390, 0x00006100, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_X, "textures/segment2/font_graphics.06140.ia4.inc.c", 0x00108a40, 48390, 0x00006140, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_Y, "textures/segment2/font_graphics.06180.ia4.inc.c", 0x00108a40, 48390, 0x00006180, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_Z, "textures/segment2/font_graphics.061C0.ia4.inc.c", 0x00108a40, 48390, 0x000061c0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_a, "textures/segment2/font_graphics.06200.ia4.inc.c", 0x00108a40, 48390, 0x00006200, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_b, "textures/segment2/font_graphics.06240.ia4.inc.c", 0x00108a40, 48390, 0x00006240, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_c, "textures/segment2/font_graphics.06280.ia4.inc.c", 0x00108a40, 48390, 0x00006280, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_d, "textures/segment2/font_graphics.062C0.ia4.inc.c", 0x00108a40, 48390, 0x000062c0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_e, "textures/segment2/font_graphics.06300.ia4.inc.c", 0x00108a40, 48390, 0x00006300, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_f, "textures/segment2/font_graphics.06340.ia4.inc.c", 0x00108a40, 48390, 0x00006340, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_g, "textures/segment2/font_graphics.06380.ia4.inc.c", 0x00108a40, 48390, 0x00006380, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_h, "textures/segment2/font_graphics.063C0.ia4.inc.c", 0x00108a40, 48390, 0x000063c0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_i, "textures/segment2/font_graphics.06400.ia4.inc.c", 0x00108a40, 48390, 0x00006400, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_j, "textures/segment2/font_graphics.06440.ia4.inc.c", 0x00108a40, 48390, 0x00006440, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_k, "textures/segment2/font_graphics.06480.ia4.inc.c", 0x00108a40, 48390, 0x00006480, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_l, "textures/segment2/font_graphics.064C0.ia4.inc.c", 0x00108a40, 48390, 0x000064c0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_m, "textures/segment2/font_graphics.06500.ia4.inc.c", 0x00108a40, 48390, 0x00006500, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_n, "textures/segment2/font_graphics.06540.ia4.inc.c", 0x00108a40, 48390, 0x00006540, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_o, "textures/segment2/font_graphics.06580.ia4.inc.c", 0x00108a40, 48390, 0x00006580, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_p, "textures/segment2/font_graphics.065C0.ia4.inc.c", 0x00108a40, 48390, 0x000065c0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_q, "textures/segment2/font_graphics.06600.ia4.inc.c", 0x00108a40, 48390, 0x00006600, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_r, "textures/segment2/font_graphics.06640.ia4.inc.c", 0x00108a40, 48390, 0x00006640, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_s, "textures/segment2/font_graphics.06680.ia4.inc.c", 0x00108a40, 48390, 0x00006680, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_t, "textures/segment2/font_graphics.066C0.ia4.inc.c", 0x00108a40, 48390, 0x000066c0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_u, "textures/segment2/font_graphics.06700.ia4.inc.c", 0x00108a40, 48390, 0x00006700, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_v, "textures/segment2/font_graphics.06740.ia4.inc.c", 0x00108a40, 48390, 0x00006740, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_w, "textures/segment2/font_graphics.06780.ia4.inc.c", 0x00108a40, 48390, 0x00006780, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_x, "textures/segment2/font_graphics.067C0.ia4.inc.c", 0x00108a40, 48390, 0x000067c0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_y, "textures/segment2/font_graphics.06800.ia4.inc.c", 0x00108a40, 48390, 0x00006800, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_z, "textures/segment2/font_graphics.06840.ia4.inc.c", 0x00108a40, 48390, 0x00006840, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_left_right_arrow, "textures/segment2/font_graphics.06880.ia4.inc.c", 0x00108a40, 48390, 0x00006880, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_exclamation, "textures/segment2/font_graphics.068C0.ia4.inc.c", 0x00108a40, 48390, 0x000068c0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_coin, "textures/segment2/font_graphics.06900.ia4.inc.c", 0x00108a40, 48390, 0x00006900, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_multiply, "textures/segment2/font_graphics.06940.ia4.inc.c", 0x00108a40, 48390, 0x00006940, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_open_parentheses, "textures/segment2/font_graphics.06980.ia4.inc.c", 0x00108a40, 48390, 0x00006980, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_close_open_parentheses, "textures/segment2/font_graphics.069C0.ia4.inc.c", 0x00108a40, 48390, 0x000069c0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_close_parentheses, "textures/segment2/font_graphics.06A00.ia4.inc.c", 0x00108a40, 48390, 0x00006a00, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_tilde, "textures/segment2/font_graphics.06A40.ia4.inc.c", 0x00108a40, 48390, 0x00006a40, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_period, "textures/segment2/font_graphics.06A80.ia4.inc.c", 0x00108a40, 48390, 0x00006a80, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_percent, "textures/segment2/font_graphics.06AC0.ia4.inc.c", 0x00108a40, 48390, 0x00006ac0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_interpunct, "textures/segment2/font_graphics.06B00.ia4.inc.c", 0x00108a40, 48390, 0x00006b00, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_comma, "textures/segment2/font_graphics.06B40.ia4.inc.c", 0x00108a40, 48390, 0x00006b40, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_apostrophe, "textures/segment2/font_graphics.06B80.ia4.inc.c", 0x00108a40, 48390, 0x00006b80, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_question, "textures/segment2/font_graphics.06BC0.ia4.inc.c", 0x00108a40, 48390, 0x00006bc0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_star_filled, "textures/segment2/font_graphics.06C00.ia4.inc.c", 0x00108a40, 48390, 0x00006c00, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_star_hollow, "textures/segment2/font_graphics.06C40.ia4.inc.c", 0x00108a40, 48390, 0x00006c40, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_double_quote_open, "textures/segment2/font_graphics.06C80.ia4.inc.c", 0x00108a40, 48390, 0x00006c80, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_double_quote_close, "textures/segment2/font_graphics.06CC0.ia4.inc.c", 0x00108a40, 48390, 0x00006cc0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_ellipsis, "textures/segment2/font_graphics.06D00.ia4.inc.c", 0x00108a40, 48390, 0x00006d00, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_slash, "textures/segment2/font_graphics.06D40.ia4.inc.c", 0x00108a40, 48390, 0x00006d40, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_ampersand, "textures/segment2/font_graphics.06D80.ia4.inc.c", 0x00108a40, 48390, 0x00006d80, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_button_A, "textures/segment2/font_graphics.06DC0.ia4.inc.c", 0x00108a40, 48390, 0x00006dc0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_button_B, "textures/segment2/font_graphics.06E00.ia4.inc.c", 0x00108a40, 48390, 0x00006e00, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_button_C, "textures/segment2/font_graphics.06E40.ia4.inc.c", 0x00108a40, 48390, 0x00006e40, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_button_Z, "textures/segment2/font_graphics.06E80.ia4.inc.c", 0x00108a40, 48390, 0x00006e80, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_button_R, "textures/segment2/font_graphics.06EC0.ia4.inc.c", 0x00108a40, 48390, 0x00006ec0, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_button_C_up, "textures/segment2/font_graphics.06F00.ia4.inc.c", 0x00108a40, 48390, 0x00006f00, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_button_C_down, "textures/segment2/font_graphics.06F40.ia4.inc.c", 0x00108a40, 48390, 0x00006f40, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_button_C_left, "textures/segment2/font_graphics.06F80.ia4.inc.c", 0x00108a40, 48390, 0x00006f80, 64);

ROM_ASSET_LOAD_TEXTURE(texture_font_char_us_button_C_right, "textures/segment2/font_graphics.06FC0.ia4.inc.c", 0x00108a40, 48390, 0x00006fc0, 64);
#endif

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_camera, "textures/segment2/segment2.07B50.rgba16.inc.c", 0x00108a40, 48390, 0x00007000, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_lakitu, "textures/segment2/segment2.07D50.rgba16.inc.c", 0x00108a40, 48390, 0x00007200, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_no_camera, "textures/segment2/segment2.07F50.rgba16.inc.c", 0x00108a40, 48390, 0x00007400, 512);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_arrow_up, "textures/segment2/segment2.08150.rgba16.inc.c", 0x00108a40, 48390, 0x00007600, 128);

ROM_ASSET_LOAD_TEXTURE(texture_hud_char_arrow_down, "textures/segment2/segment2.081D0.rgba16.inc.c", 0x00108a40, 48390, 0x00007680, 128);

// TODO: move these out of the font
extern ALIGNED8 const Texture texture_hud_char_luigi_head[];
extern ALIGNED8 const Texture texture_hud_char_toad_head[];
extern ALIGNED8 const Texture texture_hud_char_waluigi_head[];
extern ALIGNED8 const Texture texture_hud_char_wario_head[];

// Main HUD print table 0x02008250-0x02008337
const Texture *const main_hud_lut[] = {
#ifdef VERSION_EU
    texture_hud_char_0, texture_hud_char_1, texture_hud_char_2, texture_hud_char_3,
    texture_hud_char_4, texture_hud_char_5, texture_hud_char_6, texture_hud_char_7,
    texture_hud_char_8, texture_hud_char_9, texture_hud_char_A, texture_hud_char_B,
    texture_hud_char_C, texture_hud_char_D, texture_hud_char_E, texture_hud_char_F,
    texture_hud_char_G, texture_hud_char_H, texture_hud_char_I, texture_hud_char_J,
    texture_hud_char_K, texture_hud_char_L, texture_hud_char_M, texture_hud_char_N,
    texture_hud_char_O, texture_hud_char_P, texture_hud_char_Q, texture_hud_char_R,
    texture_hud_char_S, texture_hud_char_T, texture_hud_char_U, texture_hud_char_V,
    texture_hud_char_W, texture_hud_char_X, texture_hud_char_Y, texture_hud_char_Z,
    texture_hud_char_exclamation, texture_hud_char_hashtag, texture_hud_char_question, texture_hud_char_ampersand,
    texture_hud_char_percent, texture_hud_char_multiply, texture_hud_char_coin, texture_hud_char_comma,
    texture_hud_char_star, texture_hud_char_period, texture_hud_char_key, texture_hud_char_apostrophe,
    texture_hud_char_double_quote, texture_hud_char_slash, texture_hud_char_dash, texture_hud_char_divide,
    texture_hud_char_plus, texture_hud_char_mario_head, texture_hud_char_luigi_head, texture_hud_char_wario_head,
    texture_hud_char_waluigi_head, texture_hud_char_toad_head, texture_hud_char_umlaut,
#elif defined(VERSION_US)
    texture_hud_char_0, texture_hud_char_1, texture_hud_char_2, texture_hud_char_3,
    texture_hud_char_4, texture_hud_char_5, texture_hud_char_6, texture_hud_char_7,
    texture_hud_char_8, texture_hud_char_9, texture_hud_char_A, texture_hud_char_B,
    texture_hud_char_C, texture_hud_char_D, texture_hud_char_E, texture_hud_char_F,
    texture_hud_char_G, texture_hud_char_H, texture_hud_char_I, texture_hud_char_J,
    texture_hud_char_K, texture_hud_char_L, texture_hud_char_M, texture_hud_char_N,
    texture_hud_char_O, texture_hud_char_P, texture_hud_char_Q, texture_hud_char_R,
    texture_hud_char_S, texture_hud_char_T, texture_hud_char_U, texture_hud_char_V,
    texture_hud_char_W, texture_hud_char_X, texture_hud_char_Y, texture_hud_char_Z,
    texture_hud_char_exclamation, texture_hud_char_hashtag, texture_hud_char_question, texture_hud_char_ampersand,
    texture_hud_char_percent, texture_hud_char_multiply, texture_hud_char_coin, texture_hud_char_comma,
    texture_hud_char_star, texture_hud_char_period, texture_hud_char_key, texture_hud_char_apostrophe,
    texture_hud_char_double_quote, texture_hud_char_slash, texture_hud_char_dash, texture_hud_char_divide,
    texture_hud_char_plus, texture_hud_char_mario_head, texture_hud_char_luigi_head, texture_hud_char_wario_head,
    texture_hud_char_waluigi_head, texture_hud_char_toad_head,                0x0,
#else
    texture_hud_char_0, texture_hud_char_1, texture_hud_char_2, texture_hud_char_3,
    texture_hud_char_4, texture_hud_char_5, texture_hud_char_6, texture_hud_char_7,
    texture_hud_char_8, texture_hud_char_9, texture_hud_char_A, texture_hud_char_B,
    texture_hud_char_C, texture_hud_char_D, texture_hud_char_E, texture_hud_char_F,
    texture_hud_char_G, texture_hud_char_H, texture_hud_char_I, texture_hud_char_J,
    texture_hud_char_K, texture_hud_char_L, texture_hud_char_M, texture_hud_char_N,
    texture_hud_char_O, texture_hud_char_P, texture_hud_char_Q, texture_hud_char_R,
    texture_hud_char_S, texture_hud_char_T, texture_hud_char_U, texture_hud_char_V,
    texture_hud_char_W, texture_hud_char_X, texture_hud_char_Y, texture_hud_char_Z,
    texture_hud_char_exclamation, texture_hud_char_hashtag, texture_hud_char_question, texture_hud_char_ampersand,
    texture_hud_char_percent, texture_hud_char_multiply, texture_hud_char_coin, texture_hud_char_comma,
    texture_hud_char_star, texture_hud_char_period, texture_hud_char_key, texture_hud_char_apostrophe,
    texture_hud_char_double_quote, texture_hud_char_slash, texture_hud_char_dash, texture_hud_char_divide,
    texture_hud_char_plus, texture_hud_char_mario_head, texture_hud_char_luigi_head, texture_hud_char_wario_head,
    texture_hud_char_waluigi_head, texture_hud_char_toad_head,                0x0,
#endif
};

// Main small font print table 0x02008338-0x02008737
const Texture *const main_font_lut[] = {
#ifdef VERSION_EU // EU Font Table
    texture_font_char_eu_0, texture_font_char_eu_1, texture_font_char_eu_2, texture_font_char_eu_3,
    texture_font_char_eu_4, texture_font_char_eu_5, texture_font_char_eu_6, texture_font_char_eu_7,
    texture_font_char_eu_8, texture_font_char_eu_9, texture_font_char_eu_A, texture_font_char_eu_B,
    texture_font_char_eu_C, texture_font_char_eu_D, texture_font_char_eu_E, texture_font_char_eu_F,
    texture_font_char_eu_G, texture_font_char_eu_H, texture_font_char_eu_I, texture_font_char_eu_J,
    texture_font_char_eu_K, texture_font_char_eu_L, texture_font_char_eu_M, texture_font_char_eu_N,
    texture_font_char_eu_O, texture_font_char_eu_P, texture_font_char_eu_Q, texture_font_char_eu_R,
    texture_font_char_eu_S, texture_font_char_eu_T, texture_font_char_eu_U, texture_font_char_eu_V,
    texture_font_char_eu_W, texture_font_char_eu_X, texture_font_char_eu_Y, texture_font_char_eu_Z,
    texture_font_char_eu_a, texture_font_char_eu_b, texture_font_char_eu_c, texture_font_char_eu_d,
    texture_font_char_eu_e, texture_font_char_eu_f, texture_font_char_eu_g, texture_font_char_eu_h,
    texture_font_char_eu_i, texture_font_char_eu_j, texture_font_char_eu_k, texture_font_char_eu_l,
    texture_font_char_eu_m, texture_font_char_eu_n, texture_font_char_eu_o, texture_font_char_eu_p,
    texture_font_char_eu_q, texture_font_char_eu_r, texture_font_char_eu_s, texture_font_char_eu_t,
    texture_font_char_eu_u, texture_font_char_eu_v, texture_font_char_eu_w, texture_font_char_eu_x,
    texture_font_char_eu_y, texture_font_char_eu_z, texture_font_char_eu_apostrophe, texture_font_char_eu_period,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    texture_font_char_eu_button_C_up,
    texture_font_char_eu_button_C_down,
    texture_font_char_eu_button_C_left,
    texture_font_char_eu_button_C_right,
    texture_font_char_eu_button_A,
    texture_font_char_eu_button_B,
    texture_font_char_eu_button_C,
    texture_font_char_eu_button_Z,
    texture_font_char_eu_button_R,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    texture_font_char_eu_comma,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    texture_font_char_EU_slash,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0,
    texture_font_char_eu_open_parentheses,
    texture_font_char_eu_close_open_parentheses,
    texture_font_char_eu_close_parentheses,
    texture_font_char_eu_left_right_arrow,
    texture_font_char_eu_ampersand,
    texture_font_char_eu_colon,
    texture_font_char_eu_acute,
    texture_font_char_eu_circumflex,
    texture_font_char_eu_umlaut,
    texture_font_char_eu_grave,
    texture_font_char_eu_unknown,
    texture_font_char_eu_eszeet,
    texture_font_char_eu_Cedilla,
    texture_font_char_eu_cedilla,
    0x0, 0x0, 0x0,
    texture_font_char_eu_exclamation,
    texture_font_char_eu_percent,
    texture_font_char_eu_question,
    texture_font_char_eu_double_quote_open,
    texture_font_char_eu_double_quote_close,
    texture_font_char_eu_tilde,
    0x0,
    texture_font_char_eu_coin,
    texture_font_char_eu_star_filled,
    texture_font_char_eu_multiply,
    texture_font_char_eu_interpunct,
    texture_font_char_eu_star_hollow,
    0x0, 0x0,
#elif defined(VERSION_US) // US Font Table
    texture_font_char_us_0, texture_font_char_us_1, texture_font_char_us_2, texture_font_char_us_3,
    texture_font_char_us_4, texture_font_char_us_5, texture_font_char_us_6, texture_font_char_us_7,
    texture_font_char_us_8, texture_font_char_us_9, texture_font_char_us_A, texture_font_char_us_B,
    texture_font_char_us_C, texture_font_char_us_D, texture_font_char_us_E, texture_font_char_us_F,
    texture_font_char_us_G, texture_font_char_us_H, texture_font_char_us_I, texture_font_char_us_J,
    texture_font_char_us_K, texture_font_char_us_L, texture_font_char_us_M, texture_font_char_us_N,
    texture_font_char_us_O, texture_font_char_us_P, texture_font_char_us_Q, texture_font_char_us_R,
    texture_font_char_us_S, texture_font_char_us_T, texture_font_char_us_U, texture_font_char_us_V,
    texture_font_char_us_W, texture_font_char_us_X, texture_font_char_us_Y, texture_font_char_us_Z,
    texture_font_char_us_a, texture_font_char_us_b, texture_font_char_us_c, texture_font_char_us_d,
    texture_font_char_us_e, texture_font_char_us_f, texture_font_char_us_g, texture_font_char_us_h,
    texture_font_char_us_i, texture_font_char_us_j, texture_font_char_us_k, texture_font_char_us_l,
    texture_font_char_us_m, texture_font_char_us_n, texture_font_char_us_o, texture_font_char_us_p,
    texture_font_char_us_q, texture_font_char_us_r, texture_font_char_us_s, texture_font_char_us_t,
    texture_font_char_us_u, texture_font_char_us_v, texture_font_char_us_w, texture_font_char_us_x,
    texture_font_char_us_y, texture_font_char_us_z, texture_font_char_us_apostrophe, texture_font_char_us_period,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
    texture_font_char_us_button_C_up, texture_font_char_us_button_C_down, texture_font_char_us_button_C_left, texture_font_char_us_button_C_right,
    texture_font_char_us_button_A, texture_font_char_us_button_B, texture_font_char_us_button_C, texture_font_char_us_button_Z,
    texture_font_char_us_button_R,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0, texture_font_char_us_comma,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0, texture_font_char_us_slash,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0, texture_font_char_us_open_parentheses, texture_font_char_us_close_open_parentheses, texture_font_char_us_close_parentheses,
    texture_font_char_us_left_right_arrow, texture_font_char_us_ampersand, texture_font_char_us_ellipsis,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0,               0x0,               0x0,
                  0x0,               0x0, texture_font_char_us_exclamation, texture_font_char_us_percent,
    texture_font_char_us_question, texture_font_char_us_double_quote_open, texture_font_char_us_double_quote_close, texture_font_char_us_tilde,
                  0x0, texture_font_char_us_coin, texture_font_char_us_star_filled, texture_font_char_us_multiply,
    texture_font_char_us_interpunct, texture_font_char_us_star_hollow,               0x0,               0x0,
#elif defined(VERSION_JP) || defined(VERSION_SH)
    texture_font_char_jp_0, texture_font_char_jp_1, texture_font_char_jp_2, texture_font_char_jp_3,
    texture_font_char_jp_4, texture_font_char_jp_5, texture_font_char_jp_6, texture_font_char_jp_7,
    texture_font_char_jp_8, texture_font_char_jp_9, texture_font_char_jp_A, texture_font_char_jp_B,
    texture_font_char_jp_C, texture_font_char_jp_D, texture_font_char_jp_E, texture_font_char_jp_F,
    texture_font_char_jp_G, texture_font_char_jp_H, texture_font_char_jp_I, texture_font_char_jp_J,
    texture_font_char_jp_K, texture_font_char_jp_L, texture_font_char_jp_M, texture_font_char_jp_N,
    texture_font_char_jp_O, texture_font_char_jp_P, texture_font_char_jp_Q, texture_font_char_jp_R,
    texture_font_char_jp_S, texture_font_char_jp_T, texture_font_char_jp_U, texture_font_char_jp_V,
    texture_font_char_jp_W, texture_font_char_jp_X, texture_font_char_jp_Y, texture_font_char_jp_Z,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
    texture_font_char_jp_hiragana_a, texture_font_char_jp_hiragana_i, texture_font_char_jp_hiragana_u, texture_font_char_jp_hiragana_c,
    texture_font_char_jp_hiragana_o, texture_font_char_jp_hiragana_ka, texture_font_char_jp_hiragana_ki, texture_font_char_jp_hiragana_ku,
    texture_font_char_jp_hiragana_ke, texture_font_char_jp_hiragana_ko, texture_font_char_jp_hiragana_sa, texture_font_char_jp_hiragana_shi,
    texture_font_char_jp_hiragana_su, texture_font_char_jp_hiragana_se, texture_font_char_jp_hiragana_so, texture_font_char_jp_hiragana_ta,
    texture_font_char_jp_hiragana_chi, texture_font_char_jp_hiragana_tsu, texture_font_char_jp_hiragana_te, texture_font_char_jp_hiragana_to,
    texture_font_char_jp_hiragana_na, texture_font_char_jp_hiragana_ni, texture_font_char_jp_hiragana_nu, texture_font_char_jp_hiragana_ne,
    texture_font_char_jp_hiragana_no, texture_font_char_jp_hiragana_ha, texture_font_char_jp_hiragana_hi, texture_font_char_jp_hiragana_hu,
    texture_font_char_jp_hiragana_he, texture_font_char_jp_hiragana_ho, texture_font_char_jp_hiragana_ma, texture_font_char_jp_hiragana_mi,
    texture_font_char_jp_hiragana_mu, texture_font_char_jp_hiragana_me, texture_font_char_jp_hiragana_mo, texture_font_char_jp_hiragana_ya,
    texture_font_char_jp_hiragana_yu, texture_font_char_jp_hiragana_yo, texture_font_char_jp_hiragana_ra, texture_font_char_jp_hiragana_ri,
    texture_font_char_jp_hiragana_ru, texture_font_char_jp_hiragana_re, texture_font_char_jp_hiragana_ro, texture_font_char_jp_hiragana_wa,
    texture_font_char_jp_hiragana_wo, texture_font_char_jp_hiragana_n,                   0x0, texture_font_char_jp_comma,
    texture_font_char_jp_katakana_a, texture_font_char_jp_katakana_i, texture_font_char_jp_katakana_u, texture_font_char_jp_katakana_e,
    texture_font_char_jp_katakana_o, texture_font_char_jp_katakana_ka, texture_font_char_jp_katakana_ki, texture_font_char_jp_katakana_ku,
    texture_font_char_jp_katakana_ke, texture_font_char_jp_katakana_ko, texture_font_char_jp_katakana_sa, texture_font_char_jp_katakana_shi,
    texture_font_char_jp_katakana_su, texture_font_char_jp_katakana_se, texture_font_char_jp_katakana_so, texture_font_char_jp_katakana_ta,
    texture_font_char_jp_katakana_chi, texture_font_char_jp_katakana_tsu, texture_font_char_jp_katakana_te, texture_font_char_jp_katakana_to,
    texture_font_char_jp_katakana_na, texture_font_char_jp_katakana_ni, texture_font_char_jp_katakana_nu, texture_font_char_jp_katakana_ne,
    texture_font_char_jp_katakana_no, texture_font_char_jp_katakana_ha, texture_font_char_jp_katakana_hi, texture_font_char_jp_katakana_hu,
    texture_font_char_jp_katakana_he, texture_font_char_jp_katakana_ho, texture_font_char_jp_katakana_ma, texture_font_char_jp_katakana_mi,
    texture_font_char_jp_katakana_mu, texture_font_char_jp_katakana_me, texture_font_char_jp_katakana_mo, texture_font_char_jp_katakana_ya,
    texture_font_char_jp_katakana_yu, texture_font_char_jp_katakana_yo, texture_font_char_jp_katakana_ra, texture_font_char_jp_katakana_ri,
    texture_font_char_jp_katakana_ru, texture_font_char_jp_katakana_re, texture_font_char_jp_katakana_ro, texture_font_char_jp_katakana_wa,
                      0x0, texture_font_char_jp_katakana_n,                   0x0, texture_font_char_jp_long_vowel,
    texture_font_char_jp_hiragana_small_e, texture_font_char_jp_hiragana_small_tsu, texture_font_char_jp_hiragana_small_ya, texture_font_char_jp_hiragana_small_yu,
    texture_font_char_jp_hiragana_small_yo, texture_font_char_jp_hiragana_small_a, texture_font_char_jp_hiragana_small_i, texture_font_char_jp_hiragana_small_u,
    texture_font_char_jp_hiragana_small_o,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
    texture_font_char_jp_katakana_small_e, texture_font_char_jp_katakana_small_tsu, texture_font_char_jp_katakana_small_ya, texture_font_char_jp_katakana_small_yu,
    texture_font_char_jp_katakana_small_yo, texture_font_char_jp_katakana_small_a, texture_font_char_jp_katakana_small_i, texture_font_char_jp_katakana_small_u,
    texture_font_char_jp_katakana_small_o,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0, texture_font_char_jp_open_parentheses, texture_font_char_jp_close_open_parentheses, texture_font_char_jp_close_parentheses,
    texture_font_char_jp_left_right_arrow,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
                      0x0,                   0x0,                   0x0,                   0x0,
    texture_font_char_jp_dakuten, texture_font_char_jp_handakuten, texture_font_char_jp_exclamation, texture_font_char_jp_percent,
    texture_font_char_jp_question, texture_font_char_jp_double_quotation_open, texture_font_char_jp_double_quotation_close, texture_font_char_jp_wave_dash,
    texture_font_char_jp_ellipsis, texture_font_char_jp_coin, texture_font_char_jp_star_filled, texture_font_char_jp_multiply,
    texture_font_char_jp_interpunct, texture_font_char_jp_star_hollow,                   0x0,                   0x0,
#endif
};

// credits font LUT 0x02008738-0x020087CB
const Texture *const main_credits_font_lut[] = {
                       0x0,                    0x0,                    0x0, texture_credits_char_3,
    texture_credits_char_4,                    0x0, texture_credits_char_6,                    0x0,
                       0x0,                    0x0, texture_credits_char_A, texture_credits_char_B,
    texture_credits_char_C, texture_credits_char_D, texture_credits_char_E, texture_credits_char_F,
    texture_credits_char_G, texture_credits_char_H, texture_credits_char_I, texture_credits_char_J,
    texture_credits_char_K, texture_credits_char_L, texture_credits_char_M, texture_credits_char_N,
    texture_credits_char_O, texture_credits_char_P, texture_credits_char_Q, texture_credits_char_R,
    texture_credits_char_S, texture_credits_char_T, texture_credits_char_U, texture_credits_char_V,
    texture_credits_char_W, texture_credits_char_X, texture_credits_char_Y, texture_credits_char_Z,
    texture_credits_char_period,
};

// HUD camera table 0x020087CC-0x020087E3
const Texture *const main_hud_camera_lut[] = {
    texture_hud_char_camera, texture_hud_char_mario_head, texture_hud_char_lakitu, texture_hud_char_no_camera,
    texture_hud_char_arrow_up, texture_hud_char_arrow_down, texture_hud_char_luigi_head, texture_hud_char_toad_head,
    texture_hud_char_waluigi_head, texture_hud_char_wario_head,
};

// If you change the language here, the following Makefile rule also needs to
// change, to generate the right version of define_text.inc.c:
// $(BUILD_DIR)/bin/segment2.o: $(BUILD_DIR)/text/$(VERSION)/define_text.inc.c
#if defined(VERSION_JP) || defined(VERSION_SH)
#include "text/jp/define_text.inc.c"
#elif defined(VERSION_US)
#include "text/us/define_text.inc.c"
#endif

UNUSED static const u64 segment2_unused_0 = 0;

// 0x0200EC60 - 0x0200EC98
const Gfx dl_hud_img_begin[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_COPY),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(255, 255, 255, 255),
#if defined(VERSION_EU) || defined(VERSION_SH)
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
#endif
#ifdef VERSION_EU
    gsDPSetTextureFilter(G_TF_POINT),
#elif defined(VERSION_JP) || defined(VERSION_US)
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
#endif
    gsSPEndDisplayList(),
};

// 0x0200EC98 - 0x0200ECC8
const Gfx dl_hud_img_load_tex_block[] = {
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x0200ECC8 - 0x0200ED00
const Gfx dl_hud_img_end[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
#ifdef VERSION_EU
    gsDPSetTextureFilter(G_TF_BILERP),
#endif
    gsDPSetCycleType(G_CYC_1CYCLE),
#if defined(VERSION_JP) || defined(VERSION_US)
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
#endif
    gsSPEndDisplayList(),
};

// 0x0200ED00 - 0x0200ED38
const Gfx dl_rgba16_text_begin[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

// 0x0200ED38 - 0x0200ED68
const Gfx dl_rgba16_load_tex_block[] = {
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x0200ED68 - 0x0200EDA8
const Gfx dl_rgba16_text_end[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

// 0x0200EDA8 - 0x0200EDE8
ROM_ASSET_LOAD_VTX(vertex_text_bg_box, 0x00108a40, 48390, 0x00011c08, 64);

// 0x0200EDE8 - 0x0200EE28
const Gfx dl_draw_text_bg_box[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADE, G_CC_FADE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPVertexNonGlobal(vertex_text_bg_box, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

#ifndef VERSION_EU
// 0x0200EE28 - 0x0200EE68
#if defined(VERSION_JP) || defined(VERSION_SH)
static const Vtx vertex_ia8_char[] = {
    {{{     0,      0,      0}, 0, {     0,   1024}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     8,      0,      0}, 0, {   512,   1024}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     8,     16,      0}, 0, {   512,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,     16,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
};
#else
ROM_ASSET_LOAD_VTX(vertex_ia8_char, 0x00108a40, 48390, 0x00011c88, 64);
#endif
// !EU
#endif

#ifdef VERSION_EU
// 0x020073B0
const Gfx dl_ia_text_begin[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

// 0x020073E8 - 0x02007418
const Gfx dl_ia_text_tex_settings[] = {
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_MIRROR, 3, G_TX_NOLOD, G_TX_WRAP | G_TX_MIRROR, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, ((16 * 8 + G_IM_SIZ_4b_INCR) >> G_IM_SIZ_4b_SHIFT) - 1, CALC_DXT(16, G_IM_SIZ_4b_BYTES)),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_MIRROR, 3, G_TX_NOLOD, G_TX_WRAP | G_TX_MIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x02007418 - 0x02007450
const Gfx dl_ia_text_end[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};

#elif defined(VERSION_US)
const Gfx dl_ia_text_begin[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

const Gfx dl_ia_text_tex_settings[] = {
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, ((16 * 8 + G_IM_SIZ_4b_INCR) >> G_IM_SIZ_4b_SHIFT) - 1, CALC_DXT(16, G_IM_SIZ_4b_BYTES)),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(vertex_ia8_char, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0, 0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

#else
// 0x0200EE68 - 0x0200EEA8
const Gfx dl_ia_text_begin[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

// 0x0200EEA8 - 0x0200EEF0
const Gfx dl_ia_text_tex_settings[] = {
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 3, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 8 * 16 - 1, CALC_DXT(8, G_IM_SIZ_8b_BYTES)),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 1, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 3, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (8 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(vertex_ia8_char, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0, 0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};
#endif

#ifndef VERSION_EU
// 0x0200EEF0 - 0x0200EF30
const Gfx dl_ia_text_end[] = {
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPSetGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};
#endif

// 0x0200EF30 - 0x0200EF60
ROM_ASSET_LOAD_VTX(vertex_triangle, 0x00108a40, 48390, 0x00011d90, 48);

// 0x0200EF60 - 0x0200EFB0
const Gfx dl_draw_triangle[] = {
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADE, G_CC_FADE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPVertexNonGlobal(vertex_triangle, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0200EFB0 - 0x0200EFF0
ROM_ASSET_LOAD_VTX(vertex_billboard_num, 0x00108a40, 48390, 0x00011e10, 64);

// 0x0200EFF0 - 0x0200F038
const Gfx dl_billboard_num_begin[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x0200F038 - 0x0200F078
const Gfx dl_billboard_num_end[] = {
    gsSPVertex(vertex_billboard_num, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0200F078 - 0x0200F0A8
const Gfx dl_billboard_num_0[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F0A8 - 0x0200F0D8
const Gfx dl_billboard_num_1[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_1),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F0D8 - 0x0200F108
const Gfx dl_billboard_num_2[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_2),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F108 - 0x0200F138
const Gfx dl_billboard_num_3[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_3),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F138 - 0x0200F168
const Gfx dl_billboard_num_4[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_4),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F168 - 0x0200F198
const Gfx dl_billboard_num_5[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_5),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F198 - 0x0200F1C8
const Gfx dl_billboard_num_6[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_6),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F1C8 - 0x0200F1F8
const Gfx dl_billboard_num_7[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_7),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F1F8 - 0x0200F228
const Gfx dl_billboard_num_8[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

// 0x0200F228 - 0x0200F258
const Gfx dl_billboard_num_9[] = {
    gsSPDisplayList(dl_billboard_num_begin),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_9),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(dl_billboard_num_end),
    gsSPEndDisplayList(),
};

//
// Three-digits orange number
//

const Vtx vertex_billboard_num3[] = {
    { { { -32, -32, 0 }, 0, {    0, 1024 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { +32, -32, 0 }, 0, { 1024, 1024 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { +32, +32, 0 }, 0, { 1024,    0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { -32, +32, 0 }, 0, {    0,    0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { -56, -32, 0 }, 0, {    0, 1024 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { {  +8, -32, 0 }, 0, { 1024, 1024 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { {  +8, +32, 0 }, 0, { 1024,    0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { -56, +32, 0 }, 0, {    0,    0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { {  -8, -32, 0 }, 0, {    0, 1024 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { +56, -32, 0 }, 0, { 1024, 1024 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { +56, +32, 0 }, 0, { 1024,    0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { {  -8, +32, 0 }, 0, {    0,    0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { -80, -32, 0 }, 0, {    0, 1024 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { -16, -32, 0 }, 0, { 1024, 1024 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { -16, +32, 0 }, 0, { 1024,    0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { -80, +32, 0 }, 0, {    0,    0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { -32, -32, 0 }, 0, {    0, 1024 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { +32, -32, 0 }, 0, { 1024, 1024 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { +32, +32, 0 }, 0, { 1024,    0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { -32, +32, 0 }, 0, {    0,    0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { +16, -32, 0 }, 0, {    0, 1024 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { +80, -32, 0 }, 0, { 1024, 1024 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { +80, +32, 0 }, 0, { 1024,    0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
    { { { +16, +32, 0 }, 0, {    0,    0 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
};

#define define_dl_billboard_num3(type, digit, offset) \
const Gfx dl_billboard_num3_##type[] = { \
    gsSPDisplayList(dl_billboard_num_begin), \
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_hud_char_##digit), \
    gsDPLoadSync(), \
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)), \
    gsSPVertex(vertex_billboard_num3 + (4 * (offset)), 4, 0), \
    gsSPDisplayList(dl_billboard_num_end + 1), \
    gsSPEndDisplayList(), \
};

define_dl_billboard_num3(0, 0, 0);
define_dl_billboard_num3(1, 1, 0);
define_dl_billboard_num3(2, 2, 0);
define_dl_billboard_num3(3, 3, 0);
define_dl_billboard_num3(4, 4, 0);
define_dl_billboard_num3(5, 5, 0);
define_dl_billboard_num3(6, 6, 0);
define_dl_billboard_num3(7, 7, 0);
define_dl_billboard_num3(8, 8, 0);
define_dl_billboard_num3(9, 9, 0);
define_dl_billboard_num3(0x, 0, 1);
define_dl_billboard_num3(1x, 1, 1);
define_dl_billboard_num3(2x, 2, 1);
define_dl_billboard_num3(3x, 3, 1);
define_dl_billboard_num3(4x, 4, 1);
define_dl_billboard_num3(5x, 5, 1);
define_dl_billboard_num3(6x, 6, 1);
define_dl_billboard_num3(7x, 7, 1);
define_dl_billboard_num3(8x, 8, 1);
define_dl_billboard_num3(9x, 9, 1);
define_dl_billboard_num3(x0, 0, 2);
define_dl_billboard_num3(x1, 1, 2);
define_dl_billboard_num3(x2, 2, 2);
define_dl_billboard_num3(x3, 3, 2);
define_dl_billboard_num3(x4, 4, 2);
define_dl_billboard_num3(x5, 5, 2);
define_dl_billboard_num3(x6, 6, 2);
define_dl_billboard_num3(x7, 7, 2);
define_dl_billboard_num3(x8, 8, 2);
define_dl_billboard_num3(x9, 9, 2);
define_dl_billboard_num3(0xx, 0, 3);
define_dl_billboard_num3(1xx, 1, 3);
define_dl_billboard_num3(2xx, 2, 3);
define_dl_billboard_num3(3xx, 3, 3);
define_dl_billboard_num3(4xx, 4, 3);
define_dl_billboard_num3(5xx, 5, 3);
define_dl_billboard_num3(6xx, 6, 3);
define_dl_billboard_num3(7xx, 7, 3);
define_dl_billboard_num3(8xx, 8, 3);
define_dl_billboard_num3(9xx, 9, 3);
define_dl_billboard_num3(x0x, 0, 4);
define_dl_billboard_num3(x1x, 1, 4);
define_dl_billboard_num3(x2x, 2, 4);
define_dl_billboard_num3(x3x, 3, 4);
define_dl_billboard_num3(x4x, 4, 4);
define_dl_billboard_num3(x5x, 5, 4);
define_dl_billboard_num3(x6x, 6, 4);
define_dl_billboard_num3(x7x, 7, 4);
define_dl_billboard_num3(x8x, 8, 4);
define_dl_billboard_num3(x9x, 9, 4);
define_dl_billboard_num3(xx0, 0, 5);
define_dl_billboard_num3(xx1, 1, 5);
define_dl_billboard_num3(xx2, 2, 5);
define_dl_billboard_num3(xx3, 3, 5);
define_dl_billboard_num3(xx4, 4, 5);
define_dl_billboard_num3(xx5, 5, 5);
define_dl_billboard_num3(xx6, 6, 5);
define_dl_billboard_num3(xx7, 7, 5);
define_dl_billboard_num3(xx8, 8, 5);
define_dl_billboard_num3(xx9, 9, 5);

ROM_ASSET_LOAD_TEXTURE(texture_shadow_quarter_circle, "textures/segment2/shadow_quarter_circle.ia8.inc.c", 0x00108a40, 48390, 0x000120b8, 256);

ROM_ASSET_LOAD_TEXTURE(texture_shadow_quarter_square, "textures/segment2/shadow_quarter_square.ia8.inc.c", 0x00108a40, 48390, 0x000121b8, 256);

ROM_ASSET_LOAD_TEXTURE(texture_transition_star_half, "textures/segment2/segment2.0F458.ia8.inc.c", 0x00108a40, 48390, 0x000122b8, 2048);

ROM_ASSET_LOAD_TEXTURE(texture_transition_circle_half, "textures/segment2/segment2.0FC58.ia8.inc.c", 0x00108a40, 48390, 0x00012ab8, 2048);

ROM_ASSET_LOAD_TEXTURE(texture_transition_mario, "textures/segment2/segment2.10458.ia8.inc.c", 0x00108a40, 48390, 0x000132b8, 4096);

ROM_ASSET_LOAD_TEXTURE(texture_transition_bowser_half, "textures/segment2/segment2.11458.ia8.inc.c", 0x00108a40, 48390, 0x000142b8, 2048);

ROM_ASSET_LOAD_TEXTURE(texture_waterbox_water, "textures/segment2/segment2.11C58.rgba16.inc.c", 0x00108a40, 48390, 0x00014ab8, 2048);

ROM_ASSET_LOAD_TEXTURE(texture_waterbox_jrb_water, "textures/segment2/segment2.12458.rgba16.inc.c", 0x00108a40, 48390, 0x000152b8, 2048);

ROM_ASSET_LOAD_TEXTURE(texture_waterbox_unknown_water, "textures/segment2/segment2.12C58.rgba16.inc.c", 0x00108a40, 48390, 0x00015ab8, 2048);

ROM_ASSET_LOAD_TEXTURE(texture_waterbox_mist, "textures/segment2/segment2.13458.ia16.inc.c", 0x00108a40, 48390, 0x000162b8, 2048);

ROM_ASSET_LOAD_TEXTURE(texture_waterbox_lava, "textures/segment2/segment2.13C58.rgba16.inc.c", 0x00108a40, 48390, 0x00016ab8, 2048);

// Unreferenced light group
static const Lights1 segment2_lights_unused = gdSPDefLights1(
    0x40, 0x40, 0x40,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x02014470 - 0x020144B0
static const Mtx matrix_identity = {
    {{1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f}}
};


// 0x020144B0 - 0x020144F0
static const Mtx matrix_fullscreen = {
    {{2.0f / SCREEN_WIDTH, 0.0f, 0.0f, 0.0f},
    {0.0f, 2.0f / SCREEN_HEIGHT, 0.0f, 0.0f},
    {0.0f, 0.0f, -1.0f, 0.0f},
    {-1.0f, -1.0f, -1.0f, 1.0f}}
};


// 0x020144F0 - 0x02014508
const Gfx dl_draw_quad_verts_0123[] = {
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x02014508 - 0x02014520
const Gfx dl_draw_quad_verts_4567[] = {
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

const Gfx dl_shadow_begin[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

const Gfx dl_shadow_circle[] = {
    gsSPDisplayList(dl_shadow_begin),
    gsDPLoadTextureBlock(texture_shadow_quarter_circle, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0, G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPEndDisplayList(),
};

const Gfx dl_shadow_square[] = {
    gsSPDisplayList(dl_shadow_begin),
    gsDPLoadTextureBlock(texture_shadow_quarter_square, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0, G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPEndDisplayList(),
};

extern ALIGNED8 const Texture texture_shadow_spike_ext[];
const Gfx dl_shadow_spike_ext[] = {
    gsSPDisplayList(dl_shadow_begin),
    gsDPLoadTextureBlock(texture_shadow_spike_ext, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0, G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPEndDisplayList(),
};

// 0x020145D8 - 0x02014620
const Gfx dl_shadow_9_verts[] = {
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  4,  1, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  4,  8,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x02014620 - 0x02014638
const Gfx dl_shadow_4_verts[] = {
    gsSP2Triangles( 0,  2,  1, 0x0,  1,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x02014638 - 0x02014660
const Gfx dl_shadow_end[] = {
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x02014660 - 0x02014698
const Gfx dl_proj_mtx_fullscreen[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPMatrix(&matrix_identity, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPMatrix(&matrix_fullscreen, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH),
    gsSPMatrix(&matrix_identity, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPPerspNormalize(0xFFFF),
    gsSPEndDisplayList(),
};

// 0x02014698 - 0x020146C0
const Gfx dl_screen_transition_end[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsSPEndDisplayList(),
};

// 0x020146C0 - 0x02014708
const Gfx dl_transition_draw_filled_region[] = {
    gsSP2Triangles( 0,  4,  1, 0x0,  1,  4,  5, 0x0),
    gsSP2Triangles( 1,  5,  2, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 2,  6,  7, 0x0,  2,  7,  3, 0x0),
    gsSP2Triangles( 3,  4,  0, 0x0,  3,  7,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x02014708 - 0x02014738
const Gfx dl_skybox_begin[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPPerspNormalize(0xFFFF),
    gsSPMatrix(&matrix_identity, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPEndDisplayList(),
};

// 0x02014738 - 0x02014768
const Gfx dl_skybox_tile_tex_settings[] = {
    gsSPMatrix(&matrix_identity, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x02014768 - 0x02014790
const Gfx dl_skybox_end[] = {
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x02014790 - 0x020147D0
const Gfx dl_waterbox_rgba16_begin[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x020147D0 - 0x02014810
const Gfx dl_waterbox_ia16_begin[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x02014810 - 0x02014838
const Gfx dl_waterbox_end[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x02014838 - 0x02014878
ROM_ASSET_LOAD_TEXTURE(texture_ia8_up_arrow, "textures/segment2/segment2.14838.ia8.inc.c", 0x00108a40, 48390, 0x00017698, 64);

// 0x02014878 - 0x020148B0
const Gfx dl_ia8_up_arrow_begin[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_NOOP2),
    gsSPPerspNormalize(0xFFFF),
    gsSPMatrix(&matrix_identity, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH),
    gsSPEndDisplayList(),
};

// 0x020148B0 - 0x020148E0
// Unused, seems to be an early DL for the power meter, seeing that is loading a 64x32 texture
const Gfx dl_rgba16_unused[] = {
    gsSPMatrix(&matrix_identity, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

// 0x020148E0 - 0x02014938
const Gfx dl_ia8_up_arrow_load_texture_block[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 1, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 3, G_TX_NOLOD, G_TX_CLAMP, 3, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (8 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 1, texture_ia8_up_arrow),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 8 * 8 - 1, CALC_DXT(8, G_IM_SIZ_8b_BYTES)),
    gsSPEndDisplayList(),
};

// 0x02014938 - 0x02014958
const Gfx dl_ia8_up_arrow_end[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x02014958 - 0x02014960
static const Lights1 seg2_lights_02014958 = gdSPDefLights1(
    0x50, 0x50, 0x50,
    0xff, 0xff, 0xff, 0x32, 0x32, 0x32
);

// 0x02014970 - 0x020149A8
const Gfx dl_paintings_rippling_begin[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPLight(&seg2_lights_02014958.l, 1),
    gsSPLight(&seg2_lights_02014958.a, 2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

// 0x020149A8 - 0x020149C8
const Gfx dl_paintings_rippling_end[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x020149C8 - 0x02014A00
const Gfx dl_paintings_env_mapped_begin[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING | G_TEXTURE_GEN),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsSPLight(&seg2_lights_02014958.l, 1),
    gsSPLight(&seg2_lights_02014958.a, 2),
    gsSPTexture(0x4000, 0x4000, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

// 0x02014A00 - 0x02014A30
const Gfx dl_paintings_env_mapped_end[] = {
    gsSPTexture(0x4000, 0x4000, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPGeometryModeSetFirst(G_TEXTURE_GEN, G_LIGHTING),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x02014A30 - 0x02014A60
const Gfx dl_paintings_draw_ripples[] = {
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 14A60: triangle mesh
// 0x02014A60
const s16 seg2_painting_triangle_mesh[] = {
    157, // numVtx
    // format:
    // 2D point (x, y), ripple (0 or 1)
    614, 583,   0, // 0
    614, 614,   0, // 1
    562, 614,   0, // 2
    562, 553,   1, // 3
    614, 522,   0, // 4
    511, 583,   1, // 5
    511, 614,   0, // 6
    307, 614,   0, // 7
    307, 583,   1, // 8
    358, 614,   0, // 9
    256, 614,   0, // 10
    256, 553,   1, // 11
    307, 522,   1, // 12
    358, 553,   1, // 13
    409, 583,   1, // 14
    460, 614,   0, // 15
    511, 522,   1, // 16
    460, 553,   1, // 17
    409, 522,   1, // 18
    562, 307,   1, // 19
    614, 338,   0, // 20
    562, 430,   1, // 21
    614, 399,   0, // 22
    562, 368,   1, // 23
    511, 338,   1, // 24
    460, 307,   1, // 25
    460, 430,   1, // 26
    511, 399,   1, // 27
    511, 460,   1, // 28
    409, 338,   1, // 29
    460, 368,   1, // 30
    358, 307,   1, // 31
    409, 460,   1, // 32
    358, 430,   1, // 33
    409, 399,   1, // 34
    358, 368,   1, // 35
    307, 338,   1, // 36
    256, 307,   1, // 37
    307, 399,   1, // 38
    256, 430,   1, // 39
    307, 460,   1, // 40
    614, 460,   0, // 41
    562, 491,   1, // 42
    460, 491,   1, // 43
    358, 491,   1, // 44
    256, 491,   1, // 45
    409, 276,   1, // 46
    511, 276,   1, // 47
    307, 276,   1, // 48
    614,  31,   0, // 49
    614,   0,   0, // 50
    562,   0,   0, // 51
    562, 123,   1, // 52
    614,  92,   0, // 53
    511,  31,   1, // 54
    562,  61,   1, // 55
    460,   0,   0, // 56
    511,   0,   0, // 57
    460, 123,   1, // 58
    511,  92,   1, // 59
    511, 153,   1, // 60
    409,  31,   1, // 61
    460,  61,   1, // 62
    358,   0,   0, // 63
    409,   0,   0, // 64
    409,  92,   1, // 65
    358, 123,   1, // 66
    409, 153,   1, // 67
    307,  31,   1, // 68
    358,  61,   1, // 69
    256,   0,   0, // 70
    307,   0,   0, // 71
    256, 123,   1, // 72
    307,  92,   1, // 73
    307, 153,   1, // 74
    614, 153,   0, // 75
    562, 246,   1, // 76
    614, 215,   0, // 77
    562, 184,   1, // 78
    460, 246,   1, // 79
    511, 215,   1, // 80
    460, 184,   1, // 81
    358, 246,   1, // 82
    409, 215,   1, // 83
    358, 184,   1, // 84
    256, 246,   1, // 85
    307, 215,   1, // 86
    205, 583,   1, // 87
      0, 614,   0, // 88
      0, 583,   0, // 89
     51, 614,   0, // 90
     51, 553,   1, // 91
    102, 583,   1, // 92
    205, 522,   1, // 93
    153, 553,   1, // 94
    153, 614,   0, // 95
    102, 522,   1, // 96
    256, 368,   1, // 97
    205, 338,   1, // 98
    153, 307,   1, // 99
    153, 430,   1, // 100
    205, 399,   1, // 101
    205, 460,   1, // 102
    153, 368,   1, // 103
    102, 338,   1, // 104
     51, 307,   1, // 105
     51, 430,   1, // 106
    102, 399,   1, // 107
    102, 460,   1, // 108
     51, 368,   1, // 109
      0, 338,   0, // 110
      0, 460,   0, // 111
    153, 491,   1, // 112
     51, 491,   1, // 113
    153, 246,   1, // 114
    102, 276,   1, // 115
    205, 276,   1, // 116
      0, 276,   0, // 117
     51, 246,   1, // 118
    205,  31,   1, // 119
    256,  61,   1, // 120
    205,   0,   0, // 121
    153,   0,   0, // 122
    205, 153,   1, // 123
    205,  92,   1, // 124
    153, 123,   1, // 125
    102,  31,   1, // 126
    153,  61,   1, // 127
    102,   0,   0, // 128
     51,   0,   0, // 129
     51, 123,   1, // 130
    102,  92,   1, // 131
    102, 153,   1, // 132
      0,  31,   0, // 133
     51,  61,   1, // 134
      0, 153,   0, // 135
    256, 184,   1, // 136
    205, 215,   1, // 137
    153, 184,   1, // 138
    102, 215,   1, // 139
     51, 184,   1, // 140
    409, 614,   0, // 141
    614, 307,   0, // 142
    614, 276,   0, // 143
    511, 307,   1, // 144
    409, 307,   1, // 145
    307, 307,   1, // 146
    205, 614,   0, // 147
      0, 522,   0, // 148
    102, 614,   0, // 149
    205, 307,   1, // 150
    102, 307,   1, // 151
      0, 399,   0, // 152
      0, 307,   0, // 153
      0, 215,   0, // 154
      0,  92,   0, // 155
      0,   0,   0, // 156
    // triangles
    264,
      8,  12,  13, // 0
      0,   1,   2, // 1
      3,   0,   2, // 2
      4,   0,   3, // 3
      5,   2,   6, // 4
      2,   5,   3, // 5
      7,   8,   9, // 6
      8,   7,  10, // 7
     11,   8,  10, // 8
     12,   8,  11, // 9
      9,   8,  13, // 10
     13,  14,   9, // 11
     14, 141,   9, // 12
      5,   6,  15, // 13
      5,  16,   3, // 14
     16,   5,  17, // 15
     17,   5,  15, // 16
     14,  15, 141, // 17
     15,  14,  17, // 18
     18,  14,  13, // 19
     14,  18,  17, // 20
     19, 142,  20, // 21
     19,  20,  23, // 22
     28,  27,  21, // 23
     21,  23,  22, // 24
     22,  41,  21, // 25
     20,  22,  23, // 26
     23,  24,  19, // 27
     21,  27,  23, // 28
     24,  23,  27, // 29
     25, 144,  24, // 30
     19,  24, 144, // 31
     24,  27,  30, // 32
     25,  24,  30, // 33
     26,  30,  27, // 34
     27,  28,  26, // 35
     36,  38,  97, // 36
     26,  34,  30, // 37
     29,  30,  34, // 38
     30,  29,  25, // 39
     25,  29, 145, // 40
     31, 145,  29, // 41
     31,  29,  35, // 42
     29,  34,  35, // 43
     32,  34,  26, // 44
     33,  35,  34, // 45
     34,  32,  33, // 46
     33,  38,  35, // 47
     35,  36,  31, // 48
     36,  35,  38, // 49
     37,  36,  97, // 50
     37, 146,  36, // 51
     31,  36, 146, // 52
     28,  16,  43, // 53
     38,  40,  39, // 54
     39,  97,  38, // 55
     40,  38,  33, // 56
     21,  41,  42, // 57
     41,   4,  42, // 58
      3,  42,   4, // 59
     42,  28,  21, // 60
     28,  42,  16, // 61
      3,  16,  42, // 62
     26,  28,  43, // 63
     17,  43,  16, // 64
     43,  32,  26, // 65
     32,  43,  18, // 66
     17,  18,  43, // 67
     33,  32,  44, // 68
     32,  18,  44, // 69
     13,  44,  18, // 70
     44,  40,  33, // 71
     13,  12,  44, // 72
     40,  44,  12, // 73
     39,  40,  45, // 74
     40,  12,  45, // 75
     48,  31, 146, // 76
     11,  45,  12, // 77
     25,  47, 144, // 78
     46,  25, 145, // 79
     47,  19, 144, // 80
     19, 143, 142, // 81
     31,  46, 145, // 82
     60,  59,  52, // 83
     49,  53,  55, // 84
     50,  49,  51, // 85
     51,  49,  55, // 86
     52,  55,  53, // 87
     53,  75,  52, // 88
     54,  55,  59, // 89
     52,  59,  55, // 90
     55,  54,  51, // 91
     54,  59,  62, // 92
     56,  54,  62, // 93
     57,  54,  56, // 94
     54,  57,  51, // 95
     58,  62,  59, // 96
     59,  60,  58, // 97
     68,  71,  63, // 98
     61,  62,  65, // 99
     58,  65,  62, // 100
     62,  61,  56, // 101
     61,  65,  69, // 102
     63,  61,  69, // 103
     64,  61,  63, // 104
     61,  64,  56, // 105
     65,  67,  66, // 106
     66,  69,  65, // 107
     67,  65,  58, // 108
     68,  69,  73, // 109
     69,  68,  63, // 110
     66,  73,  69, // 111
     68,  73, 120, // 112
     70,  68, 120, // 113
     71,  68,  70, // 114
     72, 120,  73, // 115
     73,  74,  72, // 116
     74,  73,  66, // 117
     75,  77,  78, // 118
     52,  75,  78, // 119
     76,  78,  77, // 120
     77, 143,  76, // 121
     76,  80,  78, // 122
     60,  78,  80, // 123
     78,  60,  52, // 124
     46,  83,  79, // 125
     58,  60,  81, // 126
     60,  80,  81, // 127
     79,  81,  80, // 128
     80,  47,  79, // 129
     47,  80,  76, // 130
     81,  67,  58, // 131
     67,  81,  83, // 132
     79,  83,  81, // 133
     66,  67,  84, // 134
     67,  83,  84, // 135
     82,  84,  83, // 136
     83,  46,  82, // 137
     84,  74,  66, // 138
     82,  86,  84, // 139
     74,  84,  86, // 140
     74,  86, 136, // 141
     72,  74, 136, // 142
     85, 136,  86, // 143
     86,  48,  85, // 144
     48,  86,  82, // 145
     25,  46,  79, // 146
     79,  47,  25, // 147
     82,  46,  31, // 148
     19,  47,  76, // 149
     76, 143,  19, // 150
     31,  48,  82, // 151
     37,  48, 146, // 152
     85,  48,  37, // 153
     10,  87,  11, // 154
     87,  10, 147, // 155
     92,  95, 149, // 156
     88,  89,  90, // 157
     89, 148,  91, // 158
     90,  89,  91, // 159
     91,  92,  90, // 160
     92, 149,  90, // 161
     93,  87,  94, // 162
     87,  93,  11, // 163
     94,  87,  95, // 164
     87, 147,  95, // 165
     95,  92,  94, // 166
     96,  92,  91, // 167
     92,  96,  94, // 168
     39, 101,  97, // 169
     97,  98,  37, // 170
     98,  97, 101, // 171
     99,  98, 103, // 172
     99, 150,  98, // 173
     37,  98, 150, // 174
     98, 101, 103, // 175
    100, 103, 101, // 176
    101, 102, 100, // 177
    102, 101,  39, // 178
    100, 107, 103, // 179
    103, 104,  99, // 180
    104, 103, 107, // 181
    105, 104, 109, // 182
    105, 151, 104, // 183
     99, 104, 151, // 184
    104, 107, 109, // 185
    106, 109, 107, // 186
    107, 108, 106, // 187
    108, 107, 100, // 188
    109, 110, 105, // 189
    106, 152, 109, // 190
    110, 109, 152, // 191
    105, 110, 153, // 192
    111, 152, 106, // 193
     11,  93,  45, // 194
    102,  45,  93, // 195
     45, 102,  39, // 196
    102,  93, 112, // 197
    100, 102, 112, // 198
     94, 112,  93, // 199
    112, 108, 100, // 200
    108, 112,  96, // 201
     94,  96, 112, // 202
    106, 108, 113, // 203
    108,  96, 113, // 204
     91, 113,  96, // 205
     91, 148, 113, // 206
    113, 111, 106, // 207
    111, 113, 148, // 208
    114, 116,  99, // 209
     99, 115, 114, // 210
    115,  99, 151, // 211
     99, 116, 150, // 212
     72, 124, 120, // 213
    116,  37, 150, // 214
     37, 116,  85, // 215
    117, 105, 153, // 216
    105, 115, 151, // 217
    105, 117, 118, // 218
    118, 115, 105, // 219
    119, 120, 124, // 220
    120, 119,  70, // 221
    119, 124, 127, // 222
    119, 121,  70, // 223
    121, 119, 122, // 224
    122, 119, 127, // 225
    123, 124,  72, // 226
    124, 123, 125, // 227
    125, 127, 124, // 228
    126, 127, 131, // 229
    127, 126, 122, // 230
    125, 131, 127, // 231
    126, 131, 134, // 232
    128, 126, 129, // 233
    129, 126, 134, // 234
    126, 128, 122, // 235
    136, 123,  72, // 236
    130, 134, 131, // 237
    131, 132, 130, // 238
    132, 131, 125, // 239
    133, 134, 155, // 240
    134, 133, 129, // 241
    130, 155, 134, // 242
    133, 156, 129, // 243
    135, 155, 130, // 244
    123, 136, 137, // 245
     85, 137, 136, // 246
    139, 115, 118, // 247
    123, 137, 138, // 248
    125, 123, 138, // 249
    114, 138, 137, // 250
    137, 116, 114, // 251
    116, 137,  85, // 252
    114, 139, 138, // 253
    132, 138, 139, // 254
    138, 132, 125, // 255
    132, 139, 140, // 256
    130, 132, 140, // 257
    115, 139, 114, // 258
    118, 140, 139, // 259
    135, 140, 154, // 260
    118, 154, 140, // 261
    140, 135, 130, // 262
    117, 154, 118, // 263
};

/* 0x02015444: seg2_painting_mesh_neighbor_tris
 * Lists the neighboring triangles for each vertex in the mesh.
 * Used when applying gouraud shading to the generated ripple mesh
 *
 * Format:
 *      num neighbors, neighbor0, neighbor1, ...
 * The nth entry corresponds to the nth vertex in seg2_painting_triangle_mesh
 */
const s16 seg2_painting_mesh_neighbor_tris[] = {
      3,   1,   2,   3,
      1,   1,
      4,   1,   2,   4,   5,
      6,   2,   3,   5,  14,  59,  62,
      3,   3,  58,  59,
      6,   4,   5,  13,  14,  15,  16,
      2,   4,  13,
      2,   6,   7,
      6,   0,   6,   7,   8,   9,  10,
      4,   6,  10,  11,  12,
      4,   7,   8, 154, 155,
      6,   8,   9,  77, 154, 163, 194,
      6,   0,   9,  72,  73,  75,  77,
      6,   0,  10,  11,  19,  70,  72,
      6,  11,  12,  17,  18,  19,  20,
      4,  13,  16,  17,  18,
      6,  14,  15,  53,  61,  62,  64,
      6,  15,  16,  18,  20,  64,  67,
      6,  19,  20,  66,  67,  69,  70,
      8,  21,  22,  27,  31,  80,  81, 149, 150,
      3,  21,  22,  26,
      6,  23,  24,  25,  28,  57,  60,
      3,  24,  25,  26,
      6,  22,  24,  26,  27,  28,  29,
      6,  27,  29,  30,  31,  32,  33,
      8,  30,  33,  39,  40,  78,  79, 146, 147,
      6,  34,  35,  37,  44,  63,  65,
      6,  23,  28,  29,  32,  34,  35,
      6,  23,  35,  53,  60,  61,  63,
      6,  38,  39,  40,  41,  42,  43,
      6,  32,  33,  34,  37,  38,  39,
      8,  41,  42,  48,  52,  76,  82, 148, 151,
      6,  44,  46,  65,  66,  68,  69,
      6,  45,  46,  47,  56,  68,  71,
      6,  37,  38,  43,  44,  45,  46,
      6,  42,  43,  45,  47,  48,  49,
      6,  36,  48,  49,  50,  51,  52,
      8,  50,  51, 152, 153, 170, 174, 214, 215,
      6,  36,  47,  49,  54,  55,  56,
      6,  54,  55,  74, 169, 178, 196,
      6,  54,  56,  71,  73,  74,  75,
      3,  25,  57,  58,
      6,  57,  58,  59,  60,  61,  62,
      6,  53,  63,  64,  65,  66,  67,
      6,  68,  69,  70,  71,  72,  73,
      6,  74,  75,  77, 194, 195, 196,
      6,  79,  82, 125, 137, 146, 148,
      6,  78,  80, 129, 130, 147, 149,
      6,  76, 144, 145, 151, 152, 153,
      3,  84,  85,  86,
      1,  85,
      4,  85,  86,  91,  95,
      6,  83,  87,  88,  90, 119, 124,
      3,  84,  87,  88,
      6,  89,  91,  92,  93,  94,  95,
      6,  84,  86,  87,  89,  90,  91,
      4,  93,  94, 101, 105,
      2,  94,  95,
      6,  96,  97, 100, 108, 126, 131,
      6,  83,  89,  90,  92,  96,  97,
      6,  83,  97, 123, 124, 126, 127,
      6,  99, 101, 102, 103, 104, 105,
      6,  92,  93,  96,  99, 100, 101,
      4,  98, 103, 104, 110,
      2, 104, 105,
      6,  99, 100, 102, 106, 107, 108,
      6, 106, 107, 111, 117, 134, 138,
      6, 106, 108, 131, 132, 134, 135,
      6,  98, 109, 110, 112, 113, 114,
      6, 102, 103, 107, 109, 110, 111,
      4, 113, 114, 221, 223,
      2,  98, 114,
      6, 115, 116, 142, 213, 226, 236,
      6, 109, 111, 112, 115, 116, 117,
      6, 116, 117, 138, 140, 141, 142,
      3,  88, 118, 119,
      6, 120, 121, 122, 130, 149, 150,
      3, 118, 120, 121,
      6, 118, 119, 120, 122, 123, 124,
      6, 125, 128, 129, 133, 146, 147,
      6, 122, 123, 127, 128, 129, 130,
      6, 126, 127, 128, 131, 132, 133,
      6, 136, 137, 139, 145, 148, 151,
      6, 125, 132, 133, 135, 136, 137,
      6, 134, 135, 136, 138, 139, 140,
      6, 143, 144, 153, 215, 246, 252,
      6, 139, 140, 141, 143, 144, 145,
      6, 154, 155, 162, 163, 164, 165,
      1, 157,
      3, 157, 158, 159,
      4, 157, 159, 160, 161,
      6, 158, 159, 160, 167, 205, 206,
      6, 156, 160, 161, 166, 167, 168,
      6, 162, 163, 194, 195, 197, 199,
      6, 162, 164, 166, 168, 199, 202,
      4, 156, 164, 165, 166,
      6, 167, 168, 201, 202, 204, 205,
      6,  36,  50,  55, 169, 170, 171,
      6, 170, 171, 172, 173, 174, 175,
      8, 172, 173, 180, 184, 209, 210, 211, 212,
      6, 176, 177, 179, 188, 198, 200,
      6, 169, 171, 175, 176, 177, 178,
      6, 177, 178, 195, 196, 197, 198,
      6, 172, 175, 176, 179, 180, 181,
      6, 180, 181, 182, 183, 184, 185,
      8, 182, 183, 189, 192, 216, 217, 218, 219,
      6, 186, 187, 190, 193, 203, 207,
      6, 179, 181, 185, 186, 187, 188,
      6, 187, 188, 200, 201, 203, 204,
      6, 182, 185, 186, 189, 190, 191,
      3, 189, 191, 192,
      3, 193, 207, 208,
      6, 197, 198, 199, 200, 201, 202,
      6, 203, 204, 205, 206, 207, 208,
      6, 209, 210, 250, 251, 253, 258,
      6, 210, 211, 217, 219, 247, 258,
      6, 209, 212, 214, 215, 251, 252,
      3, 216, 218, 263,
      6, 218, 219, 247, 259, 261, 263,
      6, 220, 221, 222, 223, 224, 225,
      6, 112, 113, 115, 213, 220, 221,
      2, 223, 224,
      4, 224, 225, 230, 235,
      6, 226, 227, 236, 245, 248, 249,
      6, 213, 220, 222, 226, 227, 228,
      6, 227, 228, 231, 239, 249, 255,
      6, 229, 230, 232, 233, 234, 235,
      6, 222, 225, 228, 229, 230, 231,
      2, 233, 235,
      4, 233, 234, 241, 243,
      6, 237, 238, 242, 244, 257, 262,
      6, 229, 231, 232, 237, 238, 239,
      6, 238, 239, 254, 255, 256, 257,
      3, 240, 241, 243,
      6, 232, 234, 237, 240, 241, 242,
      3, 244, 260, 262,
      6, 141, 142, 143, 236, 245, 246,
      6, 245, 246, 248, 250, 251, 252,
      6, 248, 249, 250, 253, 254, 255,
      6, 247, 253, 254, 256, 258, 259,
      6, 256, 257, 259, 260, 261, 262,
      2,  12,  17,
      2,  21,  81,
      3,  81, 121, 150,
      4,  30,  31,  78,  80,
      4,  40,  41,  79,  82,
      4,  51,  52,  76, 152,
      2, 155, 165,
      3, 158, 206, 208,
      2, 156, 161,
      4, 173, 174, 212, 214,
      4, 183, 184, 211, 217,
      3, 190, 191, 193,
      2, 192, 216,
      3, 260, 261, 263,
      3, 240, 242, 244,
      1, 243,
};
