#include <ultra64.h>
#include "sm64.h"
#include "game/ingame_menu.h"
#include "make_const_nonconst.h"

ALIGNED8 const u8 texture_font_normal[] = {
#include "textures/custom_font/custom_font_normal.rgba32.inc.c"
};

const f32 font_normal_widths[] = {
/*        !        "        #        $        %        &        '        (        )        *        +        ,        -        .        /        */
    0.3125f, 0.3750f, 0.4375f, 0.3750f, 0.4375f, 0.5000f, 0.2500f, 0.3125f, 0.3125f, 0.3750f, 0.4375f, 0.2500f, 0.3750f, 0.2500f, 0.3125f,
/*        0        1        2        3        4        5        6        7        8        9        */
    0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f,
/*        :        ;        <        =        >        ?        @         */
    0.2500f, 0.2500f, 0.3125f, 0.3750f, 0.3125f, 0.4375f, 0.5750f,
/*        A        B        C        D        E        F        G        H        I        J        K        L        M        N        O        P        Q        R        S        T        U        V        W        X        Y        Z        */
    0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3125f, 0.3750f, 0.3750f, 0.3125f, 0.5000f, 0.5000f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3125f, 0.3750f, 0.3750f, 0.5000f, 0.4375f, 0.3750f, 0.3750f,
/*        [        \        ]        ^        _        `        */
    0.3125f, 0.3125f, 0.3125f, 0.3750f, 0.3750f, 0.2500f,
/*        a        b        c        d        e        f        g        h        i        j        k        l        m        n        o        p        q        r        s        t        u        v        w        x        y        z        */
    0.3750f, 0.3125f, 0.3125f, 0.3750f, 0.3125f, 0.3125f, 0.3750f, 0.3125f, 0.2500f, 0.3125f, 0.3125f, 0.1875f, 0.4375f, 0.3125f, 0.3125f, 0.3125f, 0.3750f, 0.3125f, 0.3125f, 0.3125f, 0.3125f, 0.3125f, 0.4375f, 0.4375f, 0.3125f, 0.3125f,
/*        {        |        }        ~      DEL        */
    0.3125f, 0.2500f, 0.3125f, 0.5000f, 0.5000f
};

//////////////////////////////////////////////////////////

ALIGNED8 const u8 texture_font_title[] = {
#include "textures/custom_font/custom_font_title.rgba32.inc.c"
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

//////////////////////////////////////////////////////////

ALIGNED8 const u8 texture_font_aliased[] = {
#include "textures/custom_font/custom_font_aliased.rgba32.inc.c"
};

const f32 font_aliased_widths[] = {
/*        !        "        #        $        %        &        '        (        )        *        +        ,        -        .        /        */
          7,      12,      14,      12,      14,      16,       8,      10,      10,      12,      14,       8,      12,       8,      10,
/*        0        1        2        3        4        5        6        7        8        9        */
         14,      12,      13,      14,      14,      14,      14,      13,      14,      14,
/*        :        ;        <        =        >        ?        @         */
          6,       8,      10,      12,      10,      11,      18,
/*        A        B        C        D        E        F        G        H        I        J        K        L        M        N        O        P        Q        R        S        T        U        V        W        X        Y        Z        */
         12,      12,      12,      12,      11,      10,      12,      12,       9,      12,      12,      10,      16,      16,      12,      11,      12,      12,      12,      10,      12,      10,      16,      14,      12,      12,
/*        [        \        ]        ^        _        `        */
         10,      10,      10,      12,      12,       8,
/*        a        b        c        d        e        f        g        h        i        j        k        l        m        n        o        p        q        r        s        t        u        v        w        x        y        z        */
         10,      10,      10,      10,       9,       8,      12,      10,       7,       9,      10,       4,      13,      10,       9,       9,      10,       9,      10,       9,      10,       9,      14,      12,      10,      10,
/*        {        |        }        ~      DEL        */
         10,       8,      10,      16,      10,
};

//////////////////////////////////////////////////////////

ALIGNED8 const u8 texture_font_hud[] = {
#include "textures/custom_font/custom_font_hud.rgba32.inc.c"
};

ALIGNED8 const u8 texture_font_hud_recolor[] = {
#include "textures/custom_font/custom_font_hud_recolor.rgba32.inc.c"
};

const f32 font_hud_widths[] = {
/*        !        "        #        $        %        &        '        (        )        *        +        ,        -        .        /        */
    0.2596f, 0.2596f, 0.4615f, 0.3750f, 0.3750f, 0.3750f, 0.1442f, 0.2596f, 0.2596f, 0.3750f, 0.3750f, 0.1442f, 0.3750f, 0.1153f, 0.3750f,
/*        0        1        2        3        4        5        6        7        8        9        */
    0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f,
/*        :        ;        <        =        >        ?        @        */
    0.1442f, 0.1442f, 0.2307f, 0.3750f, 0.2307f, 0.4615f, 0.4615f,
/*        A        B        C        D        E        F        G        H        I        J        K        L        M        N        O        P        Q        R        S        T        U        V        W        X        Y        Z        */
    0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f,
/*        [        \        ]        ^        _        `        */
    0.2596f, 0.3750f, 0.2596f, 0.2019f, 0.4615f, 0.1730f,
/*        a        b        c        d        e        f        g        h        i        j        k        l        m        n        o        p        q        r        s        t        u        v        w        x        y        z        */
    0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f,
/*        {        |        }        ~      DEL        */
    0.2596f, 0.2884f, 0.2596f, 0.4615f, 0.4615f,
};

//////////////////////////////////////////////////////////

ALIGNED8 const u8 texture_font_special[] = {
#include "textures/custom_font/custom_font_special.rgba32.inc.c"
};

const f32 font_special_widths[] = {
/*        !        "        #        $        %        &        '        (        )        *        +        ,        -        .        /        */
    0.1875f, 0.3750f, 0.5000f, 0.4375f, 0.4375f, 0.4375f, 0.2500f, 0.3125f, 0.3125f, 0.2500f, 0.4375f, 0.2500f, 0.3750f, 0.2500f, 0.3125f,
/*        0        1        2        3        4        5        6        7        8        9        */
    0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f,
/*        :        ;        <        =        >        ?        @         */
    0.2500f, 0.2500f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.5625f,
/*        A        B        C        D        E        F        G        H        I        J        K        L        M        N        O        P        Q        R        S        T        U        V        W        X        Y        Z        */
    0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.5000f, 0.5000f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.5000f, 0.4375f, 0.4375f, 0.4375f,
/*        [        \        ]        ^        _        `        */
    0.3125f, 0.3125f, 0.3125f, 0.3750f, 0.4375f, 0.2500f,
/*        a        b        c        d        e        f        g        h        i        j        k        l        m        n        o        p        q        r        s        t        u        v        w        x        y        z        */
    0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.5000f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.4375f, 0.5000f, 0.4375f, 0.4375f, 0.4375f,
/*        {        |        }        ~      DEL        */
    0.3125f, 0.1875f, 0.3125f, 0.4375f, 0.5000f
};

//////////////////////////////////////////////////////////
