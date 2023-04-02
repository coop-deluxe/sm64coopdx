#include <ultra64.h>
#include "sm64.h"
#include "game/ingame_menu.h"
#include "make_const_nonconst.h"

ALIGNED8 const u8 texture_font_normal[] = {
#include "textures/custom_font/custom_font_normal.rgba32.inc.c"
};

const f32 font_normal_widths[] = {
/*        !        "        #        $        %        &        '        (        )        *        +        ,        -        .        /        */
    0.2200f, 0.3750f, 0.4375f, 0.3750f, 0.4375f, 0.5000f, 0.2500f, 0.3125f, 0.3125f, 0.3750f, 0.4375f, 0.2500f, 0.3750f, 0.2500f, 0.3125f,
/*        0        1        2        3        4        5        6        7        8        9        */
    0.4375f, 0.3800f, 0.4200f, 0.4375f, 0.4300f, 0.4375f, 0.4375f, 0.4000f, 0.4375f, 0.4375f,
/*        :        ;        <        =        >        ?        @         */
    0.2000f, 0.2500f, 0.3125f, 0.3750f, 0.3125f, 0.3125f, 0.5750f,
/*        A        B        C        D        E        F        G        H        I        J        K        L        M        N        O        P        Q        R        S        T        U        V        W        X        Y        Z        */
     0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3125f, 0.3750f, 0.3750f, 0.3125f, 0.3750f, 0.3750f, 0.3125f, 0.5000f, 0.5000f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3750f, 0.3125f, 0.3750f, 0.3750f, 0.5000f, 0.4375f, 0.3750f, 0.3750f,
/*        [        \        ]        ^        _        `        */
    0.3125f, 0.3125f, 0.3125f, 0.3750f, 0.3750f, 0.2500f,
/*        a        b        c        d        e        f        g        h        i        j        k        l        m        n        o        p        q        r        s        t        u        v        w        x        y        z        */
    0.3000f, 0.3125f, 0.3125f, 0.3125f, 0.3125f, 0.3000f, 0.3750f, 0.3125f, 0.2200f, 0.3125f, 0.3125f, 0.1700f, 0.4350f, 0.3125f, 0.3000f, 0.3000f, 0.3125f, 0.2700f, 0.3125f, 0.3125f, 0.3125f, 0.2750f, 0.4375f, 0.3750f, 0.3125f, 0.3125f,
/*        {        |        }        ~      DEL        */
    0.3125f, 0.2500f, 0.3125f, 0.5000f, 0.2000f,
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

ALIGNED8 u8 texture_selectionbox_icon[] = {
#include "textures/segment2/custom_selectionbox_icon.rgba16.inc.c"
};

