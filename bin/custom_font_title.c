#include <ultra64.h>
#include "sm64.h"
#include "game/ingame_menu.h"
#include "make_const_nonconst.h"

ALIGNED8 static const u8 texture_font_title_char_01[] = {
#include "textures/custom_font_title/custom_font_title_01.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_02[] = {
#include "textures/custom_font_title/custom_font_title_02.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_03[] = {
#include "textures/custom_font_title/custom_font_title_03.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_04[] = {
#include "textures/custom_font_title/custom_font_title_04.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_05[] = {
#include "textures/custom_font_title/custom_font_title_05.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_06[] = {
#include "textures/custom_font_title/custom_font_title_06.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_07[] = {
#include "textures/custom_font_title/custom_font_title_07.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_08[] = {
#include "textures/custom_font_title/custom_font_title_08.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_09[] = {
#include "textures/custom_font_title/custom_font_title_09.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_10[] = {
#include "textures/custom_font_title/custom_font_title_10.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_11[] = {
#include "textures/custom_font_title/custom_font_title_11.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_12[] = {
#include "textures/custom_font_title/custom_font_title_12.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_13[] = {
#include "textures/custom_font_title/custom_font_title_13.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_14[] = {
#include "textures/custom_font_title/custom_font_title_14.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_15[] = {
#include "textures/custom_font_title/custom_font_title_15.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_16[] = {
#include "textures/custom_font_title/custom_font_title_16.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_17[] = {
#include "textures/custom_font_title/custom_font_title_17.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_18[] = {
#include "textures/custom_font_title/custom_font_title_18.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_19[] = {
#include "textures/custom_font_title/custom_font_title_19.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_20[] = {
#include "textures/custom_font_title/custom_font_title_20.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_21[] = {
#include "textures/custom_font_title/custom_font_title_21.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_22[] = {
#include "textures/custom_font_title/custom_font_title_22.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_23[] = {
#include "textures/custom_font_title/custom_font_title_23.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_24[] = {
#include "textures/custom_font_title/custom_font_title_24.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_25[] = {
#include "textures/custom_font_title/custom_font_title_25.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_26[] = {
#include "textures/custom_font_title/custom_font_title_26.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_27[] = {
#include "textures/custom_font_title/custom_font_title_27.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_28[] = {
#include "textures/custom_font_title/custom_font_title_28.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_29[] = {
#include "textures/custom_font_title/custom_font_title_29.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_30[] = {
#include "textures/custom_font_title/custom_font_title_30.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_31[] = {
#include "textures/custom_font_title/custom_font_title_31.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_32[] = {
#include "textures/custom_font_title/custom_font_title_32.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_33[] = {
#include "textures/custom_font_title/custom_font_title_33.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_34[] = {
#include "textures/custom_font_title/custom_font_title_34.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_35[] = {
#include "textures/custom_font_title/custom_font_title_35.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_36[] = {
#include "textures/custom_font_title/custom_font_title_36.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_37[] = {
#include "textures/custom_font_title/custom_font_title_37.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_38[] = {
#include "textures/custom_font_title/custom_font_title_38.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_39[] = {
#include "textures/custom_font_title/custom_font_title_39.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_40[] = {
#include "textures/custom_font_title/custom_font_title_40.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_41[] = {
#include "textures/custom_font_title/custom_font_title_41.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_42[] = {
#include "textures/custom_font_title/custom_font_title_42.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_43[] = {
#include "textures/custom_font_title/custom_font_title_43.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_44[] = {
#include "textures/custom_font_title/custom_font_title_44.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_45[] = {
#include "textures/custom_font_title/custom_font_title_45.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_46[] = {
#include "textures/custom_font_title/custom_font_title_46.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_47[] = {
#include "textures/custom_font_title/custom_font_title_47.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_48[] = {
#include "textures/custom_font_title/custom_font_title_48.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_49[] = {
#include "textures/custom_font_title/custom_font_title_49.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_50[] = {
#include "textures/custom_font_title/custom_font_title_50.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_51[] = {
#include "textures/custom_font_title/custom_font_title_51.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_52[] = {
#include "textures/custom_font_title/custom_font_title_52.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_53[] = {
#include "textures/custom_font_title/custom_font_title_53.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_54[] = {
#include "textures/custom_font_title/custom_font_title_54.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_55[] = {
#include "textures/custom_font_title/custom_font_title_55.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_56[] = {
#include "textures/custom_font_title/custom_font_title_56.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_57[] = {
#include "textures/custom_font_title/custom_font_title_57.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_58[] = {
#include "textures/custom_font_title/custom_font_title_58.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_59[] = {
#include "textures/custom_font_title/custom_font_title_59.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_60[] = {
#include "textures/custom_font_title/custom_font_title_60.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_61[] = {
#include "textures/custom_font_title/custom_font_title_61.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_62[] = {
#include "textures/custom_font_title/custom_font_title_62.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_63[] = {
#include "textures/custom_font_title/custom_font_title_63.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_64[] = {
#include "textures/custom_font_title/custom_font_title_64.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_65[] = {
#include "textures/custom_font_title/custom_font_title_65.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_66[] = {
#include "textures/custom_font_title/custom_font_title_66.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_67[] = {
#include "textures/custom_font_title/custom_font_title_67.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_68[] = {
#include "textures/custom_font_title/custom_font_title_68.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_69[] = {
#include "textures/custom_font_title/custom_font_title_69.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_70[] = {
#include "textures/custom_font_title/custom_font_title_70.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_71[] = {
#include "textures/custom_font_title/custom_font_title_71.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_72[] = {
#include "textures/custom_font_title/custom_font_title_72.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_73[] = {
#include "textures/custom_font_title/custom_font_title_73.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_74[] = {
#include "textures/custom_font_title/custom_font_title_74.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_75[] = {
#include "textures/custom_font_title/custom_font_title_75.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_76[] = {
#include "textures/custom_font_title/custom_font_title_76.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_77[] = {
#include "textures/custom_font_title/custom_font_title_77.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_78[] = {
#include "textures/custom_font_title/custom_font_title_78.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_79[] = {
#include "textures/custom_font_title/custom_font_title_79.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_80[] = {
#include "textures/custom_font_title/custom_font_title_80.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_81[] = {
#include "textures/custom_font_title/custom_font_title_81.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_82[] = {
#include "textures/custom_font_title/custom_font_title_82.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_83[] = {
#include "textures/custom_font_title/custom_font_title_83.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_84[] = {
#include "textures/custom_font_title/custom_font_title_84.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_85[] = {
#include "textures/custom_font_title/custom_font_title_85.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_86[] = {
#include "textures/custom_font_title/custom_font_title_86.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_87[] = {
#include "textures/custom_font_title/custom_font_title_87.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_88[] = {
#include "textures/custom_font_title/custom_font_title_88.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_89[] = {
#include "textures/custom_font_title/custom_font_title_89.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_90[] = {
#include "textures/custom_font_title/custom_font_title_90.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_91[] = {
#include "textures/custom_font_title/custom_font_title_91.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_92[] = {
#include "textures/custom_font_title/custom_font_title_92.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_93[] = {
#include "textures/custom_font_title/custom_font_title_93.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_94[] = {
#include "textures/custom_font_title/custom_font_title_94.rgba32.inc.c"
};

ALIGNED8 static const u8 texture_font_title_char_95[] = {
#include "textures/custom_font_title/custom_font_title_95.rgba32.inc.c"
};

const u8* const font_title_chars[] = {
    texture_font_title_char_01, // !
    texture_font_title_char_02, // "
    texture_font_title_char_03, // #
    texture_font_title_char_04, // $
    texture_font_title_char_05, // %
    texture_font_title_char_06, // &
    texture_font_title_char_07, // '
    texture_font_title_char_08, // (
    texture_font_title_char_09, // )
    texture_font_title_char_10, // *
    texture_font_title_char_11, // +
    texture_font_title_char_12, // ,
    texture_font_title_char_13, // -
    texture_font_title_char_14, // .
    texture_font_title_char_15, // /
    texture_font_title_char_16, // 0
    texture_font_title_char_17, // 1
    texture_font_title_char_18, // 2
    texture_font_title_char_19, // 3
    texture_font_title_char_20, // 4
    texture_font_title_char_21, // 5
    texture_font_title_char_22, // 6
    texture_font_title_char_23, // 7
    texture_font_title_char_24, // 8
    texture_font_title_char_25, // 9
    texture_font_title_char_26, // :
    texture_font_title_char_27, // ;
    texture_font_title_char_28, // <
    texture_font_title_char_29, // =
    texture_font_title_char_30, // >
    texture_font_title_char_31, // ?
    texture_font_title_char_32, // @
    texture_font_title_char_33, // A
    texture_font_title_char_34, // B
    texture_font_title_char_35, // C
    texture_font_title_char_36, // D
    texture_font_title_char_37, // E
    texture_font_title_char_38, // F
    texture_font_title_char_39, // G
    texture_font_title_char_40, // H
    texture_font_title_char_41, // I
    texture_font_title_char_42, // J
    texture_font_title_char_43, // K
    texture_font_title_char_44, // L
    texture_font_title_char_45, // M
    texture_font_title_char_46, // N
    texture_font_title_char_47, // O
    texture_font_title_char_48, // P
    texture_font_title_char_49, // Q
    texture_font_title_char_50, // R
    texture_font_title_char_51, // S
    texture_font_title_char_52, // T
    texture_font_title_char_53, // U
    texture_font_title_char_54, // V
    texture_font_title_char_55, // W
    texture_font_title_char_56, // X
    texture_font_title_char_57, // Y
    texture_font_title_char_58, // Z
    texture_font_title_char_59, // [
    texture_font_title_char_60, // \ //
    texture_font_title_char_61, // ]
    texture_font_title_char_62, // ^
    texture_font_title_char_63, // _
    texture_font_title_char_64, // `
    texture_font_title_char_65, // a
    texture_font_title_char_66, // b
    texture_font_title_char_67, // c
    texture_font_title_char_68, // d
    texture_font_title_char_69, // e
    texture_font_title_char_70, // f
    texture_font_title_char_71, // g
    texture_font_title_char_72, // h
    texture_font_title_char_73, // i
    texture_font_title_char_74, // j
    texture_font_title_char_75, // k
    texture_font_title_char_76, // l
    texture_font_title_char_77, // m
    texture_font_title_char_78, // n
    texture_font_title_char_79, // o
    texture_font_title_char_80, // p
    texture_font_title_char_81, // q
    texture_font_title_char_82, // r
    texture_font_title_char_83, // s
    texture_font_title_char_84, // t
    texture_font_title_char_85, // u
    texture_font_title_char_86, // v
    texture_font_title_char_87, // w
    texture_font_title_char_88, // x
    texture_font_title_char_89, // y
    texture_font_title_char_90, // z
    texture_font_title_char_91, // {
    texture_font_title_char_92, // |
    texture_font_title_char_93, // }
    texture_font_title_char_94, // ~
    texture_font_title_char_95, // DEL
};

const f32 font_title_widths[] = {
/*      !      "      #      $      %      &      '      (      )      *      +      ,      -      .      /      */
    0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f,
/*      0      1      2      3      4      5      6      7      8      9      */
    0.45f, 0.35f, 0.45f, 0.45f, 0.45f, 0.45f, 0.45f, 0.45f, 0.45f, 0.45f,
/*      :      ;      <      =      >      ?      @      */
    0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f,
/*      A      B      C      D      E      F      G      H      I      J      K      L      M      N      O      P      Q      R      S      T      U      V      W      X      Y      Z      */
    0.55f, 0.50f, 0.50f, 0.50f, 0.45f, 0.45f, 0.50f, 0.55f, 0.28f, 0.60f, 0.50f, 0.45f, 0.55f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.55f, 0.50f, 0.50f, 0.50f, 0.60f, 0.52f, 0.60f, 0.45f,
/*      [      \      ]      ^      _      `      */
    0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f,
/*      a      b      c      d      e      f      g      h      i      j      k      l      m      n      o      p      q      r      s      t      u      v      w      x      y      z      */
    0.45f, 0.45f, 0.40f, 0.40f, 0.45f, 0.37f, 0.40f, 0.40f, 0.20f, 0.45f, 0.40f, 0.30f, 0.50f, 0.40f, 0.40f, 0.40f, 0.45f, 0.40f, 0.50f, 0.45f, 0.50f, 0.40f, 0.50f, 0.50f, 0.45f, 0.45f,
/*      {      |      }      ~    DEL      */
    0.50f, 0.50f, 0.50f, 0.50f, 0.50f,
};
