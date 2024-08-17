/**
 * @file gbi.h
 * @brief Modded GBI for use with F3DEX3 custom microcode
 * 
 */

#include <PR/mbi.h>

#ifndef F3DEX3_H
#define F3DEX3_H

#define F3DEX_GBI_2  1
#define F3DEX_GBI_PL 1
#define F3DEX_GBI_3  1

#ifdef REQUIRE_SEMICOLONS_AFTER_GBI_COMMANDS
/* OoT style, semicolons required after using macros, cleaner code. If modding
SM64, will have to fix a few places the codebase omits the semicolons. */
#define _DW(macro) do {macro} while (0)
#else
/* SM64 style, semicolons optional, uglier code, will produce tens of thousands
of warnings if you use -Wpedantic. */
#define _DW(macro) macro
#endif

/*
 * The following commands are the "generated" RDP commands; the user
 * never sees them, the RSP microcode generates them.
 *                                    edge, shade, texture, zbuff bits:  estz
 */
#define G_TRI_FILL              0xC8    /* fill triangle:            11001000 */
#define G_TRI_SHADE             0xCC    /* shade triangle:           11001100 */
#define G_TRI_TXTR              0xCA    /* texture triangle:         11001010 */
#define G_TRI_SHADE_TXTR        0xCE    /* shade, texture triangle:  11001110 */
#define G_TRI_FILL_ZBUFF        0xC9    /* fill, zbuff triangle:     11001001 */
#define G_TRI_SHADE_ZBUFF       0xCD    /* shade, zbuff triangle:    11001101 */
#define G_TRI_TXTR_ZBUFF        0xCB    /* texture, zbuff triangle:  11001011 */
#define G_TRI_SHADE_TXTR_ZBUFF  0xCF    /* shade, txtr, zbuff trngl: 11001111 */

/* masks to create the above: */
#define G_RDP_TRI_FILL_MASK     0x08
#define G_RDP_TRI_SHADE_MASK    0x04
#define G_RDP_TRI_TXTR_MASK     0x02
#define G_RDP_TRI_ZBUFF_MASK    0x01

/*
 * GBI commands in order
 */
/*#define G_SPECIAL_3       0xD3  no-op in F3DEX2 */
/*#define G_SPECIAL_2       0xD4  no-op in F3DEX2 */
/*#define G_SPECIAL_1       0xD5  triggered MVP recalculation, not supported in F3DEX3 */
#define G_MEMSET            0xD5
#define G_DMA_IO            0xD6
#define G_TEXTURE           0xD7
#define G_POPMTX            0xD8
#define G_GEOMETRYMODE      0xD9
#define G_MTX               0xDA
#define G_MOVEWORD          0xDB
#define G_MOVEMEM           0xDC
#define G_LOAD_UCODE        0xDD
#define G_DL                0xDE
#define G_ENDDL             0xDF
#define G_SPNOOP            0xE0
#define G_RDPHALF_1         0xE1
#define G_SETOTHERMODE_L    0xE2
#define G_SETOTHERMODE_H    0xE3
#define G_TEXRECT           0xE4
#define G_TEXRECTFLIP       0xE5
#define G_RDPLOADSYNC       0xE6
#define G_RDPPIPESYNC       0xE7
#define G_RDPTILESYNC       0xE8
#define G_RDPFULLSYNC       0xE9
#define G_SETKEYGB          0xEA
#define G_SETKEYR           0xEB
#define G_SETCONVERT        0xEC
#define G_SETSCISSOR        0xED
#define G_SETPRIMDEPTH      0xEE
#define G_RDPSETOTHERMODE   0xEF
#define G_LOADTLUT          0xF0
#define G_RDPHALF_2         0xF1
#define G_SETTILESIZE       0xF2
#define G_LOADBLOCK         0xF3
#define G_LOADTILE          0xF4
#define G_SETTILE           0xF5
#define G_FILLRECT          0xF6
#define G_SETFILLCOLOR      0xF7
#define G_SETFOGCOLOR       0xF8
#define G_SETBLENDCOLOR     0xF9
#define G_SETPRIMCOLOR      0xFA
#define G_SETENVCOLOR       0xFB
#define G_SETCOMBINE        0xFC
#define G_SETTIMG           0xFD
#define G_SETZIMG           0xFE
#define G_SETCIMG           0xFF
#define G_NOOP              0x00
#define G_VTX               0x01
#define G_MODIFYVTX         0x02
#define G_CULLDL            0x03
#define G_BRANCH_WZ         0x04
#define G_TRI1              0x05
#define G_TRI2              0x06
#define G_QUAD              0x07
#define G_TRISTRIP          0x08 /* = G_LINE3D was a no-op in F3DEX2, has been removed */
#define G_TRIFAN            0x09
#define G_LIGHTTORDP        0x0A
#define G_RELSEGMENT        0x0B

/* names differ between F3DEX2 and F3DZEX */
#define G_BRANCH_Z G_BRANCH_WZ
#define G_BRANCH_W G_BRANCH_WZ

/*
 * RSP command argument and misc defines
 */

/* Maximum number of transformed vertices kept in buffer in RSP DMEM */
#define G_MAX_VERTS 56

/* Maximum number of directional / point lights, not counting ambient */
#define G_MAX_LIGHTS 9

/* Maximum number of display list commands loaded at once into RSP DMEM */
#define G_INPUT_BUFFER_CMDS 21

/*
 * flags for G_SETGEOMETRYMODE
 *
 * Note that flat shading, i.e. not G_SHADING_SMOOTH, sets shade RGB for all
 * three verts to the value of the first vertex in the triangle. Shade alpha is
 * still separate for each vertex, which is desired behavior for fog but not for
 * any other F3DEX3 effects which use shade alpha.
 */
#define G_ZBUFFER               0x00000001
#define G_TEXTURE_ENABLE        0x00000000  /* actually 2, but controlled by SPTexture */
#define G_SHADE                 0x00000004
#define G_AMBOCCLUSION          0x00000040
#define G_ATTROFFSET_Z_ENABLE   0x00000080
#define G_ATTROFFSET_ST_ENABLE  0x00000100
#define G_CULL_NEITHER          0x00000000
#define G_CULL_FRONT            0x00000200
#define G_CULL_BACK             0x00000400
#define G_CULL_BOTH             0x00000600  /* useless but supported */
#define G_PACKED_NORMALS        0x00000800
#define G_LIGHTTOALPHA          0x00001000
#define G_LIGHTING_SPECULAR     0x00002000
#define G_FRESNEL_COLOR         0x00004000
#define G_FRESNEL_ALPHA         0x00008000
#define G_FOG                   0x00010000
#define G_LIGHTING              0x00020000
#define G_TEXTURE_GEN           0x00040000
#define G_TEXTURE_GEN_LINEAR    0x00080000
#define G_LOD                   0x00100000  /* Ignored by all F3DEX* variants */
#define G_SHADING_SMOOTH        0x00200000
#define G_LIGHTING_POSITIONAL   0x00400000  /* Ignored by F3DEX3, assumed always on */
#define G_CLIPPING              0x00800000  /* Ignored by all F3DEX* variants */

/* See SPDisplayList / SPBranchList */
#define G_DL_PUSH       0
#define G_DL_NOPUSH     1

/* See SPMatrix */
/**
 * @brief specifies whether the matrix operation will be performed on the projection or the model view matrix.
 * 
 */
#define G_MTX_MODELVIEW    0x00    /* matrix types */
/**
 * @brief @copybrief G_MTX_MODELVIEW
 * 
 */
#define G_MTX_PROJECTION   0x04
/**
 * @brief concatenates the matrix (m) with the top of the matrix stack.
 * 
 */
#define G_MTX_MUL          0x00    /* concat or load */
/**
 * @brief loads the matrix (m) onto the top of the matrix stack.
 * 
 */
#define G_MTX_LOAD         0x02
/**
 * @brief specifies do not push the matrix stack prior to matrix operations
 * 
 */
#define G_MTX_NOPUSH       0x00    /* push or not */
/**
 * @brief specifies push the matrix stack prior to matrix operations
 * 
 */
#define G_MTX_PUSH         0x01

/* See SPNormalsMode */
#define G_NORMALS_MODE_FAST      0x00
#define G_NORMALS_MODE_AUTO      0x01
#define G_NORMALS_MODE_MANUAL    0x02

/* See SPAlphaCompareCull */
#define G_ALPHA_COMPARE_CULL_DISABLE  0
#define G_ALPHA_COMPARE_CULL_BELOW    1
#define G_ALPHA_COMPARE_CULL_ABOVE   -1

/*
 * MOVEMEM indices
 * Each of these indexes an entry in a dmem table which points to an arbitrarily
 * sized block of dmem in which to store the result of a DMA.
 */
#define G_MV_TEMPMTX0  0  /* for internal use by G_MTX multiply mode */
#define G_MV_MMTX      2
#define G_MV_TEMPMTX1  4  /* for internal use by G_MTX multiply mode */
#define G_MV_VPMTX     6
#define G_MV_VIEWPORT  8
#define G_MV_LIGHT     10
/* G_MV_POINT is no longer supported because the internal vertex format is no
longer a multiple of 8 (DMA word). This was not used in any command anyway. */
/* G_MV_MATRIX is no longer supported because there is no MVP matrix in F3DEX3. */
#define G_MV_PMTX G_MV_VPMTX /* backwards compatibility */

/*
 * MOVEWORD indices
 * Each of these indexes an entry in a dmem table which points to a word in dmem
 * where an immediate word will be stored.
 */
#define G_MW_FX             0x00 /* replaces G_MW_MATRIX which is no longer supported */
#define G_MW_NUMLIGHT       0x02
/* nothing for 0x04; G_MW_CLIP is no longer supported */
#define G_MW_SEGMENT        0x06
#define G_MW_FOG            0x08
#define G_MW_LIGHTCOL       0x0A
/* G_MW_FORCEMTX is no longer supported because there is no MVP matrix in F3DEX3. */
/* G_MW_PERSPNORM is removed; perspective norm is now set via G_MW_FX. */

#define G_MW_HALFWORD_FLAG 0x8000 /* indicates store 2 bytes instead of 4 */

/*
 * These are offsets from the address in the dmem table
 */
#define G_MWO_NUMLIGHT           0x00
#define G_MWO_FOG                0x00

#define G_MWO_SEGMENT_0          0x00
#define G_MWO_SEGMENT_1          0x01
#define G_MWO_SEGMENT_2          0x02
#define G_MWO_SEGMENT_3          0x03
#define G_MWO_SEGMENT_4          0x04
#define G_MWO_SEGMENT_5          0x05
#define G_MWO_SEGMENT_6          0x06
#define G_MWO_SEGMENT_7          0x07
#define G_MWO_SEGMENT_8          0x08
#define G_MWO_SEGMENT_9          0x09
#define G_MWO_SEGMENT_A          0x0A
#define G_MWO_SEGMENT_B          0x0B
#define G_MWO_SEGMENT_C          0x0C
#define G_MWO_SEGMENT_D          0x0D
#define G_MWO_SEGMENT_E          0x0E
#define G_MWO_SEGMENT_F          0x0F

/* These are deprecated and no longer needed. */
#define G_MWO_aLIGHT_1           0x00
#define G_MWO_bLIGHT_1           0x04
#define G_MWO_aLIGHT_2           0x10
#define G_MWO_bLIGHT_2           0x14
#define G_MWO_aLIGHT_3           0x20
#define G_MWO_bLIGHT_3           0x24
#define G_MWO_aLIGHT_4           0x30
#define G_MWO_bLIGHT_4           0x34
#define G_MWO_aLIGHT_5           0x40
#define G_MWO_bLIGHT_5           0x44
#define G_MWO_aLIGHT_6           0x50
#define G_MWO_bLIGHT_6           0x54
#define G_MWO_aLIGHT_7           0x60
#define G_MWO_bLIGHT_7           0x64
#define G_MWO_aLIGHT_8           0x70
#define G_MWO_bLIGHT_8           0x74
#define G_MWO_aLIGHT_9           0x80
#define G_MWO_bLIGHT_9           0x84
#define G_MWO_aLIGHT_10          0x90
#define G_MWO_bLIGHT_10          0x94

/**
 * @brief changes the color of the vertex. The val parameter is interpreted as 4 bytes: red (high byte), green, blue, and alpha (low byte).
 * 
 */
#define G_MWO_POINT_RGBA         0x10
/**
 * @brief changes the S and T values (texture coordinates of the vertex). The high 16 bits of val specify the S coordinate, and the low 16 bits specify the T coordinate. Each coordinate is an S10.5 number.
 * 
 */
#define G_MWO_POINT_ST           0x14
/**
 * @brief change the screen coordinates of the vertex. The high 16 bits of val specify the X coordinate and the low 16 bits specify the Y coordinate. Both coordinates are S13.2 numbers with 0,0 being the upper-left of the screen, positive X going right, and positive Y going down.
 * 
 * @deprecated to use, won't work if the tri gets clipped.
 */
#define G_MWO_POINT_XYSCREEN     0x18
/**
 * @brief changes the screen Z coordinate of the vertex. The entire 32-bit val is taken as the new screen Z value. It is a 16.16 number in the range 0x00000000 to 0x03ff0000.
 * 
 * @deprecated to use, won't work if the tri gets clipped.
 */
#define G_MWO_POINT_ZSCREEN      0x1C

#define G_MWO_AO_AMBIENT         0x00
#define G_MWO_AO_DIRECTIONAL     0x02
#define G_MWO_AO_POINT           0x04
#define G_MWO_PERSPNORM          0x06
#define G_MWO_FRESNEL_SCALE      0x0C
#define G_MWO_FRESNEL_OFFSET     0x0E
#define G_MWO_ATTR_OFFSET_S      0x10
#define G_MWO_ATTR_OFFSET_T      0x12
#define G_MWO_ATTR_OFFSET_Z      0x14
#define G_MWO_ALPHA_COMPARE_CULL 0x16
#define G_MWO_NORMALS_MODE       0x18
#define G_MWO_LAST_MAT_DL_ADDR   0x1A

/*
 * RDP command argument defines
 */

/*
 * Coordinate shift values, number of bits of fraction
 */
#define G_TEXTURE_IMAGE_FRAC    2
#define G_TEXTURE_SCALE_FRAC    16
#define G_SCALE_FRAC            8
#define G_ROTATE_FRAC           16

/*
 * Maximum z-buffer value, used to initialize the z-buffer.
 * Note : this number is NOT the viewport z-scale constant.
 * See the comment next to G_MAXZ for more info.
 */
#define G_MAXFBZ    0x3FFF  /* 3b exp, 11b mantissa */

#define GPACK_RGBA5551(r, g, b, a) \
        ((((r) << 8) & 0xF800) |   \
         (((g) << 3) & 0x07C0) |   \
         (((b) >> 2) & 0x003E) |   \
          ((a) & 1))

#define GPACK_IA16(i, a)    (((i) << 8) | (a))

#define GPACK_ZDZ(z, dz)    (((z) << 2) | (dz))

/*
 * G_SETIMG fmt: set image formats
 */
#define G_IM_FMT_RGBA   0
#define G_IM_FMT_YUV    1
#define G_IM_FMT_CI     2
#define G_IM_FMT_IA     3
#define G_IM_FMT_I      4

/*
 * G_SETIMG siz: set image pixel size
 */
#define G_IM_SIZ_4b     0
#define G_IM_SIZ_8b     1
#define G_IM_SIZ_16b    2
#define G_IM_SIZ_32b    3
#define G_IM_SIZ_DD     5

#define G_IM_SIZ_4b_BYTES       0
#define G_IM_SIZ_4b_TILE_BYTES  G_IM_SIZ_4b_BYTES
#define G_IM_SIZ_4b_LINE_BYTES  G_IM_SIZ_4b_BYTES

#define G_IM_SIZ_8b_BYTES       1
#define G_IM_SIZ_8b_TILE_BYTES  G_IM_SIZ_8b_BYTES
#define G_IM_SIZ_8b_LINE_BYTES  G_IM_SIZ_8b_BYTES

#define G_IM_SIZ_16b_BYTES      2
#define G_IM_SIZ_16b_TILE_BYTES G_IM_SIZ_16b_BYTES
#define G_IM_SIZ_16b_LINE_BYTES G_IM_SIZ_16b_BYTES

#define G_IM_SIZ_32b_BYTES      4
#define G_IM_SIZ_32b_TILE_BYTES 2
#define G_IM_SIZ_32b_LINE_BYTES 2

#define G_IM_SIZ_4b_LOAD_BLOCK  G_IM_SIZ_16b
#define G_IM_SIZ_8b_LOAD_BLOCK  G_IM_SIZ_16b
#define G_IM_SIZ_16b_LOAD_BLOCK G_IM_SIZ_16b
#define G_IM_SIZ_32b_LOAD_BLOCK G_IM_SIZ_32b

#define G_IM_SIZ_4b_SHIFT  2
#define G_IM_SIZ_8b_SHIFT  1
#define G_IM_SIZ_16b_SHIFT 0
#define G_IM_SIZ_32b_SHIFT 0

#define G_IM_SIZ_4b_INCR  3
#define G_IM_SIZ_8b_INCR  1
#define G_IM_SIZ_16b_INCR 0
#define G_IM_SIZ_32b_INCR 0

/*
 * G_SETCOMBINE: color combine modes
 */
/* Color combiner constants: */
#define G_CCMUX_COMBINED        0
#define G_CCMUX_TEXEL0          1
#define G_CCMUX_TEXEL1          2
#define G_CCMUX_PRIMITIVE       3
#define G_CCMUX_SHADE           4
#define G_CCMUX_ENVIRONMENT     5
#define G_CCMUX_CENTER          6
#define G_CCMUX_SCALE           6
#define G_CCMUX_COMBINED_ALPHA  7
#define G_CCMUX_TEXEL0_ALPHA    8
#define G_CCMUX_TEXEL1_ALPHA    9
#define G_CCMUX_PRIMITIVE_ALPHA 10
#define G_CCMUX_SHADE_ALPHA     11
#define G_CCMUX_ENV_ALPHA       12
#define G_CCMUX_LOD_FRACTION    13
#define G_CCMUX_PRIM_LOD_FRAC   14
#define G_CCMUX_NOISE           7
#define G_CCMUX_K4              7
#define G_CCMUX_K5              15
#define G_CCMUX_1               6
#define G_CCMUX_0               31

/* Alpha combiner constants: */
#define G_ACMUX_COMBINED        0
#define G_ACMUX_TEXEL0          1
#define G_ACMUX_TEXEL1          2
#define G_ACMUX_PRIMITIVE       3
#define G_ACMUX_SHADE           4
#define G_ACMUX_ENVIRONMENT     5
#define G_ACMUX_LOD_FRACTION    0
#define G_ACMUX_PRIM_LOD_FRAC   6
#define G_ACMUX_1               6
#define G_ACMUX_0               7

/* typical CC cycle 1 modes */

/* typical CC cycle 1 modes */
#define	G_CC_PRIMITIVE              0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE
#define	G_CC_SHADE                  0, 0, 0, SHADE, 0, 0, 0, SHADE

#define	G_CC_MODULATEI              TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE
#define	G_CC_MODULATEIDECALA        TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0
#define	G_CC_MODULATEIFADE          TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT

#define	G_CC_MODULATERGB            G_CC_MODULATEI
#define	G_CC_MODULATERGBDECALA      G_CC_MODULATEIDECALA
#define	G_CC_MODULATERGBFADE        G_CC_MODULATEIFADE

#define	G_CC_MODULATEIA             TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0
#define	G_CC_MODULATEIFADEA         TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0

#define	G_CC_MODULATEFADE           TEXEL0, 0, SHADE, 0, ENVIRONMENT, 0, TEXEL0, 0

#define	G_CC_MODULATERGBA           G_CC_MODULATEIA
#define	G_CC_MODULATERGBFADEA       G_CC_MODULATEIFADEA

#define	G_CC_MODULATEI_PRIM         TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE
#define	G_CC_MODULATEIA_PRIM        TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0
#define	G_CC_MODULATEIDECALA_PRIM   TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0

#define	G_CC_MODULATERGB_PRIM       G_CC_MODULATEI_PRIM
#define	G_CC_MODULATERGBA_PRIM      G_CC_MODULATEIA_PRIM
#define	G_CC_MODULATERGBDECALA_PRIM G_CC_MODULATEIDECALA_PRIM

#define	G_CC_FADE                   SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0
#define	G_CC_FADEA                  TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0

#define	G_CC_DECALRGB               0, 0, 0, TEXEL0, 0, 0, 0, SHADE
#define	G_CC_DECALRGBA              0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0
#define	G_CC_DECALFADE              0, 0, 0, TEXEL0, 0, 0, 0, ENVIRONMENT

#define	G_CC_DECALFADEA             0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0

#define	G_CC_BLENDI                 ENVIRONMENT, SHADE, TEXEL0, SHADE, 0, 0, 0, SHADE
#define	G_CC_BLENDIA                ENVIRONMENT, SHADE, TEXEL0, SHADE, TEXEL0, 0, SHADE, 0
#define	G_CC_BLENDIDECALA           ENVIRONMENT, SHADE, TEXEL0, SHADE, 0, 0, 0, TEXEL0

#define	G_CC_BLENDRGBA              TEXEL0, SHADE, TEXEL0_ALPHA, SHADE, 0, 0, 0, SHADE
#define	G_CC_BLENDRGBDECALA         TEXEL0, SHADE, TEXEL0_ALPHA, SHADE, 0, 0, 0, TEXEL0
#define	G_CC_BLENDRGBFADEA          TEXEL0, SHADE, TEXEL0_ALPHA, SHADE, 0, 0, 0, ENVIRONMENT

#define G_CC_ADDRGB                 TEXEL0, 0, TEXEL0, SHADE, 0, 0, 0, SHADE
#define G_CC_ADDRGBDECALA           TEXEL0, 0, TEXEL0, SHADE, 0, 0, 0, TEXEL0
#define G_CC_ADDRGBFADE             TEXEL0, 0, TEXEL0, SHADE, 0, 0, 0, ENVIRONMENT

#define G_CC_REFLECTRGB             ENVIRONMENT, 0, TEXEL0, SHADE, 0, 0, 0, SHADE
#define G_CC_REFLECTRGBDECALA       ENVIRONMENT, 0, TEXEL0, SHADE, 0, 0, 0, TEXEL0

#define G_CC_HILITERGB              PRIMITIVE, SHADE, TEXEL0, SHADE, 0, 0, 0, SHADE
#define G_CC_HILITERGBA             PRIMITIVE, SHADE, TEXEL0, SHADE, PRIMITIVE, SHADE, TEXEL0, SHADE
#define G_CC_HILITERGBDECALA        PRIMITIVE, SHADE, TEXEL0, SHADE, 0, 0, 0, TEXEL0

#define G_CC_SHADEDECALA            0, 0, 0, SHADE, 0, 0, 0, TEXEL0
#define G_CC_SHADEFADEA             0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT

#define	G_CC_BLENDPE                PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, SHADE, 0
#define	G_CC_BLENDPEDECALA          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0

/* oddball modes */
#define	_G_CC_BLENDPE               ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, SHADE, 0
#define	_G_CC_BLENDPEDECALA         ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, 0, 0, 0, TEXEL0
#define	_G_CC_TWOCOLORTEX           PRIMITIVE, SHADE, TEXEL0, SHADE, 0, 0, 0, SHADE
/* used for 1-cycle sparse mip-maps, primitive color has color of lowest LOD */
#define	_G_CC_SPARSEST              PRIMITIVE, TEXEL0, LOD_FRACTION, TEXEL0, PRIMITIVE, TEXEL0, LOD_FRACTION, TEXEL0
#define G_CC_TEMPLERP               TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0

/* typical CC cycle 1 modes, usually followed by other cycle 2 modes */
#define	G_CC_TRILERP                TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0
#define	G_CC_INTERFERENCE           TEXEL0, 0, TEXEL1, 0, TEXEL0, 0, TEXEL1, 0

/*
 *  One-cycle color convert operation
 */
#define	G_CC_1CYUV2RGB              TEXEL0, K4, K5, TEXEL0, 0, 0, 0, SHADE

/*
 *  NOTE: YUV2RGB expects TF step1 color conversion to occur in 2nd clock.
 * Therefore, CC looks for step1 results in TEXEL1
 */
#define	G_CC_YUV2RGB                TEXEL1, K4, K5, TEXEL1, 0, 0, 0, 0

/* typical CC cycle 2 modes */
#define	G_CC_PASS2                  0, 0, 0, COMBINED, 0, 0, 0, COMBINED
#define	G_CC_MODULATEI2             COMBINED, 0, SHADE, 0, 0, 0, 0, SHADE
#define	G_CC_MODULATEIA2            COMBINED, 0, SHADE, 0, COMBINED, 0, SHADE, 0
#define	G_CC_MODULATERGB2           G_CC_MODULATEI2
#define	G_CC_MODULATERGBA2          G_CC_MODULATEIA2
#define	G_CC_MODULATEI_PRIM2        COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE
#define	G_CC_MODULATEIA_PRIM2       COMBINED, 0, PRIMITIVE, 0, COMBINED, 0, PRIMITIVE, 0
#define	G_CC_MODULATERGB_PRIM2      G_CC_MODULATEI_PRIM2
#define	G_CC_MODULATERGBA_PRIM2     G_CC_MODULATEIA_PRIM2
#define	G_CC_DECALRGB2              0, 0, 0, COMBINED, 0, 0, 0, SHADE
/*
 * ?
#define	G_CC_DECALRGBA2		        COMBINED, SHADE, COMBINED_ALPHA, SHADE, 0, 0, 0, SHADE
*/
#define	G_CC_BLENDI2                ENVIRONMENT, SHADE, COMBINED, SHADE, 0, 0, 0, SHADE
#define	G_CC_BLENDIA2               ENVIRONMENT, SHADE, COMBINED, SHADE, COMBINED, 0, SHADE, 0
#define	G_CC_CHROMA_KEY2            TEXEL0, CENTER, SCALE, 0, 0, 0, 0, 0
#define G_CC_HILITERGB2             ENVIRONMENT, COMBINED, TEXEL0, COMBINED, 0, 0, 0, SHADE
#define G_CC_HILITERGBA2            ENVIRONMENT, COMBINED, TEXEL0, COMBINED, ENVIRONMENT, COMBINED, TEXEL0, COMBINED
#define G_CC_HILITERGBDECALA2       ENVIRONMENT, COMBINED, TEXEL0, COMBINED, 0, 0, 0, TEXEL0
#define G_CC_HILITERGBPASSA2        ENVIRONMENT, COMBINED, TEXEL0, COMBINED, 0, 0, 0, COMBINED


/*
 *  One-cycle color convert operation
 */
#define G_CC_1CYUV2RGB              TEXEL0, K4, K5, TEXEL0, 0, 0, 0, SHADE

/*
 *  NOTE: YUV2RGB expects TF step1 color conversion to occur in 2nd clock.
 * Therefore, CC looks for step1 results in TEXEL1
 */
#define G_CC_YUV2RGB                TEXEL1, K4, K5, TEXEL1, 0, 0, 0, 0

/* typical CC cycle 2 modes */
#define G_CC_PASS2                  0, 0, 0, COMBINED, 0, 0, 0, COMBINED
#define G_CC_MODULATEI2             COMBINED, 0, SHADE, 0, 0, 0, 0, SHADE
#define G_CC_MODULATEIA2            COMBINED, 0, SHADE, 0, COMBINED, 0, SHADE, 0
#define G_CC_MODULATERGB2           G_CC_MODULATEI2
#define G_CC_MODULATERGBA2          G_CC_MODULATEIA2
#define G_CC_MODULATEI_PRIM2        COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE
#define G_CC_MODULATEIA_PRIM2       COMBINED, 0, PRIMITIVE, 0, COMBINED, 0, PRIMITIVE, 0
#define G_CC_MODULATERGB_PRIM2      G_CC_MODULATEI_PRIM2
#define G_CC_MODULATERGBA_PRIM2     G_CC_MODULATEIA_PRIM2
#define G_CC_DECALRGB2              0, 0, 0, COMBINED, 0, 0, 0, SHADE
/*
 * ?
#define G_CC_DECALRGBA2             COMBINED, SHADE, COMBINED_ALPHA, SHADE, 0, 0, 0, SHADE
*/
#define G_CC_BLENDI2                ENVIRONMENT, SHADE, COMBINED, SHADE, 0, 0, 0, SHADE
#define G_CC_BLENDIA2               ENVIRONMENT, SHADE, COMBINED, SHADE, COMBINED, 0, SHADE, 0
#define G_CC_CHROMA_KEY2            TEXEL0, CENTER, SCALE, 0, 0, 0, 0, 0
#define G_CC_HILITERGB2             ENVIRONMENT, COMBINED, TEXEL0, COMBINED, 0, 0, 0, SHADE
#define G_CC_HILITERGBA2            ENVIRONMENT, COMBINED, TEXEL0, COMBINED, ENVIRONMENT, COMBINED, TEXEL0, COMBINED
#define G_CC_HILITERGBDECALA2       ENVIRONMENT, COMBINED, TEXEL0, COMBINED, 0, 0, 0, TEXEL0
#define G_CC_HILITERGBPASSA2        ENVIRONMENT, COMBINED, TEXEL0, COMBINED, 0, 0, 0, COMBINED

/*
 * G_SETOTHERMODE_L sft: shift count
 */
#define G_MDSFT_ALPHACOMPARE    0
#define G_MDSFT_ZSRCSEL         2
#define G_MDSFT_RENDERMODE      3
#define G_MDSFT_BLENDER         16

/*
 * G_SETOTHERMODE_H sft: shift count
 */
#define G_MDSFT_ALPHADITHER     4
#define G_MDSFT_RGBDITHER       6
#define G_MDSFT_COMBKEY         8
#define G_MDSFT_TEXTCONV        9
#define G_MDSFT_TEXTFILT        12
#define G_MDSFT_TEXTLUT         14
#define G_MDSFT_TEXTLOD         16
#define G_MDSFT_TEXTDETAIL      17
#define G_MDSFT_TEXTPERSP       19
#define G_MDSFT_CYCLETYPE       20
#define G_MDSFT_COLORDITHER     22  /* Needed for OoT ucode_disas even though HW 1.0 only */
#define G_MDSFT_PIPELINE        23

/* G_SETOTHERMODE_H gPipelineMode */
#define G_PM_1PRIMITIVE     (1 << G_MDSFT_PIPELINE)
#define G_PM_NPRIMITIVE     (0 << G_MDSFT_PIPELINE)

/* G_SETOTHERMODE_H gSetCycleType */
#define G_CYC_1CYCLE        (0 << G_MDSFT_CYCLETYPE)
#define G_CYC_2CYCLE        (1 << G_MDSFT_CYCLETYPE)
#define G_CYC_COPY          (2 << G_MDSFT_CYCLETYPE)
#define G_CYC_FILL          (3 << G_MDSFT_CYCLETYPE)

/* G_SETOTHERMODE_H gSetTexturePersp */
#define G_TP_NONE           (0 << G_MDSFT_TEXTPERSP)
#define G_TP_PERSP          (1 << G_MDSFT_TEXTPERSP)

/* G_SETOTHERMODE_H gSetTextureDetail */
#define G_TD_CLAMP          (0 << G_MDSFT_TEXTDETAIL)
#define G_TD_SHARPEN        (1 << G_MDSFT_TEXTDETAIL)
#define G_TD_DETAIL         (2 << G_MDSFT_TEXTDETAIL)

/* G_SETOTHERMODE_H gSetTextureLOD */
#define G_TL_TILE           (0 << G_MDSFT_TEXTLOD)
#define G_TL_LOD            (1 << G_MDSFT_TEXTLOD)

/* G_SETOTHERMODE_H gSetTextureLUT */
#define G_TT_NONE           (0 << G_MDSFT_TEXTLUT)
#define G_TT_RGBA16         (2 << G_MDSFT_TEXTLUT)
#define G_TT_IA16           (3 << G_MDSFT_TEXTLUT)

/* G_SETOTHERMODE_H gSetTextureFilter */
#define G_TF_POINT          (0 << G_MDSFT_TEXTFILT)
#define G_TF_AVERAGE        (3 << G_MDSFT_TEXTFILT)
#define G_TF_BILERP         (2 << G_MDSFT_TEXTFILT)

/* G_SETOTHERMODE_H gSetTextureConvert */
#define G_TC_CONV           (0 << G_MDSFT_TEXTCONV)
#define G_TC_FILTCONV       (5 << G_MDSFT_TEXTCONV)
#define G_TC_FILT           (6 << G_MDSFT_TEXTCONV)

/* G_SETOTHERMODE_H gSetCombineKey */
#define G_CK_NONE           (0 << G_MDSFT_COMBKEY)
#define G_CK_KEY            (1 << G_MDSFT_COMBKEY)

/* G_SETOTHERMODE_H gSetColorDither */
#define G_CD_MAGICSQ        (0 << G_MDSFT_RGBDITHER)
#define G_CD_BAYER          (1 << G_MDSFT_RGBDITHER)
#define G_CD_NOISE          (2 << G_MDSFT_RGBDITHER)
#define G_CD_DISABLE        (3 << G_MDSFT_RGBDITHER)

/* G_SETOTHERMODE_H gSetAlphaDither */
#define G_AD_PATTERN        (0 << G_MDSFT_ALPHADITHER)
#define G_AD_NOTPATTERN     (1 << G_MDSFT_ALPHADITHER)
#define G_AD_NOISE          (2 << G_MDSFT_ALPHADITHER)
#define G_AD_DISABLE        (3 << G_MDSFT_ALPHADITHER)

/* G_SETOTHERMODE_L gSetAlphaCompare */
#define G_AC_NONE           (0 << G_MDSFT_ALPHACOMPARE)
#define G_AC_THRESHOLD      (1 << G_MDSFT_ALPHACOMPARE)
#define G_AC_DITHER         (3 << G_MDSFT_ALPHACOMPARE)

/* G_SETOTHERMODE_L gSetDepthSource */
#define G_ZS_PIXEL          (0 << G_MDSFT_ZSRCSEL)
#define G_ZS_PRIM           (1 << G_MDSFT_ZSRCSEL)

/* G_SETOTHERMODE_L gSetRenderMode */
#define AA_EN           0x0008
#define Z_CMP           0x0010
#define Z_UPD           0x0020
#define IM_RD           0x0040
#define CLR_ON_CVG      0x0080
#define CVG_DST_CLAMP   0x0000
#define CVG_DST_WRAP    0x0100
#define CVG_DST_FULL    0x0200
#define CVG_DST_SAVE    0x0300
#define ZMODE_OPA       0x0000
#define ZMODE_INTER     0x0400
#define ZMODE_XLU       0x0800
#define ZMODE_DEC       0x0C00
#define CVG_X_ALPHA     0x1000
#define ALPHA_CVG_SEL   0x2000
#define FORCE_BL        0x4000
#define TEX_EDGE        0x0000  /* used to be 0x8000 */

#define G_BL_CLR_IN     0
#define G_BL_CLR_MEM    1
#define G_BL_CLR_BL     2
#define G_BL_CLR_FOG    3
#define G_BL_1MA        0
#define G_BL_A_MEM      1
#define G_BL_A_IN       0
#define G_BL_A_FOG      1
#define G_BL_A_SHADE    2
#define G_BL_1          2
#define G_BL_0          3

#define GBL_c1(m1a, m1b, m2a, m2b)  \
    (m1a) << 30 | (m1b) << 26 | (m2a) << 22 | (m2b) << 18
#define GBL_c2(m1a, m1b, m2a, m2b)  \
    (m1a) << 28 | (m1b) << 24 | (m2a) << 20 | (m2b) << 16

#define RM_AA_ZB_OPA_SURF(clk)                                  \
    AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |             \
    ZMODE_OPA | ALPHA_CVG_SEL |                                 \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_RA_ZB_OPA_SURF(clk)                                  \
    AA_EN | Z_CMP | Z_UPD | CVG_DST_CLAMP |                     \
    ZMODE_OPA | ALPHA_CVG_SEL |                                 \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_AA_ZB_XLU_SURF(clk)                                  \
    AA_EN | Z_CMP | IM_RD | CVG_DST_WRAP | CLR_ON_CVG |         \
    FORCE_BL | ZMODE_XLU |                                      \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_AA_ZB_OPA_DECAL(clk)                                 \
    AA_EN | Z_CMP | IM_RD | CVG_DST_WRAP | ALPHA_CVG_SEL |      \
    ZMODE_DEC |                                                 \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_RA_ZB_OPA_DECAL(clk)                                 \
    AA_EN | Z_CMP | CVG_DST_WRAP | ALPHA_CVG_SEL |              \
    ZMODE_DEC |                                                 \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_AA_ZB_XLU_DECAL(clk)                                 \
    AA_EN | Z_CMP | IM_RD | CVG_DST_WRAP | CLR_ON_CVG |         \
    FORCE_BL | ZMODE_DEC |                                      \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_AA_ZB_OPA_INTER(clk)                                 \
    AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |             \
    ALPHA_CVG_SEL | ZMODE_INTER |                               \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_RA_ZB_OPA_INTER(clk)                                 \
    AA_EN | Z_CMP | Z_UPD | CVG_DST_CLAMP |                     \
    ALPHA_CVG_SEL | ZMODE_INTER |                               \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_AA_ZB_XLU_INTER(clk)                                 \
    AA_EN | Z_CMP | IM_RD | CVG_DST_WRAP | CLR_ON_CVG |         \
    FORCE_BL | ZMODE_INTER |                                    \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_AA_ZB_XLU_LINE(clk)                                  \
    AA_EN | Z_CMP | IM_RD | CVG_DST_CLAMP | CVG_X_ALPHA |       \
    ALPHA_CVG_SEL | FORCE_BL | ZMODE_XLU |                      \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_AA_ZB_DEC_LINE(clk)                                  \
    AA_EN | Z_CMP | IM_RD | CVG_DST_SAVE | CVG_X_ALPHA |        \
    ALPHA_CVG_SEL | FORCE_BL | ZMODE_DEC |                      \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_AA_ZB_TEX_EDGE(clk)                                  \
    AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |             \
    CVG_X_ALPHA | ALPHA_CVG_SEL | ZMODE_OPA | TEX_EDGE |        \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_AA_ZB_TEX_INTER(clk)                                 \
    AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |             \
    CVG_X_ALPHA | ALPHA_CVG_SEL | ZMODE_INTER | TEX_EDGE |      \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_AA_ZB_SUB_SURF(clk)                                  \
    AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_FULL |              \
    ZMODE_OPA | ALPHA_CVG_SEL |                                 \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_AA_ZB_PCL_SURF(clk)                                  \
    AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |             \
    ZMODE_OPA | G_AC_DITHER |                                   \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_AA_ZB_OPA_TERR(clk)                                  \
    AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |             \
    ZMODE_OPA | ALPHA_CVG_SEL |                                 \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_AA_ZB_TEX_TERR(clk)                                  \
    AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |             \
    CVG_X_ALPHA | ALPHA_CVG_SEL | ZMODE_OPA | TEX_EDGE |        \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_AA_ZB_SUB_TERR(clk)                                  \
    AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_FULL |              \
    ZMODE_OPA | ALPHA_CVG_SEL |                                 \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


#define RM_AA_OPA_SURF(clk)                                     \
    AA_EN | IM_RD | CVG_DST_CLAMP |                             \
    ZMODE_OPA | ALPHA_CVG_SEL |                                 \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_RA_OPA_SURF(clk)                                     \
    AA_EN | CVG_DST_CLAMP |                                     \
    ZMODE_OPA | ALPHA_CVG_SEL |                                 \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_AA_XLU_SURF(clk)                                     \
    AA_EN | IM_RD | CVG_DST_WRAP | CLR_ON_CVG | FORCE_BL |      \
    ZMODE_OPA |                                                 \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_AA_XLU_LINE(clk)                                     \
    AA_EN | IM_RD | CVG_DST_CLAMP | CVG_X_ALPHA |               \
    ALPHA_CVG_SEL | FORCE_BL | ZMODE_OPA |                      \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_AA_DEC_LINE(clk)                                     \
    AA_EN | IM_RD | CVG_DST_FULL | CVG_X_ALPHA |                \
    ALPHA_CVG_SEL | FORCE_BL | ZMODE_OPA |                      \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_AA_TEX_EDGE(clk)                                     \
    AA_EN | IM_RD | CVG_DST_CLAMP |                             \
    CVG_X_ALPHA | ALPHA_CVG_SEL | ZMODE_OPA | TEX_EDGE |        \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_AA_SUB_SURF(clk)                                     \
    AA_EN | IM_RD | CVG_DST_FULL |                              \
    ZMODE_OPA | ALPHA_CVG_SEL |                                 \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_AA_PCL_SURF(clk)                                     \
    AA_EN | IM_RD | CVG_DST_CLAMP |                             \
    ZMODE_OPA | G_AC_DITHER |                                   \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_AA_OPA_TERR(clk)                                     \
    AA_EN | IM_RD | CVG_DST_CLAMP |                             \
    ZMODE_OPA | ALPHA_CVG_SEL |                                 \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_AA_TEX_TERR(clk)                                     \
    AA_EN | IM_RD | CVG_DST_CLAMP |                             \
    CVG_X_ALPHA | ALPHA_CVG_SEL | ZMODE_OPA | TEX_EDGE |        \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_AA_SUB_TERR(clk)                                     \
    AA_EN | IM_RD | CVG_DST_FULL |                              \
    ZMODE_OPA | ALPHA_CVG_SEL |                                 \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


#define RM_ZB_OPA_SURF(clk)                                     \
    Z_CMP | Z_UPD | CVG_DST_FULL | ALPHA_CVG_SEL |              \
    ZMODE_OPA |                                                 \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_ZB_XLU_SURF(clk)                                     \
    Z_CMP | IM_RD | CVG_DST_FULL | FORCE_BL | ZMODE_XLU |       \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_ZB_OPA_DECAL(clk)                                    \
    Z_CMP | CVG_DST_FULL | ALPHA_CVG_SEL | ZMODE_DEC |          \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_ZB_XLU_DECAL(clk)                                    \
    Z_CMP | IM_RD | CVG_DST_FULL | FORCE_BL | ZMODE_DEC |       \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_ZB_CLD_SURF(clk)                                     \
    Z_CMP | IM_RD | CVG_DST_SAVE | FORCE_BL | ZMODE_XLU |       \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_ZB_OVL_SURF(clk)                                     \
    Z_CMP | IM_RD | CVG_DST_SAVE | FORCE_BL | ZMODE_DEC |       \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_ZB_PCL_SURF(clk)                                     \
    Z_CMP | Z_UPD | CVG_DST_FULL | ZMODE_OPA |                  \
    G_AC_DITHER |                                               \
    GBL_c##clk(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)


#define RM_OPA_SURF(clk)                                        \
    CVG_DST_CLAMP | FORCE_BL | ZMODE_OPA |                      \
    GBL_c##clk(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)

#define RM_XLU_SURF(clk)                                        \
    IM_RD | CVG_DST_FULL | FORCE_BL | ZMODE_OPA |               \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_TEX_EDGE(clk)                                        \
    CVG_DST_CLAMP | CVG_X_ALPHA | ALPHA_CVG_SEL | FORCE_BL |    \
    ZMODE_OPA | TEX_EDGE | AA_EN |                              \
    GBL_c##clk(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)

#define RM_CLD_SURF(clk)                                        \
    IM_RD | CVG_DST_SAVE | FORCE_BL | ZMODE_OPA |               \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define RM_PCL_SURF(clk)                                        \
    CVG_DST_FULL | FORCE_BL | ZMODE_OPA |                       \
    G_AC_DITHER |                                               \
    GBL_c##clk(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)

#define RM_ADD(clk)                                             \
    IM_RD | CVG_DST_SAVE | FORCE_BL | ZMODE_OPA |               \
    GBL_c##clk(G_BL_CLR_IN, G_BL_A_FOG, G_BL_CLR_MEM, G_BL_1)

#define RM_NOOP(clk)    \
    GBL_c##clk(0, 0, 0, 0)

#define RM_VISCVG(clk)                                          \
    IM_RD | FORCE_BL |                                          \
    GBL_c##clk(G_BL_CLR_IN, G_BL_0, G_BL_CLR_BL, G_BL_A_MEM)

/* for rendering to an 8-bit framebuffer */
#define RM_OPA_CI(clk)                                          \
    CVG_DST_CLAMP | ZMODE_OPA |                                 \
    GBL_c##clk(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)

/* Custom version of RM_AA_ZB_XLU_SURF with Z_UPD */
#define RM_CUSTOM_AA_ZB_XLU_SURF(clk)				\
	RM_AA_ZB_XLU_SURF(clk) | Z_UPD

#define G_RM_CUSTOM_AA_ZB_XLU_SURF	RM_CUSTOM_AA_ZB_XLU_SURF(1)
#define G_RM_CUSTOM_AA_ZB_XLU_SURF2	RM_CUSTOM_AA_ZB_XLU_SURF(2)

#define G_RM_AA_ZB_OPA_SURF     RM_AA_ZB_OPA_SURF(1)
#define G_RM_AA_ZB_OPA_SURF2    RM_AA_ZB_OPA_SURF(2)
#define G_RM_AA_ZB_XLU_SURF     RM_AA_ZB_XLU_SURF(1)
#define G_RM_AA_ZB_XLU_SURF2    RM_AA_ZB_XLU_SURF(2)
#define G_RM_AA_ZB_OPA_DECAL    RM_AA_ZB_OPA_DECAL(1)
#define G_RM_AA_ZB_OPA_DECAL2   RM_AA_ZB_OPA_DECAL(2)
#define G_RM_AA_ZB_XLU_DECAL    RM_AA_ZB_XLU_DECAL(1)
#define G_RM_AA_ZB_XLU_DECAL2   RM_AA_ZB_XLU_DECAL(2)
#define G_RM_AA_ZB_OPA_INTER    RM_AA_ZB_OPA_INTER(1)
#define G_RM_AA_ZB_OPA_INTER2   RM_AA_ZB_OPA_INTER(2)
#define G_RM_AA_ZB_XLU_INTER    RM_AA_ZB_XLU_INTER(1)
#define G_RM_AA_ZB_XLU_INTER2   RM_AA_ZB_XLU_INTER(2)
#define G_RM_AA_ZB_XLU_LINE     RM_AA_ZB_XLU_LINE(1)
#define G_RM_AA_ZB_XLU_LINE2    RM_AA_ZB_XLU_LINE(2)
#define G_RM_AA_ZB_DEC_LINE     RM_AA_ZB_DEC_LINE(1)
#define G_RM_AA_ZB_DEC_LINE2    RM_AA_ZB_DEC_LINE(2)
#define G_RM_AA_ZB_TEX_EDGE     RM_AA_ZB_TEX_EDGE(1)
#define G_RM_AA_ZB_TEX_EDGE2    RM_AA_ZB_TEX_EDGE(2)
#define G_RM_AA_ZB_TEX_INTER    RM_AA_ZB_TEX_INTER(1)
#define G_RM_AA_ZB_TEX_INTER2   RM_AA_ZB_TEX_INTER(2)
#define G_RM_AA_ZB_SUB_SURF     RM_AA_ZB_SUB_SURF(1)
#define G_RM_AA_ZB_SUB_SURF2    RM_AA_ZB_SUB_SURF(2)
#define G_RM_AA_ZB_PCL_SURF     RM_AA_ZB_PCL_SURF(1)
#define G_RM_AA_ZB_PCL_SURF2    RM_AA_ZB_PCL_SURF(2)
#define G_RM_AA_ZB_OPA_TERR     RM_AA_ZB_OPA_TERR(1)
#define G_RM_AA_ZB_OPA_TERR2    RM_AA_ZB_OPA_TERR(2)
#define G_RM_AA_ZB_TEX_TERR     RM_AA_ZB_TEX_TERR(1)
#define G_RM_AA_ZB_TEX_TERR2    RM_AA_ZB_TEX_TERR(2)
#define G_RM_AA_ZB_SUB_TERR     RM_AA_ZB_SUB_TERR(1)
#define G_RM_AA_ZB_SUB_TERR2    RM_AA_ZB_SUB_TERR(2)

#define G_RM_RA_ZB_OPA_SURF     RM_RA_ZB_OPA_SURF(1)
#define G_RM_RA_ZB_OPA_SURF2    RM_RA_ZB_OPA_SURF(2)
#define G_RM_RA_ZB_OPA_DECAL    RM_RA_ZB_OPA_DECAL(1)
#define G_RM_RA_ZB_OPA_DECAL2   RM_RA_ZB_OPA_DECAL(2)
#define G_RM_RA_ZB_OPA_INTER    RM_RA_ZB_OPA_INTER(1)
#define G_RM_RA_ZB_OPA_INTER2   RM_RA_ZB_OPA_INTER(2)

#define G_RM_AA_OPA_SURF    RM_AA_OPA_SURF(1)
#define G_RM_AA_OPA_SURF2   RM_AA_OPA_SURF(2)
#define G_RM_AA_XLU_SURF    RM_AA_XLU_SURF(1)
#define G_RM_AA_XLU_SURF2   RM_AA_XLU_SURF(2)
#define G_RM_AA_XLU_LINE    RM_AA_XLU_LINE(1)
#define G_RM_AA_XLU_LINE2   RM_AA_XLU_LINE(2)
#define G_RM_AA_DEC_LINE    RM_AA_DEC_LINE(1)
#define G_RM_AA_DEC_LINE2   RM_AA_DEC_LINE(2)
#define G_RM_AA_TEX_EDGE    RM_AA_TEX_EDGE(1)
#define G_RM_AA_TEX_EDGE2   RM_AA_TEX_EDGE(2)
#define G_RM_AA_SUB_SURF    RM_AA_SUB_SURF(1)
#define G_RM_AA_SUB_SURF2   RM_AA_SUB_SURF(2)
#define G_RM_AA_PCL_SURF    RM_AA_PCL_SURF(1)
#define G_RM_AA_PCL_SURF2   RM_AA_PCL_SURF(2)
#define G_RM_AA_OPA_TERR    RM_AA_OPA_TERR(1)
#define G_RM_AA_OPA_TERR2   RM_AA_OPA_TERR(2)
#define G_RM_AA_TEX_TERR    RM_AA_TEX_TERR(1)
#define G_RM_AA_TEX_TERR2   RM_AA_TEX_TERR(2)
#define G_RM_AA_SUB_TERR    RM_AA_SUB_TERR(1)
#define G_RM_AA_SUB_TERR2   RM_AA_SUB_TERR(2)

#define G_RM_RA_OPA_SURF    RM_RA_OPA_SURF(1)
#define G_RM_RA_OPA_SURF2   RM_RA_OPA_SURF(2)

#define G_RM_ZB_OPA_SURF    RM_ZB_OPA_SURF(1)
#define G_RM_ZB_OPA_SURF2   RM_ZB_OPA_SURF(2)
#define G_RM_ZB_XLU_SURF    RM_ZB_XLU_SURF(1)
#define G_RM_ZB_XLU_SURF2   RM_ZB_XLU_SURF(2)
#define G_RM_ZB_OPA_DECAL   RM_ZB_OPA_DECAL(1)
#define G_RM_ZB_OPA_DECAL2  RM_ZB_OPA_DECAL(2)
#define G_RM_ZB_XLU_DECAL   RM_ZB_XLU_DECAL(1)
#define G_RM_ZB_XLU_DECAL2  RM_ZB_XLU_DECAL(2)
#define G_RM_ZB_CLD_SURF    RM_ZB_CLD_SURF(1)
#define G_RM_ZB_CLD_SURF2   RM_ZB_CLD_SURF(2)
#define G_RM_ZB_OVL_SURF    RM_ZB_OVL_SURF(1)
#define G_RM_ZB_OVL_SURF2   RM_ZB_OVL_SURF(2)
#define G_RM_ZB_PCL_SURF    RM_ZB_PCL_SURF(1)
#define G_RM_ZB_PCL_SURF2   RM_ZB_PCL_SURF(2)

#define G_RM_OPA_SURF       RM_OPA_SURF(1)
#define G_RM_OPA_SURF2      RM_OPA_SURF(2)
#define G_RM_XLU_SURF       RM_XLU_SURF(1)
#define G_RM_XLU_SURF2      RM_XLU_SURF(2)
#define G_RM_CLD_SURF       RM_CLD_SURF(1)
#define G_RM_CLD_SURF2      RM_CLD_SURF(2)
#define G_RM_TEX_EDGE       RM_TEX_EDGE(1)
#define G_RM_TEX_EDGE2      RM_TEX_EDGE(2)
#define G_RM_PCL_SURF       RM_PCL_SURF(1)
#define G_RM_PCL_SURF2      RM_PCL_SURF(2)
#define G_RM_ADD            RM_ADD(1)
#define G_RM_ADD2           RM_ADD(2)
#define G_RM_NOOP           RM_NOOP(1)
#define G_RM_NOOP2          RM_NOOP(2)
#define G_RM_VISCVG         RM_VISCVG(1)
#define G_RM_VISCVG2        RM_VISCVG(2)
#define G_RM_OPA_CI         RM_OPA_CI(1)
#define G_RM_OPA_CI2        RM_OPA_CI(2)


#define G_RM_FOG_SHADE_A    GBL_c1(G_BL_CLR_FOG, G_BL_A_SHADE, G_BL_CLR_IN, G_BL_1MA)
#define G_RM_FOG_PRIM_A     GBL_c1(G_BL_CLR_FOG, G_BL_A_FOG, G_BL_CLR_IN, G_BL_1MA)
#define G_RM_PASS           GBL_c1(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)

/*
 * G_SETCONVERT: K0-5
 */
#define G_CV_K0     175
#define G_CV_K1     -43
#define G_CV_K2     -89
#define G_CV_K3     222
#define G_CV_K4     114
#define G_CV_K5     42

/*
 * G_SETSCISSOR: interlace mode
 */
#define G_SC_NON_INTERLACE  0
#define G_SC_ODD_INTERLACE  3
#define G_SC_EVEN_INTERLACE 2

/*
 * Data Structures
 */

/**
 * Vertex (set up for use with colors)
 */
typedef struct {
    short          ob[3];   /** x, y, z */
    unsigned short flag;    /** Holds packed normals, or unused */
    short          tc[2];   /** texture coord */
    unsigned char  cn[4];   /** color & alpha */
} Vtx_t;

/**
 * @copydetails Vtx_t
 */
typedef struct {
    short          ob[3];   /** x, y, z */
    unsigned short flag;    /** Packed normals are not used when normals are in colors */
    short          tc[2];   /** texture coord */
    signed char    n[3];    /** normal */
    unsigned char  a;       /** alpha  */
} Vtx_tn;

/**
 * @copydetails Vtx_t
 */
typedef union {
    Vtx_t  v;   /** Use this one for colors  */
    Vtx_tn n;   /** Use this one for normals */
    long long int force_structure_alignment;
} Vtx;

typedef struct {
    short pos[3];
    short pad; /** value ignored, need not be 0 */
} PlainVtx_t;

typedef union {
    PlainVtx_t c;
    long long int force_structure_alignment;
} PlainVtx;

/**
 * Triangle face
 */
typedef struct {
    unsigned char flag;
    unsigned char v[3];
} Tri;

/**
 * 4x4 matrix, fixed point s15.16 format.
 * First 8 words are integer portion of the 4x4 matrix
 * Last 8 words are the fraction portion of the 4x4 matrix
 */
typedef long int Mtx_t[4][4];
typedef union {
    Mtx_t   m;
    struct {
        u16 intPart[4][4];
        u16 fracPart[4][4];
    };
    long long int force_structure_alignment;
} Mtx;

#define IPART(x) (((s32)((x) * 0x10000) >> 16) & 0xFFFF)
#define FPART(x)  ((s32)((x) * 0x10000) & 0xFFFF)

#define gdSPDefMtx( \
        xx, xy, xz, xw, \
        yx, yy, yz, yw, \
        zx, zy, zz, zw, \
        wx, wy, wz, ww) \
    { { \
        (IPART(xx) << 16) | IPART(yx), \
        (IPART(zx) << 16) | IPART(wx), \
        (IPART(xy) << 16) | IPART(yy), \
        (IPART(zy) << 16) | IPART(wy), \
        (IPART(xz) << 16) | IPART(yz), \
        (IPART(zz) << 16) | IPART(wz), \
        (IPART(xw) << 16) | IPART(yw), \
        (IPART(zw) << 16) | IPART(ww), \
        (FPART(xx) << 16) | FPART(yx), \
        (FPART(zx) << 16) | FPART(wx), \
        (FPART(xy) << 16) | FPART(yy), \
        (FPART(zy) << 16) | FPART(wy), \
        (FPART(xz) << 16) | FPART(yz), \
        (FPART(zz) << 16) | FPART(wz), \
        (FPART(xw) << 16) | FPART(yw), \
        (FPART(zw) << 16) | FPART(ww), \
    } }

/*
 * Viewport
 */

/*
 * This magic value is the maximum INTEGER z-range of the hardware
 * (there are also 16-bits of fraction, which are introduced during
 * any transformations). This is not just a good idea, it's the law.
 * Feeding the hardware eventual z-coordinates (after any transforms
 * or scaling) bigger than this, will not work.
 *
 * This number is DIFFERENT than G_MAXFBZ, which is the maximum value
 * you want to use to initialize the z-buffer.
 *
 * The reason these are different is mildly interesting, but too long
 * to explain here. It is basically the result of optimizations in the
 * hardware. A more generic API might hide this detail from the users,
 * but we don't have the ucode to do that...
 *
 */
#define G_MAXZ  0x03FF  /* 10 bits of integer screen-Z precision */

/**
 * The viewport structure elements have 2 bits of fraction, necessary
 * to accomodate the sub-pixel positioning scaling for the hardware.
 * This can also be exploited to handle odd-sized viewports.
 *
 * Accounting for these fractional bits, using the default projection
 * and viewing matrices, the viewport structure is initialized thusly:
 *
 *      (SCREEN_WD/2)*4, (SCREEN_HT/2)*4, G_MAXZ, 0,
 *      (SCREEN_WD/2)*4, (SCREEN_HT/2)*4, 0, 0,
 */
typedef struct {
    short vscale[4];    /** scale, 2 bits fraction */
    short vtrans[4];    /** translate, 2 bits fraction */
    /* both the above arrays are padded to 64-bit boundary */
} Vp_t;

typedef union {
    Vp_t vp;
    long long int force_structure_alignment[2];
} Vp;

/**
 * Light structure.
 *
 * Note: the weird order is for the DMEM alignment benefit of
 * the microcode.
 */
typedef struct {
    unsigned char col[3];   /** diffuse light color (rgb) */
    unsigned char type;     /** formerly pad1; MUST SET TO 0 to indicate directional light */
    unsigned char colc[3];  /** copy of diffuse light color (rgb) */
    char          pad2;
    signed char   dir[3];   /** direction of light (normalized) */
    char          pad3;
    char          pad4[3];
    unsigned char size;     /** For specular only; reasonable values are 1-4 */
} Light_t;

/**
 * Light structure.
 *
 * Note: the weird order is for the DMEM alignment benefit of
 * the microcode.
 */
typedef struct {
    unsigned char col[3];   /** point light color (rgb) */
    unsigned char kc;       /** constant attenuation (> 0 indicates point light) */
    unsigned char colc[3];  /** copy of point light color (rgb) */
    unsigned char kl;       /** linear attenuation */
    short         pos[3];   /** world-space position of light */
    unsigned char kq;       /** quadratic attenuation */
    unsigned char size;     /** For specular only; reasonable values are 1-4 */
} PointLight_t;

/**
 * @copydetails PosLight_t
 */
typedef struct {
    unsigned char col[3];   /** ambient light color (rgb) */
    char          pad1;
    unsigned char colc[3];  /** copy of ambient light color (rgb) */
    char          pad2;
} Ambient_t;

typedef struct {
    signed char   dir[3];   /** direction of lookat (normalized) */
    char          pad1;
} LookAt_t;

typedef struct {
    LookAt_t      l;        /** for backwards compatibility */
} LookAtWrapper;

typedef struct {
    /* texture offsets for highlight 1/2 */
    int x1;
    int y1;
    int x2;
    int y2;
} Hilite_t;

typedef struct {
    short c0;
    short c1;
    short c2;
    short c3;
    short c4;
    short c5;
    short c6;
    short c7;
    short kx;
    short ky;
    short kz;
    short kc;
} OcclusionPlane_t;

typedef struct {
    struct {
        short x;
        short y;
        short z;
    } v[4]; /** Four vertices of a quad, XYZ components in world space */
    float weight; /** Higher if there's a lot of stuff behind it */
} OcclusionPlaneCandidate;

typedef union {
    Light_t       l;
    PointLight_t  p;
    long long int force_structure_alignment[2];
} Light;

typedef union {
    Ambient_t l;
    long long int force_structure_alignment[1];
} Ambient;

typedef union {
    LookAtWrapper l[2];
    long long int force_structure_alignment[1];
} LookAt;

typedef union {
    Hilite_t h;
    long int force_structure_alignment;
} Hilite;

typedef union {
    OcclusionPlane_t o;
    short c[12];
    long long int force_structure_alignment[3];
} OcclusionPlane;

typedef struct {
    Light   l[9];
    Ambient a;
} Lightsn;

typedef struct {
    /* F3DEX3 properly supports zero lights, unlike F3DEX2 where you need
    to include one black directional light. */
    Ambient a;
} Lights0;

typedef struct {
    Light   l[1];
    Ambient a;
} Lights1;

typedef struct {
    Light   l[2];
    Ambient a;
} Lights2;

typedef struct {
    Light   l[3];
    Ambient a;
} Lights3;

typedef struct {
    Light   l[4];
    Ambient a;
} Lights4;

typedef struct {
    Light   l[5];
    Ambient a;
} Lights5;

typedef struct {
    Light   l[6];
    Ambient a;
} Lights6;

typedef struct {
    Light   l[7];
    Ambient a;
} Lights7;

typedef struct {
    Light   l[8];
    Ambient a;
} Lights8;

typedef struct {
    Light   l[9];
    Ambient a;
} Lights9;

#define gDefAmbient(r, g, b)    \
    {{                          \
        { (r), (g), (b) }, 0,   \
        { (r), (g), (b) }, 0,   \
    }}

#define gDefLight(r, g, b, x, y, z) \
    {{                              \
        { (r), (g), (b) }, 0,       \
        { (r), (g), (b) }, 0,       \
        { (x), (y), (z) }, 0,       \
        {  0,   0,   0  }, 0,       \
    }}

#define gdSPDefLights0(ar, ag, ab)                  \
        {                                           \
            gDefAmbient(ar, ag, ab),                \
        }

#define gdSPDefLights1(ar, ag, ab,                  \
                       r1, g1, b1, x1, y1, z1)      \
        {                                           \
            {                                       \
                gDefLight(r1, g1, b1, x1, y1, z1),  \
            },                                      \
            gDefAmbient(ar, ag, ab),                \
        }

#define gdSPDefLights2(ar, ag, ab,                  \
                       r1, g1, b1, x1, y1, z1,      \
                       r2, g2, b2, x2, y2, z2)      \
        {                                           \
            {                                       \
                gDefLight(r1, g1, b1, x1, y1, z1),  \
                gDefLight(r2, g2, b2, x2, y2, z2),  \
            },                                      \
            gDefAmbient(ar, ag, ab),                \
        }

#define gdSPDefLights3(ar, ag, ab,                  \
                       r1, g1, b1, x1, y1, z1,      \
                       r2, g2, b2, x2, y2, z2)      \
                       r3, g3, b3, x3, y3, z3)      \
        {                                           \
            {                                       \
                gDefLight(r1, g1, b1, x1, y1, z1),  \
                gDefLight(r2, g2, b2, x2, y2, z2),  \
                gDefLight(r3, g3, b3, x3, y3, z3),  \
            },                                      \
            gDefAmbient(ar, ag, ab),                \
        }

#define gdSPDefLights4(ar, ag, ab,                  \
                       r1, g1, b1, x1, y1, z1,      \
                       r2, g2, b2, x2, y2, z2,      \
                       r3, g3, b3, x3, y3, z3,      \
                       r4, g4, b4, x4, y4, z4)      \
        {                                           \
            {                                       \
                gDefLight(r1, g1, b1, x1, y1, z1),  \
                gDefLight(r2, g2, b2, x2, y2, z2),  \
                gDefLight(r3, g3, b3, x3, y3, z3),  \
                gDefLight(r4, g4, b4, x4, y4, z4),  \
            },                                      \
            gDefAmbient(ar, ag, ab),                \
        }

#define gdSPDefLights5(ar, ag, ab,                  \
                       r1, g1, b1, x1, y1, z1,      \
                       r2, g2, b2, x2, y2, z2,      \
                       r3, g3, b3, x3, y3, z3,      \
                       r4, g4, b4, x4, y4, z4,      \
                       r5, g5, b5, x5, y5, z5)      \
        {                                           \
            {                                       \
                gDefLight(r1, g1, b1, x1, y1, z1),  \
                gDefLight(r2, g2, b2, x2, y2, z2),  \
                gDefLight(r3, g3, b3, x3, y3, z3),  \
                gDefLight(r4, g4, b4, x4, y4, z4),  \
                gDefLight(r5, g5, b5, x5, y5, z5),  \
            },                                      \
            gDefAmbient(ar, ag, ab),                \
        }

#define gdSPDefLights6(ar, ag, ab,                  \
                       r1, g1, b1, x1, y1, z1,      \
                       r2, g2, b2, x2, y2, z2,      \
                       r3, g3, b3, x3, y3, z3,      \
                       r4, g4, b4, x4, y4, z4,      \
                       r5, g5, b5, x5, y5, z5,      \
                       r6, g6, b6, x6, y6, z6)      \
        {                                           \
            {                                       \
                gDefLight(r1, g1, b1, x1, y1, z1),  \
                gDefLight(r2, g2, b2, x2, y2, z2),  \
                gDefLight(r3, g3, b3, x3, y3, z3),  \
                gDefLight(r4, g4, b4, x4, y4, z4),  \
                gDefLight(r5, g5, b5, x5, y5, z5),  \
                gDefLight(r6, g6, b6, x6, y6, z6),  \
            },                                      \
            gDefAmbient(ar, ag, ab),                \
        }

#define gdSPDefLights7(ar, ag, ab,                  \
                       r1, g1, b1, x1, y1, z1,      \
                       r2, g2, b2, x2, y2, z2,      \
                       r3, g3, b3, x3, y3, z3,      \
                       r4, g4, b4, x4, y4, z4,      \
                       r5, g5, b5, x5, y5, z5,      \
                       r6, g6, b6, x6, y6, z6,      \
                       r7, g7, b7, x7, y7, z7)      \
        {                                           \
            {                                       \
                gDefLight(r1, g1, b1, x1, y1, z1),  \
                gDefLight(r2, g2, b2, x2, y2, z2),  \
                gDefLight(r3, g3, b3, x3, y3, z3),  \
                gDefLight(r4, g4, b4, x4, y4, z4),  \
                gDefLight(r5, g5, b5, x5, y5, z5),  \
                gDefLight(r6, g6, b6, x6, y6, z6),  \
                gDefLight(r7, g7, b7, x7, y7, z7),  \
            },                                      \
            gDefAmbient(ar, ag, ab),                \
        }

#define gdSPDefLights8(ar, ag, ab,                  \
                       r1, g1, b1, x1, y1, z1,      \
                       r2, g2, b2, x2, y2, z2,      \
                       r3, g3, b3, x3, y3, z3,      \
                       r4, g4, b4, x4, y4, z4,      \
                       r5, g5, b5, x5, y5, z5,      \
                       r6, g6, b6, x6, y6, z6,      \
                       r7, g7, b7, x7, y7, z7,      \
                       r8, g8, b8, x8, y8, z8)      \
        {                                           \
            {                                       \
                gDefLight(r1, g1, b1, x1, y1, z1),  \
                gDefLight(r2, g2, b2, x2, y2, z2),  \
                gDefLight(r3, g3, b3, x3, y3, z3),  \
                gDefLight(r4, g4, b4, x4, y4, z4),  \
                gDefLight(r5, g5, b5, x5, y5, z5),  \
                gDefLight(r6, g6, b6, x6, y6, z6),  \
                gDefLight(r7, g7, b7, x7, y7, z7),  \
                gDefLight(r8, g8, b8, x8, y8, z8),  \
            },                                      \
            gDefAmbient(ar, ag, ab),                \
        }

#define gdSPDefLights9(ar, ag, ab,                  \
                       r1, g1, b1, x1, y1, z1,      \
                       r2, g2, b2, x2, y2, z2,      \
                       r3, g3, b3, x3, y3, z3,      \
                       r4, g4, b4, x4, y4, z4,      \
                       r5, g5, b5, x5, y5, z5,      \
                       r6, g6, b6, x6, y6, z6,      \
                       r7, g7, b7, x7, y7, z7,      \
                       r8, g8, b8, x8, y8, z8,      \
                       r9, g9, b9, x9, y9, z9)      \
        {                                           \
            {                                       \
                gDefLight(r1, g1, b1, x1, y1, z1),  \
                gDefLight(r2, g2, b2, x2, y2, z2),  \
                gDefLight(r3, g3, b3, x3, y3, z3),  \
                gDefLight(r4, g4, b4, x4, y4, z4),  \
                gDefLight(r5, g5, b5, x5, y5, z5),  \
                gDefLight(r6, g6, b6, x6, y6, z6),  \
                gDefLight(r7, g7, b7, x7, y7, z7),  \
                gDefLight(r8, g8, b8, x8, y8, z8),  \
                gDefLight(r9, g9, b9, x9, y9, z9),  \
            },                                      \
            gDefAmbient(ar, ag, ab),                \
        }

#define gDefPointLight(r, g, b, x, y, z, kc, kl, kq)    \
    {{                                                  \
        { (r1), (g1), (b1) }, (kc),                     \
        { (r1), (g1), (b1) }, (kl),                     \
        { (x1), (y1), (z1) }, (kq),                     \
        0,                                              \
    }}

#define gdSPDefPointLights0(ar, ag, ab)                     \
        {                                                   \
            gDefAmbient(ar, ag, ab),                        \
        }

#define gdSPDefPointLights1(ar, ag, ab,                             \
                            r1, g1, b1, x1, y1, z1, c1, l1, q1)     \
        {                                                           \
            {                                                       \
                gDefPointLight(r1, g1, b1, x1, y1, z1, c1, l1, q1), \
            },                                                      \
            gDefAmbient(ar, ag, ab),                                \
        }

#define gdSPDefPointLights2(ar, ag, ab,                             \
                            r1, g1, b1, x1, y1, z1, c1, l1, q1,     \
                            r2, g2, b2, x2, y2, z2, c2, l2, q2)     \
        {                                                           \
            {                                                       \
                gDefPointLight(r1, g1, b1, x1, y1, z1, c1, l1, q1), \
                gDefPointLight(r2, g2, b2, x2, y2, z2, c2, l2, q2), \
            },                                                      \
            gDefAmbient(ar, ag, ab),                                \
        }

#define gdSPDefPointLights3(ar, ag, ab,                             \
                            r1, g1, b1, x1, y1, z1, c1, l1, q1,     \
                            r2, g2, b2, x2, y2, z2, c2, l2, q2,     \
                            r3, g3, b3, x3, y3, z3, c3, l3, q3)     \
        {                                                           \
            {                                                       \
                gDefPointLight(r1, g1, b1, x1, y1, z1, c1, l1, q1), \
                gDefPointLight(r2, g2, b2, x2, y2, z2, c2, l2, q2), \
                gDefPointLight(r3, g3, b3, x3, y3, z3, c3, l3, q3), \
            },                                                      \
            gDefAmbient(ar, ag, ab),                                \
        }

#define gdSPDefPointLights4(ar, ag, ab,                             \
                            r1, g1, b1, x1, y1, z1, c1, l1, q1,     \
                            r2, g2, b2, x2, y2, z2, c2, l2, q2,     \
                            r3, g3, b3, x3, y3, z3, c3, l3, q3,     \
                            r4, g4, b4, x4, y4, z4, c4, l4, q4)     \
        {                                                           \
            {                                                       \
                gDefPointLight(r1, g1, b1, x1, y1, z1, c1, l1, q1), \
                gDefPointLight(r2, g2, b2, x2, y2, z2, c2, l2, q2), \
                gDefPointLight(r3, g3, b3, x3, y3, z3, c3, l3, q3), \
                gDefPointLight(r4, g4, b4, x4, y4, z4, c4, l4, q4), \
            },                                                      \
            gDefAmbient(ar, ag, ab),                                \
        }

#define gdSPDefPointLights5(ar, ag, ab,                             \
                            r1, g1, b1, x1, y1, z1, c1, l1, q1,     \
                            r2, g2, b2, x2, y2, z2, c2, l2, q2,     \
                            r3, g3, b3, x3, y3, z3, c3, l3, q3,     \
                            r4, g4, b4, x4, y4, z4, c4, l4, q4,     \
                            r5, g5, b5, x5, y5, z5, c5, l5, q5)     \
        {                                                           \
            {                                                       \
                gDefPointLight(r1, g1, b1, x1, y1, z1, c1, l1, q1), \
                gDefPointLight(r2, g2, b2, x2, y2, z2, c2, l2, q2), \
                gDefPointLight(r3, g3, b3, x3, y3, z3, c3, l3, q3), \
                gDefPointLight(r4, g4, b4, x4, y4, z4, c4, l4, q4), \
                gDefPointLight(r5, g5, b5, x5, y5, z5, c5, l5, q5), \
            },                                                      \
            gDefAmbient(ar, ag, ab),                                \
        }

#define gdSPDefPointLights6(ar, ag, ab,                             \
                            r1, g1, b1, x1, y1, z1, c1, l1, q1,     \
                            r2, g2, b2, x2, y2, z2, c2, l2, q2,     \
                            r3, g3, b3, x3, y3, z3, c3, l3, q3,     \
                            r4, g4, b4, x4, y4, z4, c4, l4, q4,     \
                            r5, g5, b5, x5, y5, z5, c5, l5, q5,     \
                            r6, g6, b6, x6, y6, z6, c6, l6, q6)     \
        {                                                           \
            {                                                       \
                gDefPointLight(r1, g1, b1, x1, y1, z1, c1, l1, q1), \
                gDefPointLight(r2, g2, b2, x2, y2, z2, c2, l2, q2), \
                gDefPointLight(r3, g3, b3, x3, y3, z3, c3, l3, q3), \
                gDefPointLight(r4, g4, b4, x4, y4, z4, c4, l4, q4), \
                gDefPointLight(r5, g5, b5, x5, y5, z5, c5, l5, q5), \
                gDefPointLight(r6, g6, b6, x6, y6, z6, c6, l6, q6), \
            },                                                      \
            gDefAmbient(ar, ag, ab),                                \
        }

#define gdSPDefPointLights7(ar, ag, ab,                             \
                            r1, g1, b1, x1, y1, z1, c1, l1, q1,     \
                            r2, g2, b2, x2, y2, z2, c2, l2, q2,     \
                            r3, g3, b3, x3, y3, z3, c3, l3, q3,     \
                            r4, g4, b4, x4, y4, z4, c4, l4, q4,     \
                            r5, g5, b5, x5, y5, z5, c5, l5, q5,     \
                            r6, g6, b6, x6, y6, z6, c6, l6, q6,     \
                            r7, g7, b7, x7, y7, z7, c7, l7, q7)     \
        {                                                           \
            {                                                       \
                gDefPointLight(r1, g1, b1, x1, y1, z1, c1, l1, q1), \
                gDefPointLight(r2, g2, b2, x2, y2, z2, c2, l2, q2), \
                gDefPointLight(r3, g3, b3, x3, y3, z3, c3, l3, q3), \
                gDefPointLight(r4, g4, b4, x4, y4, z4, c4, l4, q4), \
                gDefPointLight(r5, g5, b5, x5, y5, z5, c5, l5, q5), \
                gDefPointLight(r6, g6, b6, x6, y6, z6, c6, l6, q6), \
                gDefPointLight(r7, g7, b7, x7, y7, z7, c7, l7, q7), \
            },                                                      \
            gDefAmbient(ar, ag, ab),                                \
        }

#define gdSPDefPointLights8(ar, ag, ab,                             \
                            r1, g1, b1, x1, y1, z1, c1, l1, q1,     \
                            r2, g2, b2, x2, y2, z2, c2, l2, q2,     \
                            r3, g3, b3, x3, y3, z3, c3, l3, q3,     \
                            r4, g4, b4, x4, y4, z4, c4, l4, q4,     \
                            r5, g5, b5, x5, y5, z5, c5, l5, q5,     \
                            r6, g6, b6, x6, y6, z6, c6, l6, q6,     \
                            r7, g7, b7, x7, y7, z7, c7, l7, q7,     \
                            r8, g8, b8, x8, y8, z8, c8, l8, q8)     \
        {                                                           \
            {                                                       \
                gDefPointLight(r1, g1, b1, x1, y1, z1, c1, l1, q1), \
                gDefPointLight(r2, g2, b2, x2, y2, z2, c2, l2, q2), \
                gDefPointLight(r3, g3, b3, x3, y3, z3, c3, l3, q3), \
                gDefPointLight(r4, g4, b4, x4, y4, z4, c4, l4, q4), \
                gDefPointLight(r5, g5, b5, x5, y5, z5, c5, l5, q5), \
                gDefPointLight(r6, g6, b6, x6, y6, z6, c6, l6, q6), \
                gDefPointLight(r7, g7, b7, x7, y7, z7, c7, l7, q7), \
                gDefPointLight(r8, g8, b8, x8, y8, z8, c8, l8, q8), \
            },                                                      \
            gDefAmbient(ar, ag, ab),                                \
        }

#define gdSPDefPointLights9(ar, ag, ab,                             \
                            r1, g1, b1, x1, y1, z1, c1, l1, q1,     \
                            r2, g2, b2, x2, y2, z2, c2, l2, q2,     \
                            r3, g3, b3, x3, y3, z3, c3, l3, q3,     \
                            r4, g4, b4, x4, y4, z4, c4, l4, q4,     \
                            r5, g5, b5, x5, y5, z5, c5, l5, q5,     \
                            r6, g6, b6, x6, y6, z6, c6, l6, q6,     \
                            r7, g7, b7, x7, y7, z7, c7, l7, q7,     \
                            r8, g8, b8, x8, y8, z8, c8, l8, q8,     \
                            r9, g9, b9, x9, y9, z9, c9, l9, q9)     \
        {                                                           \
            {                                                       \
                gDefPointLight(r1, g1, b1, x1, y1, z1, c1, l1, q1), \
                gDefPointLight(r2, g2, b2, x2, y2, z2, c2, l2, q2), \
                gDefPointLight(r3, g3, b3, x3, y3, z3, c3, l3, q3), \
                gDefPointLight(r4, g4, b4, x4, y4, z4, c4, l4, q4), \
                gDefPointLight(r5, g5, b5, x5, y5, z5, c5, l5, q5), \
                gDefPointLight(r6, g6, b6, x6, y6, z6, c6, l6, q6), \
                gDefPointLight(r7, g7, b7, x7, y7, z7, c7, l7, q7), \
                gDefPointLight(r8, g8, b8, x8, y8, z8, c8, l8, q8), \
                gDefPointLight(r9, g9, b9, x9, y9, z9, c9, l9, q9), \
            },                                                      \
            gDefAmbient(ar, ag, ab),                                \
        }

#define gdSPDefLookAt(rightx, righty, rightz, upx, upy, upz)    \
    {                                                           \
        {{{ rightx, righty, rightz }, 0 }},                     \
        {{{ upx, upy, upz }, 0 }},                              \
    }

typedef struct {
    int          cmd  : 8;
    unsigned int type : 8;
    unsigned int len  : 16;
    union {
        /* The exact form of this callback is intentionally left unspecified, a display list
        parser may choose the return value and parameters so long as it is consistent. */
        void       (*callback)();
        const char*  str;
        unsigned int u32;
        float        f32;
        void*        addr;
    } value;
} Gnoop;

/**
 *  Graphics DMA Packet
 */
typedef struct {
    int          cmd : 8;
    unsigned int par : 8;
    unsigned int len : 16;
    unsigned int addr;
} Gdma;

/**
 * @copydoc Gdma
 */
typedef struct {
    int          cmd : 8;
    unsigned int len : 8;
    unsigned int ofs : 8;
    unsigned int par : 8;
    unsigned int addr;
} Gdma2;

/**
 * Graphics Moveword Packet
 */
typedef struct {
    int          cmd    : 8;
    unsigned int index  : 8;
    unsigned int offset : 16;
    unsigned int data;
} Gmovewd;

/**
 * @copydetails Gmovewd
 */
typedef struct {
    int          cmd    : 8;
    unsigned int size   : 8;
    unsigned int offset : 8;
    unsigned int index  : 8;
    unsigned int data;
} Gmovemem;

/**
 * Graphics Immediate Mode Packet types
 */
typedef struct {
    int cmd : 8;
    int pad : 24;
    Tri tri;
} Gtri;

typedef struct {
    Tri tri1; /* flag is the command byte */
    Tri tri2;
} Gtri2;

typedef struct {
    Tri tri1; /* flag is the command byte */
    Tri tri2;
} Gquad;

typedef struct {
    int            cmd : 8;
    unsigned int   pad : 8;
    unsigned short vstart_x2;
    unsigned short pad2;
    unsigned short vend_x2;
} Gcull;

typedef struct {
    int            cmd : 8;
    unsigned int   pad : 24;
    unsigned short z;
    unsigned short dz;
} Gsetprimdepth;

typedef struct {
    int           cmd   : 8;
    int           pad1  : 24;
    unsigned int  param;
} Gpopmtx;

typedef struct {
    int cmd      : 8;
    int mw_index : 8;
    int pad0     : 8;
    int number   : 8;
    int pad1     : 8;
    int base     : 24;
} Gsegment;

typedef struct {
    int          cmd  : 8;
    int          pad0 : 8;
    unsigned int sft  : 8;
    unsigned int len  : 8;
    unsigned int data : 32;
} GsetothermodeL;

typedef struct {
    int          cmd  : 8;
    int          pad0 : 8;
    unsigned int sft  : 8;
    unsigned int len  : 8;
    unsigned int data : 32;
} GsetothermodeH;

typedef struct {
    unsigned char  cmd;
    unsigned char  lodscale;
    unsigned char  pad   : 2;
    unsigned char  level : 3;
    unsigned char  tile  : 3;
    unsigned char  on;
    unsigned short s;
    unsigned short t;
} Gtexture;

typedef struct {
    int       cmd  : 8;
    int       pad1 : 24;
    short int pad2;
    short int scale;
} Gperspnorm;


/**
 * RDP Packet types
 */
typedef struct {
    int          cmd : 8;
    unsigned int fmt : 3;
    unsigned int siz : 2;
    unsigned int pad : 7;
    unsigned int wd  : 12;  /* really only 10 bits, extra  */
    unsigned int dram;      /* to account for 1024  */
} Gsetimg;

typedef struct {
    int          cmd : 8;
    /* muxs0 */
    unsigned int a0  : 4;
    unsigned int c0  : 5;
    unsigned int Aa0 : 3;
    unsigned int Ac0 : 3;
    unsigned int a1  : 4;
    unsigned int c1  : 5;
    /* muxs1 */
    unsigned int b0  : 4;
    unsigned int b1  : 4;
    unsigned int Aa1 : 3;
    unsigned int Ac1 : 3;
    unsigned int d0  : 3;
    unsigned int Ab0 : 3;
    unsigned int Ad0 : 3;
    unsigned int d1  : 3;
    unsigned int Ab1 : 3;
    unsigned int Ad1 : 3;
} Gsetcombine;

typedef struct {
    int           cmd : 8;
    unsigned char pad;
    unsigned char prim_min_level;
    unsigned char prim_level;
    union {
        unsigned long color;
        struct {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
        };
    };
} Gsetcolor;

typedef struct {
    int          cmd    : 8;
    int          x0     : 10;
    int          x0frac : 2;
    int          y0     : 10;
    int          y0frac : 2;
    unsigned int pad    : 8;
    int          x1     : 10;
    int          x1frac : 2;
    int          y1     : 10;
    int          y1frac : 2;
} Gfillrect;

typedef struct {
    int          cmd     : 8;
    unsigned int fmt     : 3;
    unsigned int siz     : 2;
    unsigned int pad0    : 1;
    unsigned int line    : 9;
    unsigned int tmem    : 9;
    unsigned int pad1    : 5;
    unsigned int tile    : 3;
    unsigned int palette : 4;
    unsigned int ct      : 1;
    unsigned int mt      : 1;
    unsigned int maskt   : 4;
    unsigned int shiftt  : 4;
    unsigned int cs      : 1;
    unsigned int ms      : 1;
    unsigned int masks   : 4;
    unsigned int shifts  : 4;
} Gsettile;

typedef struct {
    int          cmd  : 8;
    unsigned int sl   : 12;
    unsigned int tl   : 12;
    int          pad  : 5;
    unsigned int tile : 3;
    unsigned int sh   : 12;
    unsigned int th   : 12;
} Gloadtile;

typedef Gloadtile Gloadblock;

typedef Gloadtile Gsettilesize;

typedef Gloadtile Gloadtlut;

typedef struct {
    unsigned int cmd  : 8;  /* command                      */
    unsigned int xl   : 12; /* X coordinate of upper left   */
    unsigned int yl   : 12; /* Y coordinate of upper left   */
    unsigned int pad1 : 5;  /* Padding                      */
    unsigned int tile : 3;  /* Tile descriptor index        */
    unsigned int xh   : 12; /* X coordinate of lower right  */
    unsigned int yh   : 12; /* Y coordinate of lower right  */
    unsigned int s    : 16; /* S texture coord at top left  */
    unsigned int t    : 16; /* T texture coord at top left  */
    unsigned int dsdx : 16; /* Change in S per change in X  */
    unsigned int dtdy : 16; /* Change in T per change in Y  */
} Gtexrect;

#define MakeTexRect(xh,yh,flip,tile,xl,yl,s,t,dsdx,dtdy)        \
    G_TEXRECT, xh, yh, 0, flip, 0, tile, xl, yl, s, t, dsdx, dtdy

/**
 * Textured rectangles are 128 bits not 64 bits
 */
typedef struct {
    unsigned long w0;
    unsigned long w1;
    unsigned long w2;
    unsigned long w3;
} TexRect;

typedef struct {
    int           cmd  : 8;
    unsigned int  pad  : 4;
    unsigned int  len  : 8; /* n */
    unsigned int  pad2 : 4;
    unsigned char par;      /* v0 */
    unsigned int  addr;
} Gvtx;

/**
 * Generic Gfx Packet
 */
typedef struct {
    unsigned int w0;
    unsigned int w1;
} Gwords;

/**
 * This union is the fundamental type of the display list.
 * It is, by law, exactly 64 bits in size.
 */
typedef union {
    Gwords          words;
    Gnoop           noop;
    Gdma            dma;
    Gdma2           dma2;
    Gvtx            vtx;
    Gtri            tri;
    Gtri2           tri2;
    Gquad           quad;
    Gcull           cull;
    Gmovewd         movewd;
    Gmovemem        movemem;
    Gpopmtx         popmtx;
    Gsegment        segment;
    GsetothermodeH  setothermodeH;
    GsetothermodeL  setothermodeL;
    Gtexture        texture;
    Gperspnorm      perspnorm;
    Gsetimg         setimg;
    Gsetcombine     setcombine;
    Gsetcolor       setcolor;
    Gfillrect       fillrect;   /* use for setscissor also */
    Gsettile        settile;
    Gloadtile       loadtile;   /* use for loadblock also, th is dxt */
    Gsettilesize    settilesize;
    Gloadtlut       loadtlut;
    Gsetprimdepth   setprimdepth;
    long long int force_structure_alignment;
} Gfx;

/*
 * Macros to assemble the graphics display list
 */

/*
 * DMA macros
 */
#define gDma0p(pkt, c, s, l)                \
_DW({                                       \
    Gfx *_g = (Gfx *)(pkt);                 \
                                            \
    _g->words.w0 = (_SHIFTL((c), 24,  8) |  \
                    _SHIFTL((l),  0, 24));  \
    _g->words.w1 = (unsigned int)(s);       \
})

#define gsDma0p(c, s, l)    \
{                           \
   (_SHIFTL((c), 24,  8) |  \
    _SHIFTL((l),  0, 24)),  \
    (unsigned int)(s)       \
}

#define gDma1p(pkt, c, s, l, p)             \
_DW({                                       \
    Gfx *_g = (Gfx *)(pkt);                 \
                                            \
    _g->words.w0 = (_SHIFTL((c), 24,  8) |  \
                    _SHIFTL((p), 16,  8) |  \
                    _SHIFTL((l),  0, 16));  \
    _g->words.w1 = (unsigned int)(s);       \
})

#define gsDma1p(c, s, l, p) \
{                           \
   (_SHIFTL((c), 24,  8) |  \
    _SHIFTL((p), 16,  8) |  \
    _SHIFTL((l),  0, 16)),  \
    (unsigned int)(s)       \
}

#define gDma2p(pkt, c, adrs, len, idx, ofs)             \
_DW({                                                   \
    Gfx *_g = (Gfx *)(pkt);                             \
                                                        \
    _g->words.w0 = (_SHIFTL((c),             24, 8) |   \
                    _SHIFTL(((len) - 1) / 8, 19, 5) |   \
                    _SHIFTL((ofs) / 8,        8, 8) |   \
                    _SHIFTL((idx),            0, 8));   \
    _g->words.w1 = (unsigned int)(adrs);                \
})

#define gsDma2p(c, adrs, len, idx, ofs) \
{                                       \
   (_SHIFTL((c),             24, 8) |   \
    _SHIFTL(((len) - 1) / 8, 19, 5) |   \
    _SHIFTL((ofs) / 8,        8, 8) |   \
    _SHIFTL((idx),            0, 8)),   \
    (unsigned int)(adrs)                \
}

#define gSPNoOp(pkt)    gDma0p(pkt, G_SPNOOP, 0, 0)
#define gsSPNoOp()      gsDma0p(    G_SPNOOP, 0, 0)

/**
 * @brief macro which inserts a matrix operation at the end display list.
 * 
 * It inserts a matrix operation in the display list. The parameters allow you to select which matrix stack to use (projection or model view), where to load or concatenate, and whether or not to push the matrix stack. The following parameters are bit OR'ed together:
 * - @ref G_MTX_PROJECTION @ref G_MTX_MODELVIEW - @copybrief G_MTX_MODELVIEW
 * - @ref G_MTX_MUL - @copybrief G_MTX_MUL
 * - @ref G_MTX_LOAD - @copybrief G_MTX_LOAD
 * - @ref G_MTX_NOPUSH - @copybrief G_MTX_NOPUSH
 * - @ref G_MTX_PUSH - @copybrief G_MTX_PUSH
 * # Matrix Format
 * The format of the fixed-point matrices may seem a little awkward to the application programmer because it is optimized for the RSP geometry engine. This unusual format is hidden in the graphics utility libraries and not usually exposed to the application programmer, but in some cases (static matrix declarations or direct element manipulation) it is necessary to understand the format.
 * 
 * The integer and fractional components of the matrix elements are separated. The first 8 words (16 shorts) hold the 16-bit integer elements, the second 8 words (16 shorts) hold the 16-bit fractional elements. The fact that the Mtx type is declared as a long [4][4] array is slightly misleading. For example, to declare a static identity matrix, use code similar to this:
 * ```#include "gbi.h"
 * static Mtx ident =
 * {
 * // integer portion:
 * 0x00010000, 0x00000000,
 * 0x00000001, 0x00000000,
 * 0x00000000, 0x00010000,
 * 0x00000000, 0x00000001,
 * 
 * // fractional portion:
 * 0x00000000, 0x00000000,
 * 0x00000000, 0x00000000,
 * 0x00000000, 0x00000000,
 * 0x00000000, 0x00000000,
 * };
 * ```
 * To force the translation elements of a matrix to be (10.5, 20.5, 30.5), use code similar to this:
 * ```
 * #include "gbi.h"
 * 
 * mat.m[1][2] =
 *    (10 << 16) | (20);
 * mat.m[1][3] =
 *    (30 << 16) | (1);
 * 
 * mat.m[3][2] =
 *    (0x8000 << 16) | (0x8000);
 * mat.m[3][3] =
 *    (0x8000 << 16) | (0);
 * ```
 * @note
 * Matrix concatenation in the RSP geometry engine is done using 32-bit integer arithmetic. A 32 x 32 bit multiply results in a 64-bit number. Only the middle 32 bits of this 64-bit result are kept for the new matrix. Therefore, when concatenating matrices, remember about the resulting fixed-point numerical error.
 * 
 * For example, to retain maximum precision, the number ranges must be similar. Large-scale and translate parameters can decrease the transformation precision. Because rotation and projection matrices require quite a bit of fractional accuracy, these fractions may get tossed out if multiplied against large integer numbers.
 * 
 * Each concatenation results in the rounding of the LSB of each matrix term. This means that each concatenation injects 1/2 LSB of error into the matrix. To keep full precision, concatenate matrices in floating-point on the processor and just load the result into the RSP.
 * 
 * # Performance
 * Each @ref G_MTX_MODELVIEW matrix operation has an implicit matrix multiplication even if you specify @ref G_MTX_LOAD. This is the combined model view (M) and projection (P) matrix that is necessary for the vertex transformation to use a single matrix during transformation.
 * 
 * You can optimize this by concatenating modeling matrices on the CPU and then putting the viewing (V) and projection matrices on the projection stack. By doing this, you only incur the single MxVP matrix concatenation each time you load a modeling matrix. Furthermore, the application has more information on how to do a cheap hack for modeling matrix concatenation. For example, if you want to combine a single axis rotation with a translation, just place the coefficients in the correct entries of the resulting matrix.
 * 
 * @param m is the pointer to the 4x4 fixed-point matrix (see note below about format)
 * @param p are the bit OR'd parameters to the matrix macro (@ref G_MTX_PROJECTION, @ref G_MTX_MODELVIEW, @ref G_MTX_MUL, @ref G_MTX_LOAD, @ref G_MTX_NOPUSH)
 */
#define gSPMatrix(pkt, m, p) \
        gDma2p((pkt),G_MTX, (m), sizeof(Mtx), (p) ^ G_MTX_PUSH, 0)
/**
 * @brief macro which inserts a matrix operation in a static display list.
 * 
 * @copydetails gSPMatrix
 */
#define gsSPMatrix(m, p) \
        gsDma2p(     G_MTX, (m), sizeof(Mtx), (p) ^ G_MTX_PUSH, 0)

/**
 * @brief macro which pops one of the matrix stacks at the end display list.
 * 
 * It pops `num` of the matrix stacks. The model view stack can be up to 10 matrices deep. The projection stack is 1 matrix deep, so it cannot be popped.
 * 
 * @note
 * If the stack is empty, the macro is ignored.
 * 
 * @param n is the flag field that identifies which matrix stack to pop:
 * - @ref G_MTX_MODELVIEW pops the modeling/viewing matrix stack
 * - @ref G_MTX_PROJECTION pops the projection matrix stack (NOT IMPLEMENTED)
 * @param num is the number of matrices to pop
 */
#define gSPPopMatrixN(pkt, n, num) gDma2p((pkt), G_POPMTX, (num) * 64, 64, 2, 0)
/**
 * @brief macro which pops one of the matrix stacks in a static display list.
 * 
 * @copydetails gSPPopMatrixN
 */
#define gsSPPopMatrixN(n, num)     gsDma2p(      G_POPMTX, (num) * 64, 64, 2, 0)
/**
 * @brief macro which pops one of the matrix stacks at the end display list.
 * 
 * It pops one of the matrix stacks. The model view stack can be up to 10 matrices deep. The projection stack is 1 matrix deep, so it cannot be popped.
 * 
 * @note
 * If the stack is empty, the macro is ignored.
 * 
 * @param n is the flag field that identifies which matrix stack to pop:
 * - @ref G_MTX_MODELVIEW pops the modeling/viewing matrix stack
 * - @ref G_MTX_PROJECTION pops the projection matrix stack (NOT IMPLEMENTED)
 */
#define gSPPopMatrix(pkt, n)       gSPPopMatrixN((pkt), (n), 1)
/**
 * @brief macro which pops one of the matrix stacks in a static display list.
 * 
 * @copydetails gSPPopMatrix
 */
#define gsSPPopMatrix(n)           gsSPPopMatrixN(      (n), 1)

/**
 * @brief macro which loads an internal vertex buffer in the RSP with points that are used by @ref gSP1Triangle macros to generate polygons at the end display list.
 * 
 * 
 * It loads an internal vertex buffer in the RSP with points that are used by @ref gSP1Triangle macros to generate polygons. This vertex cache can hold up to 56 vertices, and the vertex loading can begin at any entry (index) within the cache. The vertex coordinates (x,y,z) are encoded in signed 2's complement, 16-bit integers. The texture coordinates (s,t) are encoded in S10.5 format. A vertex either has a color or a normal (for shading). These values are 8-bit values. The colors and alphas are treated as 8-bit unsigned values (0-255), but the normals are treated as 8-bit signed values (-128 to 127). Therefore, the appropriate member of the union to use (.v. or .n.) depends on whether you are using colors or normals.
 * 
 * Normal coordinates range from -1.0 to 1.0. A value of -1.0 is represented as -128, and a value of 1.0 is represented as 128, but because the maximum positive value of a signed byte is 127, a value of 1.0 can't really be represented. Therefore, 0.992 is the maximum representable positive value, which is good enough for this purpose.
 * 
 * The flag value is used for the packed normals feature to store normals with octahedral encoding.
 * 
 * The coordinates (x,y,z) are transformed using the current 4x4 projection and model view matrices, and (s,t) are transformed using the scale defined by gSPTexture.
 * 
 * # Example
 * To load vertex cache entry 2,3,4, use this code:
 * ```c
 * gSPVertex(glistp++, v, 3, 2);
 * ```
 * 
 * @note
 * Because the RSP geometry transformation engine uses a vertex list with triangle list architecture, it is quite powerful. A simple one-triangle macro retains least performance compared to @ref gSP2Triangles or the new 5 tris commands in EX3 (@ref gSPTriStrip, @ref gSPTriFan).
 * 
 * @param v is the pointer to the vertex list (segment address)
 * @param n is the number of vertices
 * @param v0 is the load vertex by index vo(0~55) in vertex buffer
 */
#define gSPVertex(pkt, v, n, v0)                    \
_DW({                                               \
    Gfx *_g = (Gfx *)(pkt);                         \
                                                    \
    _g->words.w0 = (_SHIFTL(G_VTX,      24, 8) |    \
                    _SHIFTL((n),        12, 8) |    \
                    _SHIFTL((v0) + (n),  1, 7));    \
    _g->words.w1 = (unsigned int)(v);               \
})

/**
 * @brief macro which loads an internal vertex buffer in the RSP with points that are used by gSP1Triangle macros to generate polygons in a static display list.
 * 
 * @copydetails gSPVertex
 */
#define gsSPVertex(v, n, v0)        \
{                                   \
   (_SHIFTL(G_VTX,      24, 8) |    \
    _SHIFTL((n),        12, 8) |    \
    _SHIFTL((v0) + (n),  1, 7)),    \
    (unsigned int)(v)               \
}

#define gSPViewport(pkt, v) \
        gDma2p((pkt), G_MOVEMEM, (v), sizeof(Vp), G_MV_VIEWPORT, 0)
#define gsSPViewport(v) \
        gsDma2p(      G_MOVEMEM, (v), sizeof(Vp), G_MV_VIEWPORT, 0)

/*
 * Display list control flow
 */

#define _gSPDisplayListRaw(pkt,dl,hint)  gDma1p(pkt, G_DL, dl, hint, G_DL_PUSH)
#define _gsSPDisplayListRaw(   dl,hint)  gsDma1p(    G_DL, dl, hint, G_DL_PUSH)

#define _gSPBranchListRaw(pkt,dl,hint)   gDma1p(pkt, G_DL, dl, hint, G_DL_NOPUSH)
#define _gsSPBranchListRaw(   dl,hint)   gsDma1p(    G_DL, dl, hint, G_DL_NOPUSH)

#define _gSPEndDisplayListRaw(pkt,hint)  gDma0p(pkt, G_ENDDL, 0, hint)
#define _gsSPEndDisplayListRaw(hint)     gsDma0p(    G_ENDDL, 0, hint)

/*
 * Converts a total expected count of DL commands to a number of bytes to
 * initially NOT load into the DL command buffer.
 */
#define _DLHINTVALUE(count) \
    (((count) > 0 && ((count) % G_INPUT_BUFFER_CMDS) > 0) ? \
    ((G_INPUT_BUFFER_CMDS - ((count) % G_INPUT_BUFFER_CMDS)) << 3) : 0)

/**
 * Optimization for reduced memory traffic. In count, put the estimated number
 * of DL commands in the target DL (the DL being called / jumped to, or the DL
 * being returned to, starting from the next command to be executed) up to and
 * including the next call / jump / return. Normally, for SPDisplayList, this is
 * just the total number of commands in the target DL. The actual on-screen
 * result will not change regardless of the value of count, but the performance
 * will be best if count is correct, and potentially worse than not specifying
 * count if it is wrong.
 * Feature suggested by Kaze Emanuar
 */
#define gSPDisplayListHint(pkt, dl, count) _gSPDisplayListRaw(pkt, dl, _DLHINTVALUE(count))
/**
 * @copydetails gSPDisplayListHint
 */
#define gsSPDisplayListHint(    dl, count) _gsSPDisplayListRaw(    dl, _DLHINTVALUE(count))

/**
 * @copydetails gSPDisplayListHint
 */
#define gSPBranchListHint(pkt, dl, count) _gSPBranchListRaw( pkt, dl, _DLHINTVALUE(count))

/**
 * @copydetails gSPDisplayListHint
 */
#define gsSPBranchListHint(    dl, count) _gsSPBranchListRaw(     dl, _DLHINTVALUE(count))

/**
 * @copydetails gSPDisplayListHint
 */
#define gSPEndDisplayListHint(pkt, count) _gSPEndDisplayListRaw( pkt, _DLHINTVALUE(count))

/**
 * @copydetails gSPDisplayListHint
 */
#define gsSPEndDisplayListHint(    count) _gsSPEndDisplayListRaw(     _DLHINTVALUE(count))

/**
 * Normal control flow commands; same as @ref gSPDisplayListHint but with hint of 0
 */
#define gSPDisplayList(pkt, dl) _gSPDisplayListRaw(pkt, dl, 0)
/**
 * Normal control flow commands; same as @ref gsSPDisplayListHint but with hint of 0
 */
#define gsSPDisplayList(    dl) _gsSPDisplayListRaw(    dl, 0)

/**
 * Normal control flow commands; same as @ref gSPBranchListHint but with hint of 0
 */
#define gSPBranchList(pkt, dl)  _gSPBranchListRaw( pkt, dl, 0)
/**
 * Normal control flow commands; same as @ref gsSPBranchListHint but with hint of 0
 */
#define gsSPBranchList(    dl)  _gsSPBranchListRaw(     dl, 0)

/**
 * Normal control flow commands; same as @ref gSPEndDisplayListHint but with hint of 0
 */
#define gSPEndDisplayList(pkt)  _gSPEndDisplayListRaw( pkt, 0)
/**
 * Normal control flow commands; same as @ref gsSPEndDisplayListHint but with hint of 0
 */
#define gsSPEndDisplayList(  )  _gsSPEndDisplayListRaw(     0)


/**
 * gSPLoadUcode   RSP loads specified ucode.
 *
 * uc_start  = ucode text section start
 * uc_dstart = ucode data section start
 */
#define gSPLoadUcodeEx(pkt, uc_start, uc_dstart, uc_dsize)  \
_DW({                                                       \
    Gfx *_g = (Gfx *)(pkt);                                 \
                                                            \
    _g->words.w0 = _SHIFTL(G_RDPHALF_1, 24, 8);             \
    _g->words.w1 = (unsigned int)(uc_dstart);               \
                                                            \
    _g = (Gfx *)(pkt);                                      \
                                                            \
    _g->words.w0 = (_SHIFTL(G_LOAD_UCODE,        24,  8) |  \
                    _SHIFTL((int)(uc_dsize) - 1,  0, 16));  \
    _g->words.w1 = (unsigned int)(uc_start);                \
})

/**
 * @copydetails gSPLoadUcodeEx
 */
#define gsSPLoadUcodeEx(uc_start, uc_dstart, uc_dsize)  \
{                                                       \
    _SHIFTL(G_RDPHALF_1, 24, 8),                        \
    (unsigned int)(uc_dstart),                          \
},                                                      \
{                                                       \
   (_SHIFTL(G_LOAD_UCODE,        24,  8) |              \
    _SHIFTL((int)(uc_dsize) - 1,  0, 16)),              \
    (unsigned int)(uc_start),                           \
}

#define gSPLoadUcode(pkt, uc_start, uc_dstart)  \
        gSPLoadUcodeEx((pkt), (uc_start), (uc_dstart), SP_UCODE_DATA_SIZE)
#define gsSPLoadUcode(uc_start, uc_dstart)      \
        gsSPLoadUcodeEx((uc_start), (uc_dstart), SP_UCODE_DATA_SIZE)

#define gSPLoadUcodeL(pkt, ucode)                                   \
        gSPLoadUcode((pkt), OS_K0_TO_PHYSICAL(& ucode##TextStart),  \
                            OS_K0_TO_PHYSICAL(& ucode##DataStart))
#define gsSPLoadUcodeL(ucode)                                       \
        gsSPLoadUcode(      OS_K0_TO_PHYSICAL(& ucode##TextStart),  \
                            OS_K0_TO_PHYSICAL(& ucode##DataStart))

/**
 * gSPDma_io  DMA to/from DMEM/IMEM for DEBUG.
 */
#define gSPDma_io(pkt, flag, dmem, dram, size)      \
_DW({                                               \
    Gfx *_g = (Gfx *)(pkt);                         \
                                                    \
    _g->words.w0 = (_SHIFTL(G_DMA_IO, 24, 8) |      \
                    _SHIFTL((flag), 23, 1) |        \
                    _SHIFTL((dmem) / 8, 13, 10) |   \
                    _SHIFTL((size) - 1, 0, 12));    \
    _g->words.w1 = (unsigned int)(dram);            \
})

/**
 * @copydetails gSPDma_io
 */
#define gsSPDma_io(flag, dmem, dram, size)  \
{                                           \
   (_SHIFTL(G_DMA_IO,   24,  8) |           \
    _SHIFTL((flag),     23,  1) |           \
    _SHIFTL((dmem) / 8, 13, 10) |           \
    _SHIFTL((size) - 1,  0, 12)),           \
    (unsigned int)(dram)                    \
}

#define gSPDmaRead(pkt,dmem,dram,size)  gSPDma_io((pkt),0,(dmem),(dram),(size))
#define gsSPDmaRead(dmem,dram,size)     gsSPDma_io(     0,(dmem),(dram),(size))
#define gSPDmaWrite(pkt,dmem,dram,size) gSPDma_io((pkt),1,(dmem),(dram),(size))
#define gsSPDmaWrite(dmem,dram,size)    gsSPDma_io(     1,(dmem),(dram),(size))

/**
 * Use RSP DMAs to set a region of memory to a repeated 16-bit value. This can
 * clear the color framebuffer or Z-buffer faster than the RDP can in fill mode.
 * SPMemset overwrites the DMEM vertex buffer, so vertices loaded before this
 * command cannot be used after it (though this would not normally be done).
 * 
 * dram: Segmented or physical start address. Must be aligned to 16 bytes.
 * value: 16-bit value to fill the memory with. e.g. 0 for color, 0xFFFC for Z.
 * size: Size in bytes to fill, must be nonzero and a multiple of 16 bytes.
 */
#define gSPMemset(pkt, dram, value, size)               \
_DW({                                                   \
    gImmp1(pkt, G_RDPHALF_1, ((value) & 0xFFFF));       \
    gDma0p(pkt, G_MEMSET, (dram), ((size) & 0xFFFFF0)); \
})

/**
 * @copydetails gSPMemset
 */
#define gsSPMemset(pkt, dram, value, size)    \
    gsImmp1(G_RDPHALF_1, ((value) & 0xFFFF)), \
    gsDma0p(G_MEMSET, (dram), ((size) & 0xFFFFF0))

/**
 * RSP short command (no DMA required) macros
 */
#define gImmp0(pkt, c)                  \
_DW({                                   \
    Gfx *_g = (Gfx *)(pkt);             \
                                        \
    _g->words.w0 = _SHIFTL((c), 24, 8); \
})

/**
 * @copydetails gImmp0
 */
#define gsImmp0(c)      \
{                       \
    _SHIFTL((c), 24, 8) \
}

#define gImmp1(pkt, c, p0)              \
_DW({                                   \
    Gfx *_g = (Gfx *)(pkt);             \
                                        \
    _g->words.w0 = _SHIFTL((c), 24, 8); \
    _g->words.w1 = (unsigned int)(p0);  \
})

#define gsImmp1(c, p0)      \
{                           \
    _SHIFTL((c), 24, 8),    \
    (unsigned int)(p0)      \
}

#define gImmp2(pkt, c, p0, p1)              \
_DW({                                       \
    Gfx *_g = (Gfx *)(pkt);                 \
                                            \
    _g->words.w0 = _SHIFTL((c), 24, 8);     \
    _g->words.w1 = (_SHIFTL((p0), 16, 16) | \
                    _SHIFTL((p1),  8,  8)); \
})

#define gsImmp2(c, p0, p1)  \
{                           \
    _SHIFTL((c), 24, 8),    \
   (_SHIFTL((p0), 16, 16) | \
    _SHIFTL((p1),  8,  8))  \
}

#define gImmp3(pkt, c, p0, p1, p2)          \
_DW({                                       \
    Gfx *_g = (Gfx *)(pkt);                 \
                                            \
    _g->words.w0 = _SHIFTL((c), 24, 8);     \
    _g->words.w1 = (_SHIFTL((p0), 16, 16) | \
                    _SHIFTL((p1),  8,  8) | \
                    _SHIFTL((p2),  0,  8)); \
})

#define gsImmp3(c, p0, p1, p2)  \
{                               \
    _SHIFTL((c), 24, 8),        \
   (_SHIFTL((p0), 16, 16) |     \
    _SHIFTL((p1),  8,  8) |     \
    _SHIFTL((p2),  0,  8))      \
}

#define gImmp21(pkt, c, p0, p1, dat)        \
_DW({                                       \
    Gfx *_g = (Gfx *)(pkt);                 \
                                            \
    _g->words.w0 = (_SHIFTL((c),  24,  8) | \
                    _SHIFTL((p0),  8, 16) | \
                    _SHIFTL((p1),  0,  8)); \
    _g->words.w1 = (unsigned int) (dat);    \
})

#define gsImmp21(c, p0, p1, dat)    \
{                                   \
   (_SHIFTL((c),  24,  8) |         \
    _SHIFTL((p0),  8, 16) |         \
    _SHIFTL((p1),  0,  8)),         \
    (unsigned int) (dat)            \
}

#define gMoveWd(pkt, index, offset, data) \
    gDma1p((pkt), G_MOVEWORD, data, (offset & 0xFFF), index)
#define gsMoveWd(    index, offset, data) \
    gsDma1p(      G_MOVEWORD, data, (offset & 0xFFF), index)
    
#define gMoveHalfwd(pkt, index, offset, data) \
    gDma1p((pkt), G_MOVEWORD, data, (offset & 0xFFF) | G_MW_HALFWORD_FLAG, index)
#define gsMoveHalfwd(    index, offset, data) \
    gsDma1p(      G_MOVEWORD, data, (offset & 0xFFF) | G_MW_HALFWORD_FLAG, index)


/*
 * Triangle commands
 */

#define __gsSP1Triangle_w1(v0, v1, v2)    \
   (_SHIFTL((v0) * 2, 16, 8) |              \
    _SHIFTL((v1) * 2,  8, 8) |              \
    _SHIFTL((v2) * 2,  0, 8))

#define __gsSP1Triangle_w1f(v0, v1, v2, flag)         \
   (((flag) == 0) ? __gsSP1Triangle_w1(v0, v1, v2) :    \
    ((flag) == 1) ? __gsSP1Triangle_w1(v1, v2, v0) :    \
                    __gsSP1Triangle_w1(v2, v0, v1))

#define __gsSP1Quadrangle_w1f(v0, v1, v2, v3, flag)   \
   (((flag) == 0) ? __gsSP1Triangle_w1(v0, v1, v2) :    \
    ((flag) == 1) ? __gsSP1Triangle_w1(v1, v2, v3) :    \
    ((flag) == 2) ? __gsSP1Triangle_w1(v2, v3, v0) :    \
                    __gsSP1Triangle_w1(v3, v0, v1))

#define __gsSP1Quadrangle_w2f(v0, v1, v2, v3, flag)   \
   (((flag) == 0) ? __gsSP1Triangle_w1(v0, v2, v3) :    \
    ((flag) == 1) ? __gsSP1Triangle_w1(v1, v3, v0) :    \
    ((flag) == 2) ? __gsSP1Triangle_w1(v2, v0, v1) :    \
                    __gsSP1Triangle_w1(v3, v1, v2))


/**
 * 1 Triangle
 */
#define gSP1Triangle(pkt, v0, v1, v2, flag)                 \
_DW({                                                       \
    Gfx *_g = (Gfx *)(pkt);                                 \
    _g->words.w0 = (_SHIFTL(G_TRI1, 24, 8) |                \
                    __gsSP1Triangle_w1f(v0, v1, v2, flag)); \
    _g->words.w1 = 0;                                       \
})
/**
 * @copydetails gSP1Triangle
 */
#define gsSP1Triangle(v0, v1, v2, flag)     \
{                                           \
   (_SHIFTL(G_TRI1, 24, 8) |                \
    __gsSP1Triangle_w1f(v0, v1, v2, flag)), \
    0                                       \
}

/**
 * 1 Quadrangle
 */
#define gSP1Quadrangle(pkt, v0, v1, v2, v3, flag)                   \
_DW({                                                               \
    Gfx *_g = (Gfx *)(pkt);                                         \
    _g->words.w0 = (_SHIFTL(G_QUAD, 24, 8) |                        \
                    __gsSP1Quadrangle_w1f(v0, v1, v2, v3, flag));   \
    _g->words.w1 = (__gsSP1Quadrangle_w2f(v0, v1, v2, v3, flag));   \
})

/**
 * @copydetails gSP1Quadrangle
 */
#define gsSP1Quadrangle(v0, v1, v2, v3, flag)       \
{                                                   \
   (_SHIFTL(G_QUAD, 24, 8) |                        \
    __gsSP1Quadrangle_w1f(v0, v1, v2, v3, flag)),   \
    __gsSP1Quadrangle_w2f(v0, v1, v2, v3, flag)     \
}

/**
 * 2 Triangles
 */
#define gSP2Triangles(pkt, v00, v01, v02, flag0, v10, v11, v12, flag1)  \
_DW({                                                                   \
    Gfx *_g = (Gfx *)(pkt);                                             \
    _g->words.w0 = (_SHIFTL(G_TRI2, 24, 8) |                            \
                    __gsSP1Triangle_w1f(v00, v01, v02, flag0));         \
    _g->words.w1 =  __gsSP1Triangle_w1f(v10, v11, v12, flag1);          \
})

/**
 * @copydetails gSP2Triangles
 */
#define gsSP2Triangles(v00, v01, v02, flag0, v10, v11, v12, flag1)  \
{                                                                   \
   (_SHIFTL(G_TRI2, 24, 8) |                                        \
    __gsSP1Triangle_w1f(v00, v01, v02, flag0)),                     \
    __gsSP1Triangle_w1f(v10, v11, v12, flag1)                       \
}

/*
 * 5 Triangles base commands
 */
#define _gSP5Triangles(pkt, cmd, v1, v2, v3, v4, v5, v6, v7) \
_DW({                                                        \
    Gfx *_g = (Gfx *)(pkt);                                  \
    _g->words.w0 = (_SHIFTL(cmd,    24, 8) |                 \
                    _SHIFTL((v1)*2, 16, 8) |                 \
                    _SHIFTL((v2)*2,  8, 8) |                 \
                    _SHIFTL((v3)*2,  0, 8));                 \
    _g->words.w1 = (_SHIFTL((v4)*2, 24, 8) |                 \
                    _SHIFTL((v5)*2, 16, 8) |                 \
                    _SHIFTL((v6)*2,  8, 8) |                 \
                    _SHIFTL((v7)*2,  0, 8));                 \
})
#define _gsSP5Triangles(cmd, v1, v2, v3, v4, v5, v6, v7)     \
{                                                            \
    (_SHIFTL(cmd,    24, 8) |                                \
     _SHIFTL((v1)*2, 16, 8) |                                \
     _SHIFTL((v2)*2,  8, 8) |                                \
     _SHIFTL((v3)*2,  0, 8)),                                \
    (_SHIFTL((v4)*2, 24, 8) |                                \
     _SHIFTL((v5)*2, 16, 8) |                                \
     _SHIFTL((v6)*2,  8, 8) |                                \
     _SHIFTL((v7)*2,  0, 8))                                 \
})
/**
 * 5 Triangles in strip arrangement. Draws the following tris:
 * v1-v2-v3, v3-v2-v4, v3-v4-v5, v5-v4-v6, v5-v6-v7
 * If you want to draw fewer tris, set indices to -1 from the right.
 * e.g. to draw 4 tris, set v7 to -1; to draw 3 tris, set v6 to -1
 * Note that any set of 3 adjacent tris can be drawn with either SPTriStrip
 * or SPTriFan. For arbitrary sets of 4 adjacent tris, four out of five of them
 * can be drawn with one of SPTriStrip or SPTriFan. The 4-triangle formation
 * which can't be drawn with either command looks like the Triforce.
 */
#define gSPTriStrip(pkt, v1, v2, v3, v4, v5, v6, v7) \
    _gSP5Triangles(pkt, G_TRISTRIP, v1, v2, v3, v4, v5, v6, v7)
/**
 * @copydetails gSPTriStrip
 */
#define gsSPTriStrip(v1, v2, v3, v4, v5, v6, v7) \
    _gsSP5Triangles(G_TRISTRIP, v1, v2, v3, v4, v5, v6, v7)
/**
 * 5 Triangles in fan arrangement. Draws the following tris:
 * v1-v2-v3, v1-v3-v4, v1-v4-v5, v1-v5-v6, v1-v6-v7
 * Otherwise works the same as SPTriStrip, see above.
 */
#define gSPTriFan(pkt, v1, v2, v3, v4, v5, v6, v7) \
    _gSP5Triangles(pkt, G_TRIFAN, v1, v2, v3, v4, v5, v6, v7)
/**
 * @copydetails gSPTriFan
 */
#define gsSPTriFan(v1, v2, v3, v4, v5, v6, v7) \
    _gsSP5Triangles(G_TRIFAN, v1, v2, v3, v4, v5, v6, v7)


/*
 * Moveword commands
 */
/* not strictly a moveword command anymore */
#define gSPSegment(pkt, segment, base)              \
    gDma1p((pkt), G_RELSEGMENT, (base), ((segment) * 4) & 0xFFF, G_MW_SEGMENT)
#define gsSPSegment(segment, base)                  \
    gsDma1p(      G_RELSEGMENT, (base), ((segment) * 4) & 0xFFF, G_MW_SEGMENT)

#define gSPPerspNormalize(pkt, s)   gMoveHalfwd(pkt, G_MW_FX, G_MWO_PERSPNORM, (s))
#define gsSPPerspNormalize(s)       gsMoveHalfwd(    G_MW_FX, G_MWO_PERSPNORM, (s))

/**
 * @brief Clipping Macros
 * @deprecated
 * encodes SP no-ops it is not possible to change the clip ratio from 2 in F3DEX3.
 */
#define gSPClipRatio(pkt, r) gSPNoOp(pkt)
/**
 * @brief @copybrief gSPClipRatio
 * @deprecated
 * @copydetails gSPClipRatio
 */
#define gsSPClipRatio(r) gsSPNoOp()

/**
 * @brief Load new MVP matrix directly.
 * 
 * This is no longer supported as there is no MVP matrix in F3DEX3.
 * @deprecated
 */
#define gSPForceMatrix(pkt, mptr) gSPNoOp(pkt)
/**
 * @brief Load new MVP matrix directly.
 * 
 * @copydetails gSPForceMatrix
 */
#define gsSPForceMatrix(mptr)    gsSPNoOp()

/**
 * Ambient occlusion
 * Enabled with the G_AMBOCCLUSION bit in geometry mode.
 * Each of these factors sets how much ambient occlusion affects lights of
 * the given type (ambient, directional, point). They are u16s.
 * You can set each independently or two adjacent values with one moveword.
 * A two-command macro is also provided to set all three values.
 * 
 * When building the model, you must encode the amount of ambient occlusion at
 * each vertex--effectively the shadow map for the model--in vertex alpha, where
 * 00 means darkest and FF means lightest. Then, the factors set with the
 * SPAmbOcclusion command determine how much the vertex alpha values affect the
 * light intensity. For example, if the ambient factor is set to 0x8000, this
 * means that in the darkest parts of the model, the ambient light intensity
 * will be reduced by 50%, and in the lightest parts of the model, the ambient
 * light intensity won't be reduced at all.
 * 
 * The default is:
 * amb = 0xFFFF (ambient light fully affected by vertex alpha)
 * dir = 0xA000 (directional lights 62% affected by vertex alpha)
 * point = 0    (point lights not at all affected by vertex alpha)
 * 
 * Two reasons to use ambient occlusion rather than darkening the vertex colors:
 * - With ambient occlusion, the geometry can be fully lit up with point and/or
 *   directional lights, depending on your settings here.
 * - Ambient occlusion can be used with cel shading to create areas which are
 *   "darker" for the cel shading thresholds, but still have bright / white
 *   vertex colors.
 * 
 * Two reasons to use these factors to modify ambient occlusion rather than
 * just manually scaling and offsetting all the vertex alpha values:
 * - To allow the behavior to differ between ambient, directional, and point
 *   lights
 * - To allow the lighting to be adjusted at the scene level on-the-fly
 */
#define gSPAmbOcclusionAmb(pkt, amb)     gMoveHalfwd(pkt, G_MW_FX, G_MWO_AO_AMBIENT, amb)
/**
 * @copydetails gSPAmbOcclusionAmb
 */
#define gsSPAmbOcclusionAmb(amb)        gsMoveHalfwd(     G_MW_FX, G_MWO_AO_AMBIENT, amb)
/**
 * @copydetails gSPAmbOcclusionAmb
 */
#define gSPAmbOcclusionDir(pkt, dir)     gMoveHalfwd(pkt, G_MW_FX, G_MWO_AO_DIRECTIONAL, dir)
/**
 * @copydetails gSPAmbOcclusionAmb
 */
#define gsSPAmbOcclusionDir(dir)        gsMoveHalfwd(     G_MW_FX, G_MWO_AO_DIRECTIONAL, dir)
/**
 * @copydetails gSPAmbOcclusionAmb
 */
#define gSPAmbOcclusionPoint(pkt, point) gMoveHalfwd(pkt, G_MW_FX, G_MWO_AO_POINT, point)
/**
 * @copydetails gSPAmbOcclusionAmb
 */
#define gsSPAmbOcclusionPoint(point)    gsMoveHalfwd(     G_MW_FX, G_MWO_AO_POINT, point)

#define gSPAmbOcclusionAmbDir(pkt, amb, dir) \
    gMoveWd(pkt, G_MW_FX, G_MWO_AO_AMBIENT,  \
        (_SHIFTL((amb), 16, 16) | _SHIFTL((dir), 0, 16)))
#define gsSPAmbOcclusionAmbDir(amb, dir)     \
    gsMoveWd(G_MW_FX, G_MWO_AO_AMBIENT,      \
        (_SHIFTL((amb), 16, 16) | _SHIFTL((dir), 0, 16)))
#define gSPAmbOcclusionDirPoint(pkt, dir, point) \
    gMoveWd(pkt, G_MW_FX, G_MWO_AO_DIRECTIONAL,  \
        (_SHIFTL((dir), 16, 16) | _SHIFTL((point), 0, 16)))
#define gsSPAmbOcclusionDirPoint(dir, point)     \
    gsMoveWd(G_MW_FX, G_MWO_AO_DIRECTIONAL,      \
        (_SHIFTL((dir), 16, 16) | _SHIFTL((point), 0, 16)))

#define gSPAmbOcclusion(pkt, amb, dir, point) \
_DW({                                         \
    gSPAmbOcclusionAmbDir(pkt, amb, dir);     \
    gSPAmbOcclusionPoint(pkt, point);         \
})
#define gsSPAmbOcclusion(amb, dir, point)     \
    gsSPAmbOcclusionAmbDir(amb, dir),         \
    gsSPAmbOcclusionPoint(point)

/**
 * Fresnel - Feature suggested by thecozies
 * Enabled with the G_FRESNEL bit in geometry mode.
 * The dot product between a vertex normal and the vector from the vertex to the
 * camera is computed. The offset and scale here convert this to a shade alpha
 * value. This is useful for making surfaces fade between transparent when
 * viewed straight-on and opaque when viewed at a large angle, or for applying a
 * fake "outline" around the border of meshes.
 * 
 * If using Fresnel, you need to set the camera world position whenever you set
 * the VP matrix, viewport, etc. See SPCameraWorld.
 * 
 * The RSP does:
 * s16 dotProduct = dot(vertex normal, camera pos - vertex pos);
 * dotProduct = abs(dotProduct); // 0 = points to side, 7FFF = points at or away
 * s32 factor = ((scale * dotProduct) >> 15) + offset;
 * s16 result = clamp(factor << 8, 0, 7FFF);
 * color_or_alpha = result >> 7;
 * 
 * At dotMax, color_or_alpha = FF, result = 7F80, factor = 7F
 * At dotMin, color_or_alpha = 00, result = 0, factor = 0
 * 7F = ((scale * dotMax) >> 15) + offset
 * 00 = ((scale * dotMin) >> 15) + offset
 * Subtract: 7F = (scale * (dotMax - dotMin)) >> 15
 *           3F8000 = scale * (dotMax - dotMin)
 *           scale = 3F8000 / (dotMax - dotMin)                <--
 * offset = -(((3F8000 / (dotMax - dotMin)) * dotMin) >> 15)
 * offset = -((7F * dotMin) / (dotMax - dotMin))               <--
 * 
 * To convert in the opposite direction:
 * ((7F - offset) << 15) / scale = dotMax
 * ((00 - offset) << 15) / scale = dotMin
 */
#define gSPFresnelScale(pkt, scale) \
    gMoveHalfwd(pkt, G_MW_FX, G_MWO_FRESNEL_SCALE, scale)
/**
 * @copydetails gSPFresnelScale
 */
#define gsSPFresnelScale(scale) \
    gsMoveHalfwd(G_MW_FX, G_MWO_FRESNEL_SCALE, scale)
/**
 * @copydetails gSPFresnelScale
 */
#define gSPFresnelOffset(pkt, offset) \
    gMoveHalfwd(pkt, G_MW_FX, G_MWO_FRESNEL_OFFSET, offset)
/**
 * @copydetails gSPFresnelScale
 */
#define gsSPFresnelOffset(offset) \
    gsMoveHalfwd(G_MW_FX, G_MWO_FRESNEL_OFFSET, offset)
/**
 * @copydetails gSPFresnelScale
 */
#define gSPFresnel(pkt, scale, offset) \
    gMoveWd(pkt, G_MW_FX, G_MWO_FRESNEL_SCALE, \
        (_SHIFTL((scale), 16, 16) | _SHIFTL((offset), 0, 16)))
/**
 * @copydetails gSPFresnelScale
 */
#define gsSPFresnel(scale, offset) \
    gsMoveWd(G_MW_FX, G_MWO_FRESNEL_SCALE, \
        (_SHIFTL((scale), 16, 16) | _SHIFTL((offset), 0, 16)))

/**
 * Attribute offsets
 * These are added to ST or Z values after vertices are loaded and transformed.
 * They are all s16s.
 * For ST, the addition is after the multiplication for ST scale in SPTexture.
 * For Z, this simply adds to the Z offset from the viewport.
 * Whether each feature is enabled or disabled at a given time is determined
 * by the G_ATTROFFSET_ST_ENABLE and G_ATTROFFSET_Z_ENABLE bits respectively in
 * the geometry mode.
 * Normally you would use ST offsets for UV scrolling, and you would use a Z
 * offset of -2 (which it is set to by default) to fix decal mode. For the
 * latter, enable the Z offset and set the Z mode to opaque.
 */
#define gSPAttrOffsetST(pkt, s, t) \
    gMoveWd(pkt, G_MW_FX, G_MWO_ATTR_OFFSET_S, \
        (_SHIFTL((s), 16, 16) | _SHIFTL((t), 0, 16)))
/**
 * @copydetails gSPAttrOffsetST
 */
#define gsSPAttrOffsetST(s, t) \
    gsMoveWd(G_MW_FX, G_MWO_ATTR_OFFSET_S, \
        (_SHIFTL((s), 16, 16) | _SHIFTL((t), 0, 16)))
/**
 * @copydetails gSPAttrOffsetST
 */
#define gSPAttrOffsetZ(pkt, z) \
    gMoveHalfwd(pkt, G_MW_FX, G_MWO_ATTR_OFFSET_Z, z)
/**
 * @copydetails gSPAttrOffsetST
 */
#define gsSPAttrOffsetZ(z) \
    gsMoveHalfwd(G_MW_FX, G_MWO_ATTR_OFFSET_Z, z)
    
/**
 * Alpha compare culling. Optimization for cel shading, could also be used for
 * other scenarios where lots of tris are being drawn with alpha compare.
 * 
 * If mode == G_ALPHA_COMPARE_CULL_DISABLE, tris are drawn normally.
 * 
 * Otherwise:
 * - "vertex alpha" means the post-transform alpha value at each vertex being
 *   sent to the RDP. This may be the original model vertex alpha, fog, light
 *   level (for cel shading), or Fresnel.
 * - Assuming a cel shading context: you have a threshold value thresh, you draw
 *   tris once and want to write all pixels where shade alpha >= thresh. Then
 *   you change color settings and draw tris again, and want to write all other
 *   pixels, i.e. where shade alpha < thresh.
 * 
 * For the light pass:
 * - Set blend color alpha to thresh
 * - Set CC alpha cycle 1 (or only cycle) to (shade alpha - 0) * tex alpha + 0
 * - The RDP will draw pixels whenever shade alpha >= thresh (with binary alpha
 *   from the texture)
 * - Set mode = G_ALPHA_COMPARE_CULL_BELOW in SPAlphaCompareCull, and thresh
 * - The RSP will cull any tris where all three vertex alpha values (i.e. light
 *   level) are < thresh
 * 
 * For the dark pass:
 * - Set blend color alpha to 0x100 - thresh (yes, not 0xFF - thresh).
 * - Set CC alpha cycle 1 (or only cycle) to (1 - shade alpha) * tex alpha + 0
 * - The RDP will draw pixels whenever shade alpha < thresh (with binary alpha
 *   from the texture)
 * - Set mode = G_ALPHA_COMPARE_CULL_ABOVE in SPAlphaCompareCull, and thresh
 * - The RSP will cull any tris where all three vertex alpha values (i.e. light
 *   level) are >= thresh
 * 
 * The idea is to cull tris early on the RSP which won't have any of their
 * fragments drawn on the RDP, to save RDP time and memory bandwidth.
 */
#define gSPAlphaCompareCull(pkt, mode, thresh) \
    gMoveHalfwd(pkt, G_MW_FX, G_MWO_ALPHA_COMPARE_CULL, \
        (_SHIFTL((mode), 8, 8) | _SHIFTL((thresh), 0, 8)))
/**
 * @copydetails gSPAlphaCompareCull
 */
#define gsSPAlphaCompareCull(mode, thresh) \
    gsMoveHalfwd(G_MW_FX, G_MWO_ALPHA_COMPARE_CULL, \
        (_SHIFTL((mode), 8, 8) | _SHIFTL((thresh), 0, 8)))

/**
 * Normals mode: How to handle transformation of vertex normals from model to
 * world space for lighting.
 * 
 * If mode = G_NORMALS_MODE_FAST, transforms normals from model space to world
 * space with the M matrix. This is correct if the object's transformation
 * matrix stack only included translations, rotations, and uniform scale (i.e.
 * same scale in X, Y, and Z); otherwise, if the transformation matrix has
 * nonuniform scale or shear, the lighting on the object will be somewhat
 * distorted.
 * 
 * If mode = G_NORMALS_MODE_AUTO, transforms normals from model space to world
 * space with M inverse transpose, which renders lighting correctly for the
 * object regardless of its transformation matrix (nonuniform scale or shear is
 * okay). Whenever vertices are drawn with lighting enabled after M has been
 * changed, computes M inverse transpose from M. This requires swapping to
 * overlay 4 for M inverse transpose and then back to overlay 2 for lighting,
 * which produces roughly 3.5 us of extra DRAM traffic. This performance penalty
 * happens effectively once per matrix, which is once per normal object or
 * separated limb or about twice per flex skeleton limb. So in a scene with lots
 * of complex skeletons, this may have a noticeable performance impact.
 * 
 * If mode = G_NORMALS_MODE_MANUAL, uses M inverse transpose for correct results
 * like G_NORMALS_MODE_AUTO, but it never internally computes M inverse
 * transpose. You have to upload M inverse transpose to the RSP using
 * SPMITMatrix every time you change the M matrix. The DRAM traffic for the
 * extra matrix uploads is much smaller than the overlay swaps, so if you can
 * efficiently compute M inverse transpose on the CPU, this may be faster than
 * G_NORMALS_MODE_AUTO.
 * 
 * Recommended to leave this set to G_NORMALS_MODE_FAST generally, and only set
 * it to G_NORMALS_MODE_AUTO for specific objects at times when they actually
 * have a nonuniform scale. For example, G_NORMALS_MODE_FAST for Mario
 * generally, but G_NORMALS_MODE_AUTO temporarily while he is squashed.
 */
#define gSPNormalsMode(pkt, mode) \
    gMoveHalfwd(pkt, G_MW_FX, G_MWO_NORMALS_MODE, (mode) & 0xFF)
/**
 * @copydetails gSPNormalsMode
 */
#define gsSPNormalsMode(mode) \
    gsMoveHalfwd(G_MW_FX, G_MWO_NORMALS_MODE, (mode) & 0xFF)

/**
 * F3DEX3 has a basic auto-batched rendering system. At a high level, if a
 * material display list being run is the same as the last material, the texture
 * loads are automatically skipped the second time as they should already be in
 * TMEM.
 * 
 * This design generally works, but can break if you call a display list twice
 * but in between change a segment mapping so that a referenced image inside is
 * actually different the two times. In these cases, run the below command
 * between the two calls (e.g. when you change the segment) and the microcode
 * will not skip the second texture loads.
 * 
 * Internally, a material is defined to start with any set image command, and
 * end on any of the following: call, branch, return, vertex, all tri commands,
 * modify vertex, branch Z/W, or cull. The physical address of the display list
 * --not the address of the image--is stored when a material is started. If a
 * material starts and its physical address is the same as the stored last start
 * address, i.e. we're executing the same material display list as the last
 * material, material cull mode is set. In this mode, load block, load tile, and
 * load TLUT all are skipped. This mode is cleared when the material ends.
 * 
 * This design has the benefit that it works correctly even with complex
 * materials, e.g. with two CI4 textures (four loads), whereas it would be
 * difficult to implement tracking all these loads separately. Furthermore, a
 * design based on tracking the image addresses could break if you loaded
 * different tile sections of the same image in consecutive materials.
 */
#define gSPDontSkipTexLoadsAcross(pkt) \
    gMoveWd(pkt, G_MW_FX, G_MWO_LAST_MAT_DL_ADDR, 0xFFFFFFFF)
/**
 * @copydetails gSPDontSkipTexLoadsAcross
 */
#define gsSPDontSkipTexLoadsAcross() \
    gsMoveWd(G_MW_FX, G_MWO_LAST_MAT_DL_ADDR, 0xFFFFFFFF)

typedef union {
    struct {
        s16 intPart[3][4];  /** Fourth row containing translations is omitted. */
        u16 fracPart[3][4]; /** Also the fourth column data is ignored, need not be 0. */
    };
    long long int force_structure_alignment;
} MITMtx;

/**
 * See SPNormalsMode. mtx is the address of a MITMtx (M inverse transpose).
 * 
 * The matrix values must be scaled down so that the matrix norm is <= 1,
 * i.e. multiplying this matrix by any vector length <= 1 must produce a vector
 * with length <= 1. Normally, M scales things down substantially, so M inverse
 * transpose natively would scale them up substantially; you need to apply a
 * constant scale to counteract this. One easy way to do this is compute M
 * inverse transpose normally, then scale it so until the maximum absolute
 * value of any element is 0.5. Because of this scaling, you can also skip the
 * part of the inverse computation where you compute the determinant and divide
 * by it, cause you're going to rescale it arbitrarily anyway.
 */
#define gSPMITMatrix(pkt, mit) \
        gDma2p((pkt), G_MOVEMEM, (mit), sizeof(MITMtx), G_MV_MMTX, 0x80)
/**
 * @copydetails gSPMITMatrix
 */
#define gsSPMITMatrix(mtx) \
        gsDma2p(      G_MOVEMEM, (mit), sizeof(MITMtx), G_MV_MMTX, 0x80)


/**
 * @brief You can use this macro to modify certain sections of a vertex after it has been sent to the RSP (by the gSPVertex macro).
 * 
 * This is an advanced macro. You need a good understanding of how vertices work in the RSP microcode before you use this macro (refer to gSPVertex).
 * 
 * You can use this macro to modify certain sections of a vertex after it has been sent to the RSP (by the gSPVertex macro). This is useful for vertices that are shared between two or more triangles that must have different properties when associated with one triangle versus the other triangle.
 * 
 * For example, you might have two adjacent triangles that both need smooth-shaded color, but one is smooth-shaded red-to-yellow and the other is smooth-shaded green-to-cyan. In this case, the vertex that is shared by both triangles is sent with red/yellow color by using the gSPVertex macro. The first triangle is drawn. Then, the gSPModifyVertex macro is used to change the color to green/cyan, and the second triangle is drawn.

 * The primary use of the gSPModifyVertex macro is to modify the texture coordinate of a vertex so that a vertex that is shared by two triangles with different textures and different texture coordinate spaces can contain the texture coordinate for the first texture and then be modified to contain the texture coordinate for the second texture.
 * 
 * It is faster to use the gSPModifyVertex macro than to send a new vertex macro with a different but similar vertex because no transformations or lighting are done to the vertex when you use the gSPModifyVertex macro.
 * 
 * The where argument specifies which part of the vertex is to be modified. It can hold one of the following values:
 * - @ref G_MWO_POINT_RGBA - @copybrief G_MWO_POINT_RGBA
 * - @ref G_MWO_POINT_ST - @copybrief G_MWO_POINT_ST
 * - @ref G_MWO_POINT_XYSCREEN - @copybrief G_MWO_POINT_XYSCREEN
 * - @ref G_MWO_POINT_ZSCREEN - @copybrief G_MWO_POINT_ZSCREEN
 * 
 * @note
 * Lighting is not performed after a gSPModifyVertex macro, so modifying the color of the vertex with @ref G_MWO_POINT_RGBA is just that - modifying the actual color that will be output. It is not a modification of normal values. This means it cannot be used to update vertex normals for lighting.
 * 
 * The S and T coordinates supplied in the gSPModifyVertex macro are never multiplied by the texture scale (from the gSPTexture macro), so you must pre-scale them before sending them. For example, if you want a texture scale of 1/2 (0x8000), make the S and T values sent with the gSPModifyVertex macro half the value of the equivalent values used with the gSPVertex macro.
 * 
 * # Example
 * To share a vertex between two triangles with different textures and texture coordinates, use this code:
 * ```c
 * // load vertex by gSPVertex
 * gSPVertex(...);
 * // load texture of triangle 1
 * gDPLoadTextureBlock(...);
 * 
 * // draw triangle 1 using vertex #3
 * gSP1Triangle(glistp++, 1,2,3,0);
 * 
 * // change a value of vertex 3 to S=3.0 and T=2.5
 * gSPModifyVertex(glistp++, 3, G_MWO_POINT_ST, 0x00600050);
 * 
 * // load texture of triangle 2
 * gDPLoadTextureBlock(...);
 * 
 * // draw triangle 2 using vertex #3
 * gSP1Triangle(glistp++, 1,2,3,0);
 * ```
 * 
 * @param vtx specifies which of the RSP's vertices (0-55) to modify
 * @param where specifies which part of the vertex to modify (@ref G_MWO_POINT_RGBA, @ref G_MWO_POINT_ST, @ref G_MWO_POINT_XYSCREEN or @ref G_MWO_POINT_ZSCREEN)
 * @param val is the new value for the part of the vertex to be modified (a 32 bit integer number)
 */
# define gSPModifyVertex(pkt, vtx, where, val)      \
_DW({                                               \
    Gfx *_g = (Gfx *)(pkt);                         \
                                                    \
    _g->words.w0 = (_SHIFTL(G_MODIFYVTX, 24,  8) |  \
                    _SHIFTL((where),     16,  8) |  \
                    _SHIFTL((vtx) * 2,    0, 16));  \
    _g->words.w1 = (unsigned int)(val);             \
})
/**
 * @brief You can use this macro to modify certain sections of a vertex after it has been sent to the RSP (by the gSPVertex macro).
 * 
 * @copydetails gSPModifyVertex
 */
# define gsSPModifyVertex(vtx, where, val)  \
{                                           \
   (_SHIFTL(G_MODIFYVTX, 24,  8) |          \
    _SHIFTL((where),     16,  8) |          \
    _SHIFTL((vtx) * 2,    0, 16)),          \
    (unsigned int)(val)                     \
}

/*
 * Display list optimization / object culling
 */

/**
 * Cull the display list based on screen clip flags of range of loaded verts.
 * Executes SPEndDisplayList if the convex hull formed by the specified range of
 * already-loaded vertices is offscreen.
 */
#define gSPCullDisplayList(pkt,vstart,vend)             \
_DW({                                                   \
    Gfx *_g = (Gfx *)(pkt);                             \
                                                        \
    _g->words.w0 = (_SHIFTL(G_CULLDL,     24, 8) |      \
                    _SHIFTL((vstart) * 2,  0, 16));     \
    _g->words.w1 = _SHIFTL((vend) * 2, 0, 16);          \
})
/**
 * @copydetails gSPCullDisplayList
 */
#define gsSPCullDisplayList(vstart,vend)    \
{                                           \
   (_SHIFTL(G_CULLDL,     24, 8) |          \
    _SHIFTL((vstart) * 2,  0, 16)),         \
    _SHIFTL((vend) * 2, 0, 16)              \
}

/*
 * gSPBranchLessZ   Branch DL if (vtx.z) less than or equal (zval).
 * Note that this uses W in F3DZEX / CFG_G_BRANCH_W, in which case all the
 * Z calculations below are wrong and raw values must be used.
 *
 *  dl   = DL branch to
 *  vtx  = Vertex
 *  zval = Screen depth
 *  near = Near plane
 *  far  = Far  plane
 *  flag = G_BZ_PERSP or G_BZ_ORTHO
 */

/* From gu.h */
#ifndef FTOFIX32
# define FTOFIX32(x) (long)((x) * (float)0x00010000)
#endif

#define G_BZ_PERSP  0
#define G_BZ_ORTHO  1

#define G_DEPTOZSrg(zval, near, far, flag, zmin, zmax)          \
    (((unsigned int)FTOFIX32(((flag) == G_BZ_PERSP ?            \
                  (1.0f - (float)(near) / (float)(zval)) /      \
                  (1.0f - (float)(near) / (float)(far )) :      \
                  ((float)(zval) - (float)(near)) /             \
                  ((float)(far ) - (float)(near))))) *          \
     (((int)((zmax) - (zmin))) & ~1) + (int)FTOFIX32(zmin))

#define G_DEPTOZS(zval, near, far, flag) \
    G_DEPTOZSrg(zval, near, far, flag, 0, G_MAXZ)

#define gSPBranchLessZrg(pkt, dl, vtx, zval, near, far, flag, zmin, zmax)   \
_DW({                                                                       \
    Gfx *_g = (Gfx *)(pkt);                                                 \
                                                                            \
    _g->words.w0 = _SHIFTL(G_RDPHALF_1, 24, 8);                             \
    _g->words.w1 = (unsigned int)(dl);                                      \
                                                                            \
    _g = (Gfx *)(pkt);                                                      \
                                                                            \
    _g->words.w0 = (_SHIFTL(G_BRANCH_Z, 24,  8) |                           \
                    _SHIFTL((vtx) * 5,  12, 12) |                           \
                    _SHIFTL((vtx) * 2,   0, 12));                           \
    _g->words.w1 = G_DEPTOZSrg(zval, near, far, flag, zmin, zmax);          \
})

#define gsSPBranchLessZrg(dl, vtx, zval, near, far, flag, zmin, zmax)   \
{                                                                       \
    _SHIFTL(G_RDPHALF_1, 24, 8),                                        \
    (unsigned int)(dl),                                                 \
},                                                                      \
{                                                                       \
   (_SHIFTL(G_BRANCH_Z, 24, 8) |                                        \
    _SHIFTL((vtx) * 5, 12, 12) |                                        \
    _SHIFTL((vtx) * 2, 0, 12)),                                         \
    G_DEPTOZSrg(zval, near, far, flag, zmin, zmax),                     \
}

#define gSPBranchLessZ(pkt, dl, vtx, zval, near, far, flag)         \
    gSPBranchLessZrg(pkt, dl, vtx, zval, near, far, flag, 0, G_MAXZ)
#define gsSPBranchLessZ(dl, vtx, zval, near, far, flag)             \
    gsSPBranchLessZrg(dl, vtx, zval, near, far, flag, 0, G_MAXZ)

/**
 *  gSPBranchLessZraw   Branch DL if (vtx.z) less than or equal (raw zval).
 *
 *  dl   = DL branch to
 *  vtx  = Vertex
 *  zval = Raw value of screen depth
 */
#define gSPBranchLessZraw(pkt, dl, vtx, zval)       \
_DW({                                               \
    Gfx *_g = (Gfx *)(pkt);                         \
                                                    \
    _g->words.w0 = _SHIFTL(G_RDPHALF_1, 24, 8);     \
    _g->words.w1 = (unsigned int)(dl);              \
                                                    \
    _g = (Gfx *)(pkt);                              \
                                                    \
    _g->words.w0 = (_SHIFTL(G_BRANCH_Z, 24,  8) |   \
                    _SHIFTL((vtx) * 5,  12, 12) |   \
                    _SHIFTL((vtx) * 2,   0, 12));   \
    _g->words.w1 = (unsigned int)(zval);            \
})

/**
 * @copydetails gSPBranchLessZraw
 */
#define gsSPBranchLessZraw(dl, vtx, zval)   \
{                                           \
    _SHIFTL(G_RDPHALF_1, 24, 8),            \
    (unsigned int)(dl),                     \
},                                          \
{                                           \
   (_SHIFTL(G_BRANCH_Z, 24,  8) |           \
    _SHIFTL((vtx) * 5,  12, 12) |           \
    _SHIFTL((vtx) * 2,   0, 12)),           \
    (unsigned int)(zval),                   \
}


/*
 * Lighting Commands
 */

#define NUML(n)    ((n) * 0x10)
/*
 * F3DEX3 properly supports zero lights, so there is no need to use these macros
 * anymore.
 */
#define NUMLIGHTS_0 0
#define NUMLIGHTS_1 1
#define NUMLIGHTS_2 2
#define NUMLIGHTS_3 3
#define NUMLIGHTS_4 4
#define NUMLIGHTS_5 5
#define NUMLIGHTS_6 6
#define NUMLIGHTS_7 7
#define NUMLIGHTS_8 8
#define NUMLIGHTS_9 9

/**
 * Number of directional / point lights, in the range 0-9. There is also always
 * one ambient light not counted in this number.
 */
#define gSPNumLights(pkt, n)                            \
    gMoveWd(pkt, G_MW_NUMLIGHT, G_MWO_NUMLIGHT, NUML(n))
/**
 * @copydetails gSPNumLights
 */
#define gsSPNumLights(n)                                \
    gsMoveWd(    G_MW_NUMLIGHT, G_MWO_NUMLIGHT, NUML(n))

/* There is also no need to use these macros. */
#define LIGHT_1     1
#define LIGHT_2     2
#define LIGHT_3     3
#define LIGHT_4     4
#define LIGHT_5     5
#define LIGHT_6     6
#define LIGHT_7     7
#define LIGHT_8     8
#define LIGHT_9     9
#define LIGHT_10    10

#define _LIGHT_TO_OFFSET(n) (((n) - 1) * 0x10 + 0x10) /* The + 0x10 skips cam pos and lookat */

/**
 * l should point to a Light struct.
 * n should be an integer 1-9 to load lights 0-8.
 * Can also load Ambient lights to lights 0-8 with this. However, if you have
 * 9 directional / point lights, you must use SPAmbient to load light 9
 * (LIGHT_10) with an ambient light. (That is, the memory for light 9 (LIGHT_10)
 * is only sizeof(Ambient), so if you load this with SPLight, it will overwrite
 * other DMEM and corrupt unrelated things.)
 * New code should not generally use SPLight, and instead use SPSetLights to set
 * all lights in one memory transaction.
 */
#define gSPLight(pkt, l, n) \
    gDma2p((pkt), G_MOVEMEM, (l), sizeof(Light), G_MV_LIGHT, _LIGHT_TO_OFFSET(n))
/**
 * @copydetails gSPLight
 */
#define gsSPLight(l, n) \
    gsDma2p(      G_MOVEMEM, (l), sizeof(Light), G_MV_LIGHT, _LIGHT_TO_OFFSET(n))

/**
 * l should point to an Ambient struct.
 * n should be an integer 1-10 to load lights 0-9.
 */
#define gSPAmbient(pkt, l, n) \
    gDma2p((pkt), G_MOVEMEM, (l), sizeof(Ambient), G_MV_LIGHT, _LIGHT_TO_OFFSET(n))
/**
 * @copydetails gSPAmbient
 */
#define gsSPAmbient(l, n) \
    gsDma2p(      G_MOVEMEM, (l), sizeof(Ambient), G_MV_LIGHT, _LIGHT_TO_OFFSET(n))

/**
 * gSPLightColor changes the color of a directional light without an additional
 * DMA transfer.
 * col is a 32 bit word where (col >> 24) & 0xFF is red, (col >> 16) & 0xFF is
 * green, and (col >> 8) & 0xFF is blue. (col & 0xFF) is ignored and masked to
 * zero.
 * n should be an integer 1-10 to apply to light 0-9.
 */
#define gSPLightColor(pkt, n, col)                  \
_DW({                                               \
    gMoveWd(pkt, G_MW_LIGHTCOL, ((((n) - 1) * 0x10) + 0), ((col) & 0xFFFFFF00));   \
    gMoveWd(pkt, G_MW_LIGHTCOL, ((((n) - 1) * 0x10) + 4), ((col) & 0xFFFFFF00));   \
})
/**
 * @copydetails gSPLightColor
 */
#define gsSPLightColor(n, col)                      \
    gsMoveWd(G_MW_LIGHTCOL, ((((n) - 1) * 0x10) + 0), ((col) & 0xFFFFFF00)),       \
    gsMoveWd(G_MW_LIGHTCOL, ((((n) - 1) * 0x10) + 4), ((col) & 0xFFFFFF00))
/*
 * Version for point lights. (col1 & 0xFF) must be set to the point light constant
 * factor (must be nonzero), and (col2 & 0xFF) must be set to the point light
 * linear factor.
 * n should be an integer 1-10 to apply to light 0-9.
 */
#define _gSPLightColor2(pkt, n, col1, col2) \
_DW({\
  gMoveWd(pkt, G_MW_LIGHTCOL, ((((n) - 1) * 0x10) + 0), col1); \
  gMoveWd(pkt, G_MW_LIGHTCOL, ((((n) - 1) * 0x10) + 4), col2); \
})
#define _gsSPLightColor2(n, col1, col2) \
  gsMoveWd(G_MW_LIGHTCOL, ((((n) - 1) * 0x10) + 0), col1), \
  gsMoveWd(G_MW_LIGHTCOL, ((((n) - 1) * 0x10) + 4), col2)


/**
 * Set all your scene's lights (directional/point + ambient) with one memory
 * transaction.
 * n is the number of directional / point lights, from 0 to 9. There is also
 * always an ambient light.
 * name should be the NAME of a Lights struct (NOT A POINTER)
 * filled in with all the lighting data. You can use the gdSPDef* macros to fill
 * in the struct or just do it manually. Example:
 * Lights2 myLights; // 2 dir/pos + 1 ambient
 * <code to fill in the fields of myLights>
 * gSPSetLights(POLY_OPA_DISP++, 2, myLights);
 * 
 * If you need to use a pointer, e.g. if the number of lights is variable at
 * runtime:
 * Light *lights = memory_allocate((numLights + 1) * sizeof(Light));
 * lights[0].p.pos = ...;
 * lights[1].l.dir = ...;
 * ...
 * lights[numLights].l.col = ambient_color();
 * gSPSetLights(POLY_OPA_DISP++, numLights, *lights); // <- NOTE DEREFERENCE
 * 
 * If you're wondering why this macro takes a name / dereference instead of a
 * pointer, it's for backwards compatibility.
 */
#define gSPSetLights(pkt, n, name) \
_DW({ \
    gSPNumLights(pkt, n); \
    gDma2p((pkt),  G_MOVEMEM, &(name), (n) * 0x10 + 8, G_MV_LIGHT, 0x10); \
})
/**
 * @copydetails gSPSetLights
 */
#define gsSPSetLights(n, name) \
    gsSPNumLights(n), \
    gsDma2p(G_MOVEMEM, &(name), (n) * 0x10 + 8, G_MV_LIGHT, 0x10)

#define  gSPSetLights0(pkt, name)  gSPSetLights(pkt, 0, name)
#define gsSPSetLights0(name)      gsSPSetLights(     0, name)
#define  gSPSetLights1(pkt, name)  gSPSetLights(pkt, 1, name)
#define gsSPSetLights1(name)      gsSPSetLights(     1, name)
#define  gSPSetLights2(pkt, name)  gSPSetLights(pkt, 2, name)
#define gsSPSetLights2(name)      gsSPSetLights(     2, name)
#define  gSPSetLights3(pkt, name)  gSPSetLights(pkt, 3, name)
#define gsSPSetLights3(name)      gsSPSetLights(     3, name)
#define  gSPSetLights4(pkt, name)  gSPSetLights(pkt, 4, name)
#define gsSPSetLights4(name)      gsSPSetLights(     4, name)
#define  gSPSetLights5(pkt, name)  gSPSetLights(pkt, 5, name)
#define gsSPSetLights5(name)      gsSPSetLights(     5, name)
#define  gSPSetLights6(pkt, name)  gSPSetLights(pkt, 6, name)
#define gsSPSetLights6(name)      gsSPSetLights(     6, name)
#define  gSPSetLights7(pkt, name)  gSPSetLights(pkt, 7, name)
#define gsSPSetLights7(name)      gsSPSetLights(     7, name)
#define  gSPSetLights8(pkt, name)  gSPSetLights(pkt, 8, name)
#define gsSPSetLights8(name)      gsSPSetLights(     8, name)
#define  gSPSetLights9(pkt, name)  gSPSetLights(pkt, 9, name)
#define gsSPSetLights9(name)      gsSPSetLights(     9, name)


/**
 * Camera world position for Fresnel and specular lighting. Set this whenever
 * you set the VP matrix, viewport, etc. cam is the address of a PlainVtx struct.
 */
#define gSPCameraWorld(pkt, cam) \
    gDma2p((pkt), G_MOVEMEM, (cam), sizeof(PlainVtx), G_MV_LIGHT, 0)
/**
 * @copydetails gSPCameraWorld
 */
#define gsSPCameraWorld(cam) \
    gsDma2p(      G_MOVEMEM, (cam), sizeof(PlainVtx), G_MV_LIGHT, 0)


/**
 * Reflection/Hiliting Macros.
 * la is the address of a LookAt struct.
 */
#define gSPLookAt(pkt, la) \
    gDma2p((pkt), G_MOVEMEM, (la), sizeof(LookAt), G_MV_LIGHT, 8)
/**
 * @copydetails gSPLookAt
 */
#define gsSPLookAt(la) \
    gsDma2p(      G_MOVEMEM, (la), sizeof(LookAt), G_MV_LIGHT, 8)
 
/**
 * These versions are deprecated, please use g*SPLookAt. The two directions
 * cannot be set independently anymore as they both fit within one memory word.
 * (They could be set with moveword, but then the values would have to be within
 * the command itself, not at a memory address.)
 * This deprecated version has the X command set both (assuming l is the name /
 * address of a LookAt struct) and has the Y command as a SP no-op.
 * @deprecated
 */
#define gSPLookAtX(pkt, l) gSPLookAt(pkt, l)
/**
 * @copydetails gSPLookAtX
 */
#define gsSPLookAtX(l)     gsSPLookAt(l)
/**
 * @copydetails gSPLookAtX
 */
#define gSPLookAtY(pkt, l) gSPNoOp(pkt)
/**
 * @copydetails gSPLookAtX
 */
#define gsSPLookAtY(l)     gsSPNoOp()


#define gDPSetHilite1Tile(pkt, tile, hilite, width, height) \
    gDPSetTileSize(pkt, tile,                               \
        (hilite)->h.x1 & 0xFFF,                             \
        (hilite)->h.y1 & 0xFFF,                             \
        ((((width)  - 1) * 4) + (hilite)->h.x1) & 0xFFF,    \
        ((((height) - 1) * 4) + (hilite)->h.y1) & 0xFFF)
#define gsDPSetHilite1Tile(tile, hilite, width, height)     \
    gsDPSetTileSize(tile,                                   \
        (hilite)->h.x1 & 0xFFF,                             \
        (hilite)->h.y1 & 0xFFF,                             \
        ((((width)  - 1) * 4) + (hilite)->h.x1) & 0xFFF,    \
        ((((height) - 1) * 4) + (hilite)->h.y1) & 0xFFF)

#define gDPSetHilite2Tile(pkt, tile, hilite, width, height) \
    gDPSetTileSize(pkt, tile,                               \
        (hilite)->h.x2 & 0xFFF,                             \
        (hilite)->h.y2 & 0xFFF,                             \
        ((((width)  - 1) * 4) + (hilite)->h.x2) & 0xFFF,    \
        ((((height) - 1) * 4) + (hilite)->h.y2) & 0xFFF)
#define gsDPSetHilite2Tile(tile, hilite, width, height)     \
    gsDPSetTileSize(tile,                                   \
        (hilite)->h.x2 & 0xFFF,                             \
        (hilite)->h.y2 & 0xFFF,                             \
        ((((width)  - 1) * 4) + (hilite)->h.x2) & 0xFFF,    \
        ((((height) - 1) * 4) + (hilite)->h.y2) & 0xFFF)


/**
 * Set the occlusion plane. This is a quadrilateral in 3D space where all
 * geometry behind it is culled. You should create occlusion plane candidates
 * just behind walls and other large objects, and have your game engine pick
 * the most optimal one every frame to send to the RSP.
 * 
 * Computing the coefficients for the occlusion plane is far too complicated to
 * explain here. The reference implementation `guOcclusionPlane` is provided
 * separately.
 * 
 * o is the address of an OcclusionPlane struct
 */
#define gSPOcclusionPlane(pkt, o) \
    gDma2p((pkt), G_MOVEMEM, (o), sizeof(OcclusionPlane), G_MV_LIGHT, \
        (G_MAX_LIGHTS * 0x10) + 0x18)
/**
 * @copydetails gSPOcclusionPlane
 */
#define gsSPOcclusionPlane(o) \
    gsDma2p(      G_MOVEMEM, (o), sizeof(OcclusionPlane), G_MV_LIGHT, \
        (G_MAX_LIGHTS * 0x10) + 0x18)


/**
 * FOG macros
 * fm = z multiplier
 * fo = z offset
 * FOG FORMULA:    alpha(fog) = (eyespace z) * fm  + fo  CLAMPED 0 to 255
 *   note: (eyespace z) ranges -1 to 1
 *
 * Alternate method of setting fog:
 * min, max: range 0 to 1000: 0=nearplane, 1000=farplane
 * min is where fog begins (usually less than max and often 0)
 * max is where fog is thickest (usually 1000)
 *
 */
#define gSPFogFactor(pkt, fm, fo)                   \
    gMoveWd(pkt, G_MW_FOG, G_MWO_FOG,               \
       (_SHIFTL(fm, 16, 16) | _SHIFTL(fo, 0, 16)))

/**
 * @copydetails gSPFogFactor
 */
#define gsSPFogFactor(fm, fo)                       \
    gsMoveWd(G_MW_FOG, G_MWO_FOG,                   \
       (_SHIFTL(fm, 16, 16) | _SHIFTL(fo, 0, 16)))

#define gSPFogPosition(pkt, min, max)                               \
    gMoveWd(pkt, G_MW_FOG, G_MWO_FOG,                               \
       (_SHIFTL((128000 / ((max) - (min))), 16, 16) |               \
        _SHIFTL(((500 - (min)) * 256 / ((max) - (min))), 0, 16)))

#define gsSPFogPosition(min, max)                                   \
    gsMoveWd(G_MW_FOG, G_MWO_FOG,                                   \
       (_SHIFTL((128000 / ((max) - (min))), 16, 16) |               \
        _SHIFTL(((500 - (min)) * 256 / ((max) - (min))), 0, 16)))


/**
 * Macros to turn texture on/off
 */
#define gSPTexture(pkt, s, t, level, tile, on)                 \
_DW({                                                           \
    Gfx *_g = (Gfx *)(pkt);                                     \
                                                                \
    _g->words.w0 = (_SHIFTL(G_TEXTURE,  24, 8) |                \
                    _SHIFTL((level),    11, 3) |                \
                    _SHIFTL((tile),      8, 3) |                \
                    _SHIFTL((on),        1, 7));                \
    _g->words.w1 = (_SHIFTL((s), 16, 16) |                      \
                    _SHIFTL((t),  0, 16));                      \
})
/**
 * @copydetails gSPTexture
 */
#define gsSPTexture(s, t, level, tile, on) \
{                                           \
   (_SHIFTL(G_TEXTURE,  24, 8) |            \
    _SHIFTL((level),    11, 3) |            \
    _SHIFTL((tile),      8, 3) |            \
    _SHIFTL((on),        1, 7)),            \
   (_SHIFTL((s), 16, 16) |                  \
    _SHIFTL((t),  0, 16))                   \
}

/**
 * The bowtie value is a workaround for a bug in HW V1, and is not supported
 * by F3DEX2, let alone F3DEX3.
 */
#define gSPTextureL(pkt, s, t, level, bowtie, tile, on) \
    gSPTexture(pkt, s, t, level, tile, on)
/**
 * @copydetails gSPTextureL
 */
#define gsSPTextureL(s, t, level, bowtie, tile, on) \
    gsSPTexture(s, t, level, tile, on)

/**
 *  One gSPGeometryMode(pkt,c,s) GBI is equal to these two GBIs.
 *
 *      gSPClearGeometryMode(pkt,c)
 *      gSPSetGeometryMode(pkt,s)
 *
 *  gSPLoadGeometryMode(pkt, word) sets GeometryMode directly.
 */
#define gSPGeometryMode(pkt, c, s)                      \
_DW({                                                   \
    Gfx *_g = (Gfx *)(pkt);                             \
                                                        \
    _g->words.w0 = (_SHIFTL(G_GEOMETRYMODE, 24,  8) |   \
                    _SHIFTL(~(u32)(c),       0, 24));   \
    _g->words.w1 = (u32)(s);                            \
})

/**
 * @copydetails gSPGeometryMode
 */
#define gsSPGeometryMode(c, s)          \
{                                       \
   (_SHIFTL(G_GEOMETRYMODE, 24,  8) |   \
    _SHIFTL(~(u32)(c),       0, 24)),   \
    (u32)(s)                            \
}

#define gSPSetGeometryMode(pkt, word)   gSPGeometryMode((pkt), 0, (word))
#define gsSPSetGeometryMode(word)       gsSPGeometryMode(      0, (word))
#define gSPClearGeometryMode(pkt, word) gSPGeometryMode((pkt), (word), 0)
#define gsSPClearGeometryMode(word)     gsSPGeometryMode(      (word), 0)
#define gSPLoadGeometryMode(pkt, word)  gSPGeometryMode((pkt), -1, (word))
#define gsSPLoadGeometryMode(word)      gsSPGeometryMode(      -1, (word))

#define gsSPGeometryModeSetFirst(c, s)	gsSPGeometryMode(c, s)

#define gSPSetOtherMode(pkt, cmd, sft, len, data)           \
_DW({                                                       \
    Gfx *_g = (Gfx *)(pkt);                                 \
                                                            \
    _g->words.w0 = (_SHIFTL(cmd,                24, 8) |    \
                    _SHIFTL(32 - (sft) - (len),  8, 8) |    \
                    _SHIFTL((len) - 1,           0, 8));    \
    _g->words.w1 = (unsigned int)(data);                    \
})

#define gsSPSetOtherMode(cmd, sft, len, data)   \
{                                               \
   (_SHIFTL(cmd,                24, 8) |        \
    _SHIFTL(32 - (sft) - (len),  8, 8) |        \
    _SHIFTL((len) - 1,           0, 8)),        \
    (unsigned int)(data)                        \
}

/**
 * RDP setothermode register commands - register shadowed in RSP
 */
#define gDPPipelineMode(pkt, mode)  \
    gSPSetOtherMode(pkt, G_SETOTHERMODE_H, G_MDSFT_PIPELINE, 1, mode)
/**
 * @copydetails gDPPipelineMode
 */
#define gsDPPipelineMode(mode)      \
    gsSPSetOtherMode(    G_SETOTHERMODE_H, G_MDSFT_PIPELINE, 1, mode)

#define gDPSetCycleType(pkt, type)  \
    gSPSetOtherMode(pkt, G_SETOTHERMODE_H, G_MDSFT_CYCLETYPE, 2, type)
#define gsDPSetCycleType(type)      \
    gsSPSetOtherMode(    G_SETOTHERMODE_H, G_MDSFT_CYCLETYPE, 2, type)

#define gDPSetTexturePersp(pkt, type)   \
    gSPSetOtherMode(pkt, G_SETOTHERMODE_H, G_MDSFT_TEXTPERSP, 1, type)
#define gsDPSetTexturePersp(type)       \
    gsSPSetOtherMode(    G_SETOTHERMODE_H, G_MDSFT_TEXTPERSP, 1, type)

#define gDPSetTextureDetail(pkt, type)  \
    gSPSetOtherMode(pkt, G_SETOTHERMODE_H, G_MDSFT_TEXTDETAIL, 2, type)
#define gsDPSetTextureDetail(type)      \
    gsSPSetOtherMode(    G_SETOTHERMODE_H, G_MDSFT_TEXTDETAIL, 2, type)

#define gDPSetTextureLOD(pkt, type) \
    gSPSetOtherMode(pkt, G_SETOTHERMODE_H, G_MDSFT_TEXTLOD, 1, type)
#define gsDPSetTextureLOD(type)     \
    gsSPSetOtherMode(    G_SETOTHERMODE_H, G_MDSFT_TEXTLOD, 1, type)

#define gDPSetTextureLUT(pkt, type) \
    gSPSetOtherMode(pkt, G_SETOTHERMODE_H, G_MDSFT_TEXTLUT, 2, type)
#define gsDPSetTextureLUT(type)     \
    gsSPSetOtherMode(    G_SETOTHERMODE_H, G_MDSFT_TEXTLUT, 2, type)

#define gDPSetTextureFilter(pkt, type)  \
    gSPSetOtherMode(pkt, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, type)
#define gsDPSetTextureFilter(type)      \
    gsSPSetOtherMode(    G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, type)

#define gDPSetTextureConvert(pkt, type) \
    gSPSetOtherMode(pkt, G_SETOTHERMODE_H, G_MDSFT_TEXTCONV, 3, type)
#define gsDPSetTextureConvert(type)     \
    gsSPSetOtherMode(    G_SETOTHERMODE_H, G_MDSFT_TEXTCONV, 3, type)

#define gDPSetCombineKey(pkt, type) \
    gSPSetOtherMode(pkt, G_SETOTHERMODE_H, G_MDSFT_COMBKEY, 1, type)
#define gsDPSetCombineKey(type)     \
    gsSPSetOtherMode(    G_SETOTHERMODE_H, G_MDSFT_COMBKEY, 1, type)

#define gDPSetColorDither(pkt, mode)    \
    gSPSetOtherMode(pkt, G_SETOTHERMODE_H, G_MDSFT_RGBDITHER, 2, mode)
#define gsDPSetColorDither(mode)        \
    gsSPSetOtherMode(    G_SETOTHERMODE_H, G_MDSFT_RGBDITHER, 2, mode)

#define gDPSetAlphaDither(pkt, mode)    \
    gSPSetOtherMode(pkt, G_SETOTHERMODE_H, G_MDSFT_ALPHADITHER, 2, mode)
#define gsDPSetAlphaDither(mode)        \
    gsSPSetOtherMode(    G_SETOTHERMODE_H, G_MDSFT_ALPHADITHER, 2, mode)

/**
 * 'blendmask' is not supported anymore.
 * The bits are reserved for future use.
 * Fri May 26 13:45:55 PDT 1995
 * @deprecated
 */
#define gDPSetBlendMask(pkt, mask)  gDPNoOp(pkt)
/**
 * @copydetails gDPSetBlendMask
 */
#define gsDPSetBlendMask(mask)      gsDPNoOp()

#define gDPSetAlphaCompare(pkt, type)   \
    gSPSetOtherMode(pkt, G_SETOTHERMODE_L, G_MDSFT_ALPHACOMPARE, 2, type)
#define gsDPSetAlphaCompare(type)       \
    gsSPSetOtherMode(    G_SETOTHERMODE_L, G_MDSFT_ALPHACOMPARE, 2, type)

#define gDPSetDepthSource(pkt, src) \
    gSPSetOtherMode(pkt, G_SETOTHERMODE_L, G_MDSFT_ZSRCSEL, 1, src)
#define gsDPSetDepthSource(src) \
    gsSPSetOtherMode(    G_SETOTHERMODE_L, G_MDSFT_ZSRCSEL, 1, src)

#define gDPSetRenderMode(pkt, c0, c1)   \
    gSPSetOtherMode(pkt, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, (c0) | (c1))
#define gsDPSetRenderMode(c0, c1)   \
    gsSPSetOtherMode(    G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, (c0) | (c1))

#define gSetImage(pkt, cmd, fmt, siz, width, i)     \
_DW({                                               \
    Gfx *_g = (Gfx *)(pkt);                         \
                                                    \
    _g->words.w0 = (_SHIFTL(cmd,         24,  8) |  \
                    _SHIFTL(fmt,         21,  3) |  \
                    _SHIFTL(siz,         19,  2) |  \
                    _SHIFTL((width) - 1,  0, 12));  \
    _g->words.w1 = (unsigned int)(i);               \
})

#define gsSetImage(cmd, fmt, siz, width, i) \
{                                           \
   (_SHIFTL(cmd,         24,  8) |          \
    _SHIFTL(fmt,         21,  3) |          \
    _SHIFTL(siz,         19,  2) |          \
    _SHIFTL((width) - 1,  0, 12)),          \
    (unsigned int)(i)                       \
}

#define gDPSetColorImage(pkt, f, s, w, i)   gSetImage(pkt, G_SETCIMG, f, s, w, i)
#define gsDPSetColorImage(f, s, w, i)       gsSetImage(    G_SETCIMG, f, s, w, i)


/* use these for new code */
#define gDPSetDepthImage(pkt, i)    gSetImage(pkt, G_SETZIMG, 0, 0, 1, i)
#define gsDPSetDepthImage(i)        gsSetImage(    G_SETZIMG, 0, 0, 1, i)
/* kept for compatibility */
#define gDPSetMaskImage(pkt, i)     gDPSetDepthImage(pkt, i)
#define gsDPSetMaskImage(i)         gsDPSetDepthImage(    i)

#define gDPSetTextureImage(pkt, f, s, w, i) gSetImage(pkt, G_SETTIMG, f, s, w, i)
#define gsDPSetTextureImage(f, s, w, i)     gsSetImage(    G_SETTIMG, f, s, w, i)

/*
 * RDP macros
 */

#define gDPSetCombine(pkt, muxs0, muxs1)            \
_DW({                                               \
    Gfx *_g = (Gfx *)(pkt);                         \
                                                    \
    _g->words.w0 = (_SHIFTL(G_SETCOMBINE, 24,  8) | \
                    _SHIFTL(muxs0,         0, 24)); \
    _g->words.w1 = (unsigned int)(muxs1);           \
})

#define gsDPSetCombine(muxs0, muxs1)    \
{                                       \
   (_SHIFTL(G_SETCOMBINE, 24,  8) |     \
    _SHIFTL(muxs0,         0, 24)),     \
    (unsigned int)(muxs1)               \
}

#define GCCc0w0(saRGB0, mRGB0, saA0, mA0)   \
   (_SHIFTL((saRGB0), 20, 4) |              \
    _SHIFTL((mRGB0),  15, 5) |              \
    _SHIFTL((saA0),   12, 3) |              \
    _SHIFTL((mA0),     9, 3))

#define GCCc1w0(saRGB1, mRGB1)  \
   (_SHIFTL((saRGB1), 5, 4) |   \
    _SHIFTL((mRGB1),  0, 5))

#define GCCc0w1(sbRGB0, aRGB0, sbA0, aA0)   \
   (_SHIFTL((sbRGB0), 28, 4) |              \
    _SHIFTL((aRGB0),  15, 3) |              \
    _SHIFTL((sbA0),   12, 3) |              \
    _SHIFTL((aA0),     9, 3))

#define GCCc1w1(sbRGB1, saA1, mA1, aRGB1, sbA1, aA1)    \
   (_SHIFTL((sbRGB1), 24, 4) |                          \
    _SHIFTL((saA1),   21, 3) |                          \
    _SHIFTL((mA1),    18, 3) |                          \
    _SHIFTL((aRGB1),   6, 3) |                          \
    _SHIFTL((sbA1),    3, 3) |                          \
    _SHIFTL((aA1),     0, 3))

#define gDPSetCombineLERP(pkt, a0, b0, c0, d0, Aa0, Ab0, Ac0, Ad0,          \
                               a1, b1, c1, d1, Aa1, Ab1, Ac1, Ad1)          \
_DW({                                                                       \
    Gfx *_g = (Gfx *)(pkt);                                                 \
                                                                            \
    _g->words.w0 = (_SHIFTL(G_SETCOMBINE, 24, 8) |                          \
                    _SHIFTL(GCCc0w0(G_CCMUX_##a0,  G_CCMUX_##c0,            \
                                    G_ACMUX_##Aa0, G_ACMUX_##Ac0) |         \
                            GCCc1w0(G_CCMUX_##a1,  G_CCMUX_##c1),           \
                        0, 24));                                            \
    _g->words.w1 =  (unsigned int)(GCCc0w1(G_CCMUX_##b0,  G_CCMUX_##d0,     \
                                           G_ACMUX_##Ab0, G_ACMUX_##Ad0) |  \
                                   GCCc1w1(G_CCMUX_##b1,  G_ACMUX_##Aa1,    \
                                           G_ACMUX_##Ac1, G_CCMUX_##d1,     \
                                           G_ACMUX_##Ab1, G_ACMUX_##Ad1));  \
})

#define gsDPSetCombineLERP(a0, b0, c0, d0, Aa0, Ab0, Ac0, Ad0,  \
                           a1, b1, c1, d1, Aa1, Ab1, Ac1, Ad1)  \
{                                                               \
   (_SHIFTL(G_SETCOMBINE, 24, 8) |                              \
    _SHIFTL(GCCc0w0(G_CCMUX_##a0,  G_CCMUX_##c0,                \
                    G_ACMUX_##Aa0, G_ACMUX_##Ac0) |             \
            GCCc1w0(G_CCMUX_##a1,  G_CCMUX_##c1),               \
        0, 24)),                                                \
    (unsigned int)(GCCc0w1(G_CCMUX_##b0,  G_CCMUX_##d0,         \
                           G_ACMUX_##Ab0, G_ACMUX_##Ad0) |      \
                   GCCc1w1(G_CCMUX_##b1,  G_ACMUX_##Aa1,        \
                           G_ACMUX_##Ac1, G_CCMUX_##d1,         \
                           G_ACMUX_##Ab1, G_ACMUX_##Ad1))       \
}

/**
 * SetCombineMode macros are NOT redunant. It allow the C preprocessor
 * to substitute single parameter which includes commas in the token and
 * rescan for higher parameter count macro substitution.
 *
 * eg.  gsDPSetCombineMode(G_CC_MODULATE, G_CC_MODULATE) turns into
 *  gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0,
 *      TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0)
 */
#define gDPSetCombineMode(pkt, a, b)    gDPSetCombineLERP(pkt, a, b)
/**
 * @copydetails gDPSetCombineMode
 */
#define gsDPSetCombineMode(a, b)        gsDPSetCombineLERP(    a, b)

#define gDPSetColor(pkt, c, d)          \
_DW({                                   \
    Gfx *_g = (Gfx *)(pkt);             \
                                        \
    _g->words.w0 = _SHIFTL(c, 24, 8);   \
    _g->words.w1 = (unsigned int)(d);   \
})

#define gsDPSetColor(c, d)  \
{                           \
    _SHIFTL(c, 24, 8),      \
    (unsigned int)(d)       \
}

#define DPRGBColor(pkt, cmd, r, g, b, a)    \
    gDPSetColor(pkt, cmd,                   \
           (_SHIFTL(r, 24, 8) |             \
            _SHIFTL(g, 16, 8) |             \
            _SHIFTL(b,  8, 8) |             \
            _SHIFTL(a,  0, 8)))

#define sDPRGBColor(cmd, r, g, b, a)    \
    gsDPSetColor(cmd,                   \
           (_SHIFTL(r, 24, 8) |         \
            _SHIFTL(g, 16, 8) |         \
            _SHIFTL(b,  8, 8) |         \
            _SHIFTL(a,  0, 8)))

#define gDPSetEnvColor(pkt, r, g, b, a) \
            DPRGBColor(pkt, G_SETENVCOLOR,   r, g, b, a)

#define gsDPSetEnvColor(r, g, b, a) \
            sDPRGBColor(    G_SETENVCOLOR,   r, g, b, a)

#define gDPSetBlendColor(pkt, r, g, b, a) \
            DPRGBColor(pkt, G_SETBLENDCOLOR, r, g, b, a)

#define gsDPSetBlendColor(r, g, b, a) \
            sDPRGBColor(    G_SETBLENDCOLOR, r, g, b, a)

#define gDPSetFogColor(pkt, r, g, b, a) \
            DPRGBColor(pkt, G_SETFOGCOLOR,   r, g, b, a)

#define gsDPSetFogColor(r, g, b, a) \
            sDPRGBColor(    G_SETFOGCOLOR,   r, g, b, a)

#define gDPSetFillColor(pkt, d) \
            gDPSetColor(pkt, G_SETFILLCOLOR, (d))

#define gsDPSetFillColor(d) \
            gsDPSetColor(    G_SETFILLCOLOR, (d))

#define gDPSetPrimDepth(pkt, z, dz)                         \
        gDPSetColor(pkt, G_SETPRIMDEPTH,                    \
                    _SHIFTL(z, 16, 16) | _SHIFTL(dz, 0, 16))

#define gsDPSetPrimDepth(z, dz)                             \
        gsDPSetColor(G_SETPRIMDEPTH,                        \
                    _SHIFTL(z, 16, 16) | _SHIFTL(dz, 0, 16))

#define gDPSetPrimColor(pkt, m, l, r, g, b, a)          \
_DW({                                                   \
    Gfx *_g = (Gfx *)(pkt);                             \
                                                        \
    _g->words.w0 = (_SHIFTL(G_SETPRIMCOLOR, 24, 8) |    \
                    _SHIFTL(m,               8, 8) |    \
                    _SHIFTL(l,               0, 8));    \
    _g->words.w1 = (_SHIFTL(r, 24, 8) |                 \
                    _SHIFTL(g, 16, 8) |                 \
                    _SHIFTL(b,  8, 8) |                 \
                    _SHIFTL(a,  0, 8));                 \
})

#define gsDPSetPrimColor(m, l, r, g, b, a)  \
{                                           \
   (_SHIFTL(G_SETPRIMCOLOR, 24, 8) |        \
    _SHIFTL(m,               8, 8) |        \
    _SHIFTL(l,               0, 8)),        \
   (_SHIFTL(r, 24, 8) |                     \
    _SHIFTL(g, 16, 8) |                     \
    _SHIFTL(b,  8, 8) |                     \
    _SHIFTL(a,  0, 8))                      \
}

/**
 * Send the color of the specified light to one of the RDP's color registers.
 * light is the index of a light in the RSP counting from the end, i.e. 0 is
 * the ambient light, 1 is the last directional / point light, etc. The RGB
 * color of the selected light is combined with the alpha specified in this
 * command as word 1 of a RDP command, and word 0 is specified in this command.
 * Specialized versions are provided below for prim color and fog color, 
 * because these are the two versions needed for cel shading, but any RDP color
 * command could be specified this way.
 */
#define gSPLightToRDP(pkt, light, alpha, word0)    \
_DW({                                              \
    Gfx *_g = (Gfx *)(pkt);                        \
    _g->words.w0 = (_SHIFTL(G_LIGHTTORDP, 24, 8) | \
                    _SHIFTL(light * 0x10,  8, 8) | \
                    _SHIFTL(alpha,         0, 8)); \
    _g->words.w1 = (word0);                        \
})
/**
 * @copydetails gSPLightToRDP
 */
#define gsSPLightToRDP(light, alpha, word0) \
{                                           \
   (_SHIFTL(G_LIGHTTORDP, 24, 8) |          \
    _SHIFTL(light * 0x10,  8, 8) |          \
    _SHIFTL(alpha,         0, 8)),          \
   (word0)                                  \
}
#define gSPLightToPrimColor(pkt, light, alpha, m, l) \
    gSPLightToRDP(pkt, light, alpha,                 \
        (_SHIFTL(G_SETPRIMCOLOR, 24, 8) | _SHIFTL(m, 8, 8) | _SHIFTL(l, 0, 8)))
#define gsSPLightToPrimColor(light, alpha, m, l) \
    gsSPLightToRDP(light, alpha,                 \
        (_SHIFTL(G_SETPRIMCOLOR, 24, 8) | _SHIFTL(m, 8, 8) | _SHIFTL(l, 0, 8)))
#define gSPLightToFogColor(pkt, light, alpha) \
    gSPLightToRDP(pkt, light, alpha, _SHIFTL(G_SETFOGCOLOR, 24, 8))
#define gsSPLightToFogColor(light, alpha) \
    gsSPLightToRDP(light, alpha, _SHIFTL(G_SETFOGCOLOR, 24, 8))

/**
 * gDPSetOtherMode (This is for expert user.)
 *
 * This command makes all othermode parameters set.
 * Do not use this command in the same DL with another g*SPSetOtherMode DLs.
 *
 * [Usage]
 *  gDPSetOtherMode(pkt, modeA, modeB)
 *
 *      'modeA' is described all parameters of GroupA GBI command.
 *      'modeB' is also described all parameters of GroupB GBI command.
 *
 *  GroupA:
 *    gDPPipelineMode, gDPSetCycleType, gSPSetTexturePersp,
 *    gDPSetTextureDetail, gDPSetTextureLOD, gDPSetTextureLUT,
 *    gDPSetTextureFilter, gDPSetTextureConvert, gDPSetCombineKey,
 *    gDPSetColorDither, gDPSetAlphaDither
 *
 *  GroupB:
 *    gDPSetAlphaCompare, gDPSetDepthSource, gDPSetRenderMode
 *
 *  Use 'OR' operation to get modeA and modeB.
 *
 *  modeA = G_PM_* | G_CYC_* | G_TP_* | G_TD_* | G_TL_* | G_TT_* | G_TF_*
 *      G_TC_* | G_CK_*  | G_CD_* | G_AD_*;
 *
 *  modeB = G_AC_* | G_ZS_*  | G_RM_* | G_RM_*2;
 */
#define gDPSetOtherMode(pkt, mode0, mode1)              \
_DW({                                                   \
    Gfx *_g = (Gfx *)(pkt);                             \
                                                        \
    _g->words.w0 = (_SHIFTL(G_RDPSETOTHERMODE, 24, 8) | \
                    _SHIFTL(mode0, 0, 24));             \
    _g->words.w1 = (unsigned int)(mode1);               \
})

/**
 * @copydetails gDPSetOtherMode
 */
#define gsDPSetOtherMode(mode0, mode1)      \
{                                           \
   (_SHIFTL(G_RDPSETOTHERMODE, 24,  8) |    \
    _SHIFTL(mode0,              0, 24)),    \
    (unsigned int)(mode1)                   \
}

/*
 * Texturing macros
 */

#define G_TX_LOADTILE   7
#define G_TX_RENDERTILE 0

/*
 * Define this to remove syncs from texture loading multi-command macros.
 * 
 * You should convert your romhack codebase to F3DEX3 without this defined
 * first, then once everything is stable, define it and fix any crashes or
 * graphical issues that arise.
 * 
 * How the syncs work: load, tile, and pipe sync all delay the RDP by fixed
 * numbers of cycles. It is the smallest number for load, a medium number for
 * tile, and the largest number for pipe. These syncs do NOT wait until
 * something is finished being used; they just stall for a fixed time.
 * (DPFullSync is different and DOES wait for writebacks to memory to be done;
 * that is not considered in this explanation.)
 * 
 * Syncs always happen after rendering something and before changing some
 * settings. In other words:
 * - gsSP2Triangles(), gsSPTextureRectangle(), etc.
 * - gsDPSomeSync(),
 * - gsDPSetSomething()
 * You never need the opposite, i.e. you never need a sync after changing
 * settings but before rendering.
 * 
 * Which sync you use depends on which settings you are changing. If you are
 * doing a texture load (DPLoadBlock or DPLoadTile), you need a load sync (or
 * either of the other syncs which wait for even longer). If you are changing
 * tile settings, you need a tile sync (or pipe sync which is longer). If you
 * are changing CC, othermode, env color, or other things like that, you need
 * a pipe sync.
 * 
 * Display lists overall should be structured like:
 * 
 * - ...
 * - previous draw tris
 * - pipe sync
 * - texture load, CC settings, othermode, etc. (no syncs within these)
 * - (no sync here)
 * - draw tris
 * - pipe sync
 * - next material setup
 * - ...
 * 
 * In SM64, the pipe sync is at the end of each object or sub-object; in OoT
 * it is at the start of each display list. This ends up being the same thing
 * when the display lists are effectively concatenated: you have a pipe sync
 * after each set of rendering things, and before each new set of changing
 * settings.
 * 
 * If you are doing multitexture and/or CI texture loads, use a different tile
 * for each load, and then you don't need any syncs in the loads. As an extreme
 * example with two CI textures:
 * - previous pipe sync, either at the start of this DL or the end of the last
 * - set tile 7 to load texture 0 CIs (no syncs)
 * - load block on tile 7 (no syncs)
 * - set tile 5 to load texture 0 palette (no syncs)
 * - load block on tile 5 (no syncs)
 * - set tile 6 to load texture 1 CIs (no syncs)
 * - load block on tile 6 (no syncs)
 * - set tile 4 to load texture 1 palette (no syncs)
 * - load block on tile 4 (no syncs)
 * - set tile 0 for render texture 0 (no syncs)
 * - set tile 1 for render texture 0 (no syncs)
 * - set othermode, CC, etc. (no syncs)
 * - draw tris (no syncs)
 * - next pipe sync, either at the end of this DL or the start of the next
 * Both fast64 and the multi-command macros in this GBI if
 * NO_SYNCS_IN_TEXTURE_LOADS is enabled do this, but if you wrote the DLs by
 * hand or they were vanilla DLs not using the multi-command macros, they may
 * need to be updated. (Then again, in that case the syncs are also written by
 * hand, so these syncs changes do not affect them.)
 * 
 * If you are writing GUI display lists with texture rectangle which look like
 * - load tex
 * - tex rect
 * - load tex
 * - tex rect
 * you need a load sync before each load tex, and you don't need any other
 * syncs.
 */
#ifdef NO_SYNCS_IN_TEXTURE_LOADS
#define gDPLoadSyncInTexLoad(pkt) (void)0
#define gDPTileSyncInTexLoad(pkt) (void)0
#define gDPPipeSyncInTexLoad(pkt) (void)0
#define gsDPLoadSyncInTexLoad
#define gsDPTileSyncInTexLoad
#define gsDPPipeSyncInTexLoad
#define gsDPPipeSyncEndOfTexLoad
#define _G_TEXLOADTILE(rtile) (G_TX_LOADTILE - (rtile))
#define _G_PALLOADTILE(rtile) (G_TX_LOADTILE - 2 - (rtile))
#else
#define gDPLoadSyncInTexLoad(pkt) gDPLoadSync(pkt)
#define gDPTileSyncInTexLoad(pkt) gDPTileSync(pkt)
#define gDPPipeSyncInTexLoad(pkt) gDPPipeSync(pkt)
#define gsDPLoadSyncInTexLoad gsDPLoadSync(),
#define gsDPTileSyncInTexLoad gsDPTileSync(),
#define gsDPPipeSyncInTexLoad gsDPPipeSync(),
#define gsDPPipeSyncEndOfTexLoad , gsDPPipeSync()
#define _G_TEXLOADTILE(rtile) G_TX_LOADTILE
#define _G_PALLOADTILE(rtile) G_TX_LOADTILE
#endif


#define G_TX_NOMIRROR   (0 << 0)
#define G_TX_WRAP       (0 << 1)
#define G_TX_MIRROR     (1 << 0)
#define G_TX_CLAMP      (1 << 1)
#define G_TX_NOMASK     0
#define G_TX_NOLOD      0

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

/*
 *  Dxt is the inverse of the number of 64-bit words in a line of
 *  the texture being loaded using the load_block command.  If
 *  there are any 1's to the right of the 11th fractional bit,
 *  dxt should be rounded up.  The following macros accomplish
 *  this.  The 4b macros are a special case since 4-bit textures
 *  are loaded as 8-bit textures.  Dxt is fixed point 1.11. RJM
 */
#define G_TX_DXT_FRAC   11

/*
 *  For RCP 2.0, the maximum number of texels that can be loaded
 *  using a load_block command is 2048.  In order to load the total
 *  4kB of Tmem, change the texel size when loading to be G_IM_SIZ_16b,
 *  then change the tile to the proper texel size after the load.
 *  The g*DPLoadTextureBlock macros already do this, so this change
 *  will be transparent if you use these macros.  If you use
 *  the g*DPLoadBlock macros directly, you will need to handle this
 *  tile manipulation yourself.  RJM.
 */
#define G_TX_LDBLK_MAX_TXL  2047

#define TXL2WORDS(txls, b_txl)  \
    MAX(1, ((txls) * (b_txl) / 8))

#define CALC_DXT(width, b_txl)  \
    (((1 << G_TX_DXT_FRAC) + TXL2WORDS(width, b_txl) - 1) / TXL2WORDS(width, b_txl))

#define TXL2WORDS_4b(txls)  \
    MAX(1, ((txls) / 16))

#define CALC_DXT_4b(width)  \
    (((1 << G_TX_DXT_FRAC) + TXL2WORDS_4b(width) - 1) / TXL2WORDS_4b(width))

#define gDPLoadTileGeneric(pkt, c, tile, uls, ult, lrs, lrt)    \
_DW({                                                           \
    Gfx *_g = (Gfx *)(pkt);                                     \
                                                                \
    _g->words.w0 = (_SHIFTL(c,   24,  8) |                      \
                    _SHIFTL(uls, 12, 12) |                      \
                    _SHIFTL(ult,  0, 12));                      \
    _g->words.w1 = (_SHIFTL(tile, 24, 3) |                      \
                    _SHIFTL(lrs, 12, 12) |                      \
                    _SHIFTL(lrt, 0, 12));                       \
})

#define gsDPLoadTileGeneric(c, tile, uls, ult, lrs, lrt)    \
{                                                           \
   (_SHIFTL(c,   24,  8) |                                  \
    _SHIFTL(uls, 12, 12) |                                  \
    _SHIFTL(ult,  0, 12)),                                  \
   (_SHIFTL(tile, 24,  3) |                                 \
    _SHIFTL(lrs,  12, 12) |                                 \
    _SHIFTL(lrt,   0, 12))                                  \
}

#define gDPSetTileSize(pkt, t, uls, ult, lrs, lrt)                  \
        gDPLoadTileGeneric(pkt, G_SETTILESIZE, t, uls, ult, lrs, lrt)
#define gsDPSetTileSize(t, uls, ult, lrs, lrt)                      \
        gsDPLoadTileGeneric(    G_SETTILESIZE, t, uls, ult, lrs, lrt)
#define gDPLoadTile(pkt, t, uls, ult, lrs, lrt)                     \
        gDPLoadTileGeneric(pkt, G_LOADTILE, t, uls, ult, lrs, lrt)
#define gsDPLoadTile(t, uls, ult, lrs, lrt)                         \
        gsDPLoadTileGeneric(    G_LOADTILE, t, uls, ult, lrs, lrt)

#define gDPSetTile(pkt, fmt, siz, line, tmem, tile, palette, cmt,   \
                        maskt, shiftt, cms, masks, shifts)          \
_DW({                                                               \
    Gfx *_g = (Gfx *)(pkt);                                         \
                                                                    \
    _g->words.w0 = (_SHIFTL(G_SETTILE, 24, 8) |                     \
                    _SHIFTL(fmt,       21, 3) |                     \
                    _SHIFTL(siz,       19, 2) |                     \
                    _SHIFTL(line,       9, 9) |                     \
                    _SHIFTL(tmem,       0, 9));                     \
    _g->words.w1 = (_SHIFTL(tile,    24, 3) |                       \
                    _SHIFTL(palette, 20, 4) |                       \
                    _SHIFTL(cmt,     18, 2) |                       \
                    _SHIFTL(maskt,   14, 4) |                       \
                    _SHIFTL(shiftt,  10, 4) |                       \
                    _SHIFTL(cms,      8, 2) |                       \
                    _SHIFTL(masks,    4, 4) |                       \
                    _SHIFTL(shifts,   0, 4));                       \
})

#define gsDPSetTile(fmt, siz, line, tmem, tile, palette, cmt,   \
                    maskt, shiftt, cms, masks, shifts)          \
{                                                               \
   (_SHIFTL(G_SETTILE, 24, 8) |                                 \
    _SHIFTL(fmt,       21, 3) |                                 \
    _SHIFTL(siz,       19, 2) |                                 \
    _SHIFTL(line,       9, 9) |                                 \
    _SHIFTL(tmem,       0, 9)),                                 \
   (_SHIFTL(tile,    24, 3) |                                   \
    _SHIFTL(palette, 20, 4) |                                   \
    _SHIFTL(cmt,     18, 2) |                                   \
    _SHIFTL(maskt,   14, 4) |                                   \
    _SHIFTL(shiftt,  10, 4) |                                   \
    _SHIFTL(cms,      8, 2) |                                   \
    _SHIFTL(masks,    4, 4) |                                   \
    _SHIFTL(shifts,   0, 4))                                    \
}

#define gDPLoadBlock(pkt, tile, uls, ult, lrs, dxt)         \
_DW({                                                               \
    Gfx *_g = (Gfx *)(pkt);                                         \
    _g->words.w0 = (_SHIFTL(G_LOADBLOCK, 24,  8) |                  \
                    _SHIFTL(uls,         12, 12) |                  \
                    _SHIFTL(ult,          0, 12));                  \
    _g->words.w1 = (_SHIFTL(tile,                         24,  3) | \
                    _SHIFTL(MIN(lrs, G_TX_LDBLK_MAX_TXL), 12, 12) | \
                    _SHIFTL(dxt,                           0, 12)); \
})

#define gsDPLoadBlock(tile, uls, ult, lrs, dxt) \
{                                                       \
   (_SHIFTL(G_LOADBLOCK, 24,  8) |                      \
    _SHIFTL(uls,         12, 12) |                      \
    _SHIFTL(ult,          0, 12)),                      \
   (_SHIFTL(tile,                           24,  3) |   \
    _SHIFTL((MIN(lrs, G_TX_LDBLK_MAX_TXL)), 12, 12) |   \
    _SHIFTL(dxt,                             0, 12))    \
}

#define gDPLoadTLUTCmd(pkt, tile, count)        \
_DW({                                           \
    Gfx *_g = (Gfx *)pkt;                       \
                                                \
    _g->words.w0 = _SHIFTL(G_LOADTLUT, 24, 8);  \
    _g->words.w1 = (_SHIFTL((tile),  24,  3) |  \
                    _SHIFTL((count), 14, 10));  \
})

#define gsDPLoadTLUTCmd(tile, count)    \
{                                       \
    _SHIFTL(G_LOADTLUT, 24, 8),         \
   (_SHIFTL((tile),  24,  3) |          \
    _SHIFTL((count), 14, 10))           \
}

#define gDPLoadTextureBlock(pkt, timg, fmt, siz, width, height, pal,        \
                                 cms, cmt, masks, maskt, shifts, shiftt)    \
_DW({                                                                       \
    gDPSetTextureImage(pkt, fmt, siz##_LOAD_BLOCK, 1, timg);                \
    gDPSetTile(pkt, fmt, siz##_LOAD_BLOCK, 0, 0, G_TX_LOADTILE,             \
        0, cmt, maskt, shiftt, cms, masks, shifts);                         \
    gDPLoadSyncInTexLoad(pkt);                                              \
    gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0,                                  \
        (((width) * (height) + siz##_INCR) >> siz##_SHIFT) -1,              \
        CALC_DXT(width, siz##_BYTES));                                      \
    gDPPipeSyncInTexLoad(pkt);                                              \
    gDPSetTile(pkt, fmt, siz,                                               \
        (((width) * siz##_LINE_BYTES) + 7) >> 3, 0,                         \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);      \
    gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0,                              \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                             \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC);                            \
})

#define gDPLoadTextureBlockYuv(pkt, timg, fmt, siz, width, height, pal,     \
                                    cms, cmt, masks, maskt, shifts, shiftt) \
_DW({                                                                       \
    gDPSetTextureImage(pkt, fmt, siz##_LOAD_BLOCK, 1, timg);                \
    gDPSetTile(pkt, fmt, siz##_LOAD_BLOCK, 0, 0, G_TX_LOADTILE,             \
        0, cmt, maskt, shiftt, cms, masks, shifts);                         \
    gDPLoadSyncInTexLoad(pkt);                                              \
    gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0,                                  \
        (((width) * (height) + siz##_INCR) >> siz##_SHIFT) -1,              \
        CALC_DXT(width, siz##_BYTES));                                      \
    gDPPipeSyncInTexLoad(pkt);                                              \
    gDPSetTile(pkt, fmt, siz,                                               \
        (((width) * 1) + 7) >> 3, 0,                                        \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);      \
    gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0,                              \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                             \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC);                            \
})

/* Load fix rww 27jun95 */
/* The S at the end means odd lines are already word Swapped */

#define gDPLoadTextureBlockS(pkt, timg, fmt, siz, width, height, pal,       \
                                  cms, cmt, masks, maskt, shifts, shiftt)   \
_DW({                                                                       \
    gDPSetTextureImage(pkt, fmt, siz##_LOAD_BLOCK, 1, timg);                \
    gDPSetTile(pkt, fmt, siz##_LOAD_BLOCK, 0, 0, G_TX_LOADTILE,             \
        0, cmt, maskt, shiftt, cms, masks, shifts);                         \
    gDPLoadSyncInTexLoad(pkt);                                              \
    gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0,                                  \
        (((width) * (height) + siz##_INCR) >> siz##_SHIFT) - 1, 0);         \
    gDPPipeSyncInTexLoad(pkt);                                              \
    gDPSetTile(pkt, fmt, siz,                                               \
        (((width) * siz##_LINE_BYTES) + 7) >> 3, 0,                         \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);      \
    gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0,                              \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                             \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC);                            \
})

/**
 *  Allow tmem address and render tile to be specified.
 *  The S at the end means odd lines are already word Swapped
 */
#define gDPLoadMultiBlockS(pkt, timg, tmem, rtile, fmt, siz, width, height, pal,    \
                                cms, cmt, masks, maskt, shifts, shiftt)             \
_DW({                                                                               \
    gDPSetTextureImage(pkt, fmt, siz##_LOAD_BLOCK, 1, timg);                        \
    gDPSetTile(pkt, fmt, siz##_LOAD_BLOCK, 0, tmem, _G_TEXLOADTILE(rtile),          \
        0, cmt, maskt, shiftt, cms, masks, shifts);                                 \
    gDPLoadSyncInTexLoad(pkt);                                                      \
    gDPLoadBlock(pkt, _G_TEXLOADTILE(rtile), 0, 0,                                  \
        (((width) * (height) + siz##_INCR) >> siz##_SHIFT) - 1,0);                  \
    gDPPipeSyncInTexLoad(pkt);                                                      \
    gDPSetTile(pkt, fmt, siz,                                                       \
        (((width) * siz##_LINE_BYTES) + 7) >> 3, tmem,                              \
        rtile, pal, cmt, maskt, shiftt, cms, masks,                                 \
        shifts);                                                                    \
    gDPSetTileSize(pkt, rtile, 0, 0,                                                \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                                     \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC);                                    \
})


#define gDPLoadTextureBlockYuvS(pkt, timg, fmt, siz, width, height, pal,        \
                                     cms, cmt, masks, maskt, shifts, shiftt)    \
_DW({                                                                           \
    gDPSetTextureImage(pkt, fmt, siz##_LOAD_BLOCK, 1, timg);                    \
    gDPSetTile(pkt, fmt, siz##_LOAD_BLOCK, 0, 0, G_TX_LOADTILE,                 \
        0, cmt, maskt, shiftt, cms, masks, shifts);                             \
    gDPLoadSyncInTexLoad(pkt);                                                  \
    gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0,                                      \
        (((width) * (height) + siz##_INCR) >> siz##_SHIFT) - 1,0);              \
    gDPPipeSyncInTexLoad(pkt);                                                  \
    gDPSetTile(pkt, fmt, siz,                                                   \
        (((width) * 1) + 7) >> 3, 0,                                            \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);          \
    gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0,                                  \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                                 \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC);                                \
})

/*
 *  allows tmem address to be specified
 */
#define _gDPLoadTextureBlock(pkt, timg, tmem, fmt, siz, width, height, pal, \
                                  cms, cmt, masks, maskt, shifts, shiftt)   \
_DW({                                                                       \
    gDPSetTextureImage(pkt, fmt, siz##_LOAD_BLOCK, 1, timg);                \
    gDPSetTile(pkt, fmt, siz##_LOAD_BLOCK, 0, tmem, G_TX_LOADTILE,          \
        0, cmt, maskt, shiftt, cms, masks, shifts);                         \
    gDPLoadSyncInTexLoad(pkt);                                              \
    gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0,                                  \
        (((width) * (height) + siz##_INCR) >> siz##_SHIFT) - 1,             \
        CALC_DXT(width, siz##_BYTES));                                      \
    gDPPipeSyncInTexLoad(pkt);                                              \
    gDPSetTile(pkt, fmt, siz,                                               \
        (((width) * siz##_LINE_BYTES) + 7) >> 3, tmem,                      \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);      \
    gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0,                              \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                             \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC);                            \
})

/*
 *  allows tmem address and render tile to be specified
 */
#define _gDPLoadTextureBlockTile(pkt, timg, tmem, rtile, fmt, siz, width, height, pal,  \
                                      cms, cmt, masks, maskt, shifts, shiftt)           \
_DW({                                                                                   \
    gDPSetTextureImage(pkt, fmt, siz##_LOAD_BLOCK, 1, timg);                            \
    gDPSetTile(pkt, fmt, siz##_LOAD_BLOCK, 0, tmem, _G_TEXLOADTILE(rtile),              \
        0, cmt, maskt, shiftt, cms, masks, shifts);                                     \
    gDPLoadSyncInTexLoad(pkt);                                                          \
    gDPLoadBlock(pkt, _G_TEXLOADTILE(rtile), 0, 0,                                      \
        (((width) * (height) + siz##_INCR) >> siz##_SHIFT) - 1,                         \
        CALC_DXT(width, siz##_BYTES));                                                  \
    gDPPipeSyncInTexLoad(pkt);                                                          \
    gDPSetTile(pkt, fmt, siz,                                                           \
        (((width) * siz##_LINE_BYTES) + 7) >> 3, tmem,                                  \
        rtile, pal, cmt, maskt, shiftt, cms, masks, shifts);                            \
    gDPSetTileSize(pkt, rtile, 0, 0,                                                    \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                                         \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC);                                        \
})

/**
 *  allows tmem address and render tile to be specified
 */
#define gDPLoadMultiBlock(pkt, timg, tmem, rtile, fmt, siz, width, height, pal, \
                               cms, cmt, masks, maskt, shifts, shiftt)          \
_DW({                                                                           \
    gDPSetTextureImage(pkt, fmt, siz##_LOAD_BLOCK, 1, timg);                    \
    gDPSetTile(pkt, fmt, siz##_LOAD_BLOCK, 0, tmem, _G_TEXLOADTILE(rtile),      \
        0, cmt, maskt, shiftt, cms, masks, shifts);                             \
    gDPLoadSyncInTexLoad(pkt);                                                  \
    gDPLoadBlock(pkt, _G_TEXLOADTILE(rtile), 0, 0,                              \
        (((width) * (height) + siz##_INCR) >> siz##_SHIFT) - 1,                 \
        CALC_DXT(width, siz##_BYTES));                                          \
    gDPPipeSyncInTexLoad(pkt);                                                  \
    gDPSetTile(pkt, fmt, siz,                                                   \
        (((width) * siz##_LINE_BYTES) + 7) >> 3, tmem,                          \
        rtile, pal, cmt, maskt, shiftt, cms, masks, shifts);                    \
    gDPSetTileSize(pkt, rtile, 0, 0,                                            \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                                 \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC);                                \
})

#define gsDPLoadTextureBlock(timg, fmt, siz, width, height, pal,        \
                             cms, cmt, masks, maskt, shifts, shiftt)    \
    gsDPSetTextureImage(fmt, siz##_LOAD_BLOCK, 1, timg),                \
    gsDPSetTile(fmt, siz##_LOAD_BLOCK, 0, 0, G_TX_LOADTILE,             \
        0, cmt, maskt, shiftt, cms, masks, shifts),                     \
    gsDPLoadSyncInTexLoad                                               \
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0,                                  \
        (((width)*(height) + siz##_INCR) >> siz##_SHIFT) - 1,           \
        CALC_DXT(width, siz##_BYTES)),                                  \
    gsDPPipeSyncInTexLoad                                               \
    gsDPSetTile(fmt, siz,                                               \
        ((((width) * siz##_LINE_BYTES) + 7) >> 3), 0,                   \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts),  \
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,                              \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                         \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC)

/* Here is the static form of the pre-swapped texture block loading */
/* See gDPLoadTextureBlockS() for reference.  Basically, just don't
   calculate DxT, use 0 */

#define gsDPLoadTextureBlockS(timg, fmt, siz, width, height, pal,       \
                              cms, cmt, masks, maskt, shifts, shiftt)   \
    gsDPSetTextureImage(fmt, siz##_LOAD_BLOCK, 1, timg),                \
    gsDPSetTile(fmt, siz##_LOAD_BLOCK, 0, 0, G_TX_LOADTILE,             \
        0, cmt, maskt,shiftt, cms, masks, shifts),                      \
    gsDPLoadSyncInTexLoad                                               \
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0,                                  \
        (((width) * (height) + siz##_INCR) >> siz##_SHIFT) - 1, 0),     \
    gsDPPipeSyncInTexLoad                                               \
    gsDPSetTile(fmt, siz,                                               \
        ((((width) * siz##_LINE_BYTES) + 7) >> 3), 0,                   \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks,           \
        shifts),                                                        \
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,                              \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                         \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC)

/*
 *  Allow tmem address to be specified
 */
#define _gsDPLoadTextureBlock(timg, tmem, fmt, siz, width, height, pal, \
                              cms, cmt, masks, maskt, shifts, shiftt)   \
    gsDPSetTextureImage(fmt, siz##_LOAD_BLOCK, 1, timg),                \
    gsDPSetTile(fmt, siz##_LOAD_BLOCK, 0, tmem, G_TX_LOADTILE,          \
        0, cmt, maskt, shiftt, cms, masks, shifts),                     \
    gsDPLoadSyncInTexLoad                                               \
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0,                                  \
        (((width) * (height) + siz##_INCR) >> siz##_SHIFT) - 1,         \
        CALC_DXT(width, siz##_BYTES)),                                  \
    gsDPPipeSyncInTexLoad                                               \
    gsDPSetTile(fmt, siz,                                               \
        ((((width) * siz##_LINE_BYTES) + 7) >> 3), tmem,                \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks,           \
        shifts),                                                        \
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,                              \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                         \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC)


/*
 *  Allow tmem address and render_tile to be specified
 */
#define _gsDPLoadTextureBlockTile(timg, tmem, rtile, fmt, siz, width, height, pal,  \
                                  cms, cmt, masks, maskt, shifts, shiftt)           \
    gsDPSetTextureImage(fmt, siz##_LOAD_BLOCK, 1, timg),                            \
    gsDPSetTile(fmt, siz##_LOAD_BLOCK, 0, tmem, _G_TEXLOADTILE(rtile),              \
        0, cmt, maskt, shiftt, cms, masks, shifts),                                 \
    gsDPLoadSyncInTexLoad                                                           \
    gsDPLoadBlock(_G_TEXLOADTILE(rtile), 0, 0,                                      \
        (((width) * (height) + siz##_INCR) >> siz##_SHIFT) - 1,                     \
        CALC_DXT(width, siz##_BYTES)),                                              \
    gsDPPipeSyncInTexLoad                                                           \
    gsDPSetTile(fmt, siz,                                                           \
        ((((width) * siz##_LINE_BYTES) + 7) >> 3), tmem,                            \
        rtile, pal, cmt, maskt, shiftt, cms, masks,                                 \
        shifts),                                                                    \
    gsDPSetTileSize(rtile, 0, 0,                                                    \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                                     \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC)


/**
 *  Allow tmem address and render_tile to be specified, useful when loading
 *  mutilple tiles at a time.
 */
#define gsDPLoadMultiBlock(timg, tmem, rtile, fmt, siz, width, height, pal, \
                           cms, cmt, masks, maskt, shifts, shiftt)          \
    gsDPSetTextureImage(fmt, siz##_LOAD_BLOCK, 1, timg),                    \
    gsDPSetTile(fmt, siz##_LOAD_BLOCK, 0, tmem, _G_TEXLOADTILE(rtile),      \
        0, cmt, maskt, shiftt, cms, masks, shifts),                         \
    gsDPLoadSyncInTexLoad                                                   \
    gsDPLoadBlock(_G_TEXLOADTILE(rtile), 0, 0,                              \
        (((width) * (height) + siz##_INCR) >> siz##_SHIFT) - 1,             \
        CALC_DXT(width, siz##_BYTES)),                                      \
    gsDPPipeSyncInTexLoad                                                   \
    gsDPSetTile(fmt, siz,                                                   \
        ((((width) * siz##_LINE_BYTES) + 7) >> 3), tmem,                    \
        rtile, pal, cmt, maskt, shiftt, cms, masks, shifts),                \
    gsDPSetTileSize(rtile, 0, 0,                                            \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                             \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC)

/**
 *  Allows tmem and render tile to be specified.  Useful when loading
 *  several tiles at a time.
 *
 *  Here is the static form of the pre-swapped texture block loading
 *  See gDPLoadTextureBlockS() for reference.  Basically, just don't
 *  calculate DxT, use 0
 */
#define gsDPLoadMultiBlockS(timg, tmem, rtile, fmt, siz, width, height, pal,    \
                            cms, cmt, masks, maskt, shifts, shiftt)             \
    gsDPSetTextureImage(fmt, siz##_LOAD_BLOCK, 1, timg),                        \
    gsDPSetTile(fmt, siz##_LOAD_BLOCK, 0, tmem, _G_TEXLOADTILE(rtile),          \
        0, cmt, maskt,shiftt, cms, masks, shifts),                              \
    gsDPLoadSyncInTexLoad                                                       \
    gsDPLoadBlock(_G_TEXLOADTILE(rtile), 0, 0,                                  \
        (((width) * (height) + siz##_INCR) >> siz##_SHIFT) - 1, 0),             \
    gsDPPipeSyncInTexLoad                                                       \
    gsDPSetTile(fmt, siz,                                                       \
        ((((width) * siz##_LINE_BYTES) + 7) >> 3), tmem,                        \
        rtile, pal, cmt, maskt, shiftt, cms, masks, shifts),                    \
    gsDPSetTileSize(rtile, 0, 0,                                                \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                                 \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC)


#define gDPLoadTextureBlock_4b(pkt, timg, fmt, width, height, pal,          \
                                    cms, cmt, masks, maskt, shifts, shiftt) \
_DW({                                                                       \
    gDPSetTextureImage(pkt, fmt, G_IM_SIZ_16b, 1, timg);                    \
    gDPSetTile(pkt, fmt, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE,                 \
        0, cmt, maskt, shiftt, cms, masks, shifts);                         \
    gDPLoadSyncInTexLoad(pkt);                                              \
    gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0,                                  \
        (((width) * (height) + 3) >> 2) - 1,                                \
        CALC_DXT_4b(width));                                                \
    gDPPipeSyncInTexLoad(pkt);                                              \
    gDPSetTile(pkt, fmt, G_IM_SIZ_4b,                                       \
        ((((width) >> 1) + 7) >> 3), 0,                                     \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);      \
    gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0,                              \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                             \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC);                            \
})

/* Load fix rww 27jun95 */
/* The S at the end means odd lines are already word Swapped */

#define gDPLoadTextureBlock_4bS(pkt, timg, fmt, width, height, pal,             \
                                     cms, cmt, masks, maskt, shifts, shiftt)    \
_DW({                                                                           \
    gDPSetTextureImage(pkt, fmt, G_IM_SIZ_16b, 1, timg);                        \
    gDPSetTile(pkt, fmt, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE,                     \
        0, cmt, maskt, shiftt, cms, masks, shifts);                             \
    gDPLoadSyncInTexLoad(pkt);                                                  \
    gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0,                                      \
        (((width) * (height) + 3) >> 2) - 1,                                    \
        0);                                                                     \
    gDPPipeSyncInTexLoad(pkt);                                                  \
    gDPSetTile(pkt, fmt, G_IM_SIZ_4b,                                           \
        ((((width) >> 1) + 7) >> 3), 0,                                         \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);          \
    gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0,                                  \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                                 \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC);                                \
})

/**
 *  4-bit load block.  Useful when loading multiple tiles
 */
#define gDPLoadMultiBlock_4b(pkt, timg, tmem, rtile, fmt, width, height, pal,   \
                                  cms, cmt, masks, maskt, shifts, shiftt)       \
_DW({                                                                           \
    gDPSetTextureImage(pkt, fmt, G_IM_SIZ_16b, 1, timg);                        \
    gDPSetTile(pkt, fmt, G_IM_SIZ_16b, 0, tmem, _G_TEXLOADTILE(rtile),          \
        0, cmt, maskt, shiftt, cms, masks, shifts);                             \
    gDPLoadSyncInTexLoad(pkt);                                                  \
    gDPLoadBlock(pkt, _G_TEXLOADTILE(rtile), 0, 0,                              \
        (((width) * (height) + 3) >> 2) - 1,                                    \
        CALC_DXT_4b(width));                                                    \
    gDPPipeSyncInTexLoad(pkt);                                                  \
    gDPSetTile(pkt, fmt, G_IM_SIZ_4b,                                           \
        ((((width) >> 1) + 7) >> 3), tmem,                                      \
        rtile, pal, cmt, maskt, shiftt, cms, masks, shifts);                    \
    gDPSetTileSize(pkt, rtile, 0, 0,                                            \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                                 \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC);                                \
})

/**
 *  4-bit load block.  Allows tmem and render tile to be specified.  Useful when
 *  loading multiple tiles.  The S means odd lines are already word swapped.
 */
#define gDPLoadMultiBlock_4bS(pkt, timg, tmem, rtile, fmt, width, height, pal,  \
                                   cms, cmt, masks, maskt, shifts, shiftt)      \
_DW({                                                                           \
    gDPSetTextureImage(pkt, fmt, G_IM_SIZ_16b, 1, timg);                        \
    gDPSetTile(pkt, fmt, G_IM_SIZ_16b, 0, tmem, _G_TEXLOADTILE(rtile),          \
        0, cmt, maskt, shiftt, cms, masks, shifts);                             \
    gDPLoadSyncInTexLoad(pkt);                                                  \
    gDPLoadBlock(pkt, _G_TEXLOADTILE(rtile), 0, 0,                              \
        (((width) * (height) + 3) >> 2) - 1,                                    \
        0);                                                                     \
    gDPPipeSyncInTexLoad(pkt);                                                  \
    gDPSetTile(pkt, fmt, G_IM_SIZ_4b,                                           \
        ((((width) >> 1) + 7) >> 3), tmem,                                      \
        rtile, pal, cmt, maskt, shiftt, cms, masks, shifts);                    \
    gDPSetTileSize(pkt, rtile, 0, 0,                                            \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                                 \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC);                                \
})


#define _gDPLoadTextureBlock_4b(pkt, timg, tmem, fmt, width, height, pal,       \
                                     cms, cmt, masks, maskt, shifts, shiftt)    \
_DW({                                                                           \
    gDPSetTextureImage(pkt, fmt, G_IM_SIZ_16b, 1, timg);                        \
    gDPSetTile(pkt, fmt, G_IM_SIZ_16b, 0, tmem, G_TX_LOADTILE,                  \
        0, cmt, maskt, shiftt, cms, masks, shifts);                             \
    gDPLoadSyncInTexLoad(pkt);                                                  \
    gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0,                                      \
        (((width) * (height) + 3) >> 2) - 1,                                    \
        CALC_DXT_4b(width));                                                    \
    gDPPipeSyncInTexLoad(pkt);                                                  \
    gDPSetTile(pkt, fmt, G_IM_SIZ_4b,                                           \
        ((((width) >> 1) + 7) >> 3), tmem,                                      \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);          \
    gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0,                                  \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                                 \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC);                                \
})

#define gsDPLoadTextureBlock_4b(timg, fmt, width, height, pal,          \
                                cms, cmt, masks, maskt, shifts, shiftt) \
    gsDPSetTextureImage(fmt, G_IM_SIZ_16b, 1, timg),                    \
    gsDPSetTile(fmt, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE,                 \
        0, cmt, maskt, shiftt, cms, masks, shifts),                     \
    gsDPLoadSyncInTexLoad                                               \
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0,                                  \
        (((width) * (height) + 3) >> 2) - 1,                            \
        CALC_DXT_4b(width)),                                            \
    gsDPPipeSyncInTexLoad                                               \
    gsDPSetTile(fmt, G_IM_SIZ_4b,                                       \
        ((((width) >> 1) + 7) >> 3), 0,                                 \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts),  \
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,                              \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                         \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC)

#define gsDPLoadTextureBlock_4bS(timg, fmt, width, height, pal,             \
                                 cms, cmt, masks, maskt, shifts, shiftt)    \
    gsDPSetTextureImage(fmt, G_IM_SIZ_16b, 1, timg),                        \
    gsDPSetTile(fmt, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE,                     \
        0, cmt, maskt, shiftt, cms, masks, shifts),                         \
    gsDPLoadSyncInTexLoad                                                   \
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0,                                      \
        (((width) * (height) + 3) >> 2) - 1,                                \
        0),                                                                 \
    gsDPPipeSyncInTexLoad                                                   \
    gsDPSetTile(fmt, G_IM_SIZ_4b,                                           \
        ((((width) >> 1) + 7) >> 3), 0,                                     \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts),      \
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,                                  \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                             \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC)

/**
 *  4-bit load block.  Allows tmem address and render tile to be specified.
 *  Useful when loading multiple tiles.
 */
#define gsDPLoadMultiBlock_4b(timg, tmem, rtile, fmt, width, height, pal,   \
                              cms, cmt, masks, maskt, shifts, shiftt)       \
    gsDPSetTextureImage(fmt, G_IM_SIZ_16b, 1, timg),                        \
    gsDPSetTile(fmt, G_IM_SIZ_16b, 0, tmem, _G_TEXLOADTILE(rtile),          \
        0, cmt, maskt, shiftt, cms, masks, shifts),                         \
    gsDPLoadSyncInTexLoad                                                   \
    gsDPLoadBlock(_G_TEXLOADTILE(rtile), 0, 0,                              \
        (((width) * (height) + 3) >> 2) - 1,                                \
        CALC_DXT_4b(width)),                                                \
    gsDPPipeSyncInTexLoad                                                   \
    gsDPSetTile(fmt, G_IM_SIZ_4b,                                           \
        ((((width) >> 1) + 7) >> 3), tmem,                                  \
        rtile, pal, cmt, maskt, shiftt, cms, masks, shifts),                \
    gsDPSetTileSize(rtile, 0, 0,                                            \
        ((width)-1) << G_TEXTURE_IMAGE_FRAC,                                \
        ((height)-1) << G_TEXTURE_IMAGE_FRAC)


/**
 *  4-bit load block.  Allows tmem address and render tile to be specified.
 *  Useful when loading multiple tiles.  S means odd lines are already swapped.
 */
#define gsDPLoadMultiBlock_4bS(timg, tmem, rtile, fmt, width, height, pal,  \
                               cms, cmt, masks, maskt, shifts, shiftt)      \
    gsDPSetTextureImage(fmt, G_IM_SIZ_16b, 1, timg),                        \
    gsDPSetTile(fmt, G_IM_SIZ_16b, 0, tmem, _G_TEXLOADTILE(rtile),          \
        0, cmt, maskt, shiftt, cms, masks, shifts),                         \
    gsDPLoadSyncInTexLoad                                                   \
    gsDPLoadBlock(_G_TEXLOADTILE(rtile), 0, 0,                              \
        (((width) * (height) + 3) >> 2) - 1,                                \
        0),                                                                 \
    gsDPPipeSyncInTexLoad                                                   \
    gsDPSetTile(fmt, G_IM_SIZ_4b,                                           \
        ((((width) >> 1) + 7) >> 3), tmem,                                  \
        rtile, pal, cmt, maskt, shiftt, cms, masks, shifts),                \
    gsDPSetTileSize(rtile, 0, 0,                                            \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                             \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC)


/*
 *  Allows tmem address to be specified
 */
#define _gsDPLoadTextureBlock_4b(timg, tmem, fmt, width, height, pal,       \
                                 cms, cmt, masks, maskt, shifts, shiftt)    \
    gsDPSetTextureImage(fmt, G_IM_SIZ_16b, 1, timg),                        \
    gsDPSetTile(fmt, G_IM_SIZ_16b, 0, tmem, G_TX_LOADTILE,                  \
        0, cmt, maskt, shiftt, cms, masks, shifts),                         \
    gsDPLoadSyncInTexLoad                                                   \
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0,                                      \
        (((width) * (height) + 3) >> 2) - 1,                                \
        CALC_DXT_4b(width)),                                                \
    gsDPPipeSyncInTexLoad                                                   \
    gsDPSetTile(fmt, G_IM_SIZ_4b,                                           \
        ((((width) >> 1) + 7) >> 3), tmem,                                  \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts),      \
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,                                  \
        ((width)  - 1) << G_TEXTURE_IMAGE_FRAC,                             \
        ((height) - 1) << G_TEXTURE_IMAGE_FRAC)

#define gDPLoadTextureTile(pkt, timg, fmt, siz, width, height,          \
                                uls, ult, lrs, lrt, pal,                \
                                cms, cmt, masks, maskt, shifts, shiftt) \
_DW({                                                                   \
    gDPSetTextureImage(pkt, fmt, siz, width, timg);                     \
    gDPSetTile(pkt, fmt, siz,                                           \
        (((((lrs) - (uls) + 1) * siz##_TILE_BYTES) + 7) >> 3), 0,       \
        G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks,               \
        shifts);                                                        \
    gDPLoadSyncInTexLoad(pkt);                                          \
    gDPLoadTile(pkt, G_TX_LOADTILE,                                     \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                  \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                  \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                  \
        (lrt) << G_TEXTURE_IMAGE_FRAC);                                 \
    gDPPipeSyncInTexLoad(pkt);                                          \
    gDPSetTile(pkt, fmt, siz,                                           \
        (((((lrs) - (uls) + 1) * siz##_LINE_BYTES) + 7) >> 3), 0,       \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);  \
    gDPSetTileSize(pkt, G_TX_RENDERTILE,                                \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                  \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                  \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                  \
        (lrt) << G_TEXTURE_IMAGE_FRAC);                                 \
})

/**
 *  Load texture tile.  Allows tmem address and render tile to be specified.
 *  Useful for loading multiple tiles.
 */
#define gDPLoadMultiTile(pkt, timg, tmem, rtile, fmt, siz, width, height,   \
                              uls, ult, lrs, lrt, pal,                      \
                              cms, cmt, masks, maskt, shifts, shiftt)       \
_DW({                                                                       \
    gDPSetTextureImage(pkt, fmt, siz, width, timg);                         \
    gDPSetTile(pkt, fmt, siz,                                               \
        (((((lrs) - (uls) + 1) * siz##_TILE_BYTES) + 7) >> 3), tmem,        \
        _G_TEXLOADTILE(rtile), 0, cmt, maskt, shiftt, cms, masks, shifts);  \
    gDPLoadSyncInTexLoad(pkt);                                              \
    gDPLoadTile(pkt, _G_TEXLOADTILE(rtile),                                 \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                      \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                      \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                      \
        (lrt) << G_TEXTURE_IMAGE_FRAC);                                     \
    gDPPipeSyncInTexLoad(pkt);                                              \
    gDPSetTile(pkt, fmt, siz,                                               \
        (((((lrs) - (uls) + 1) * siz##_LINE_BYTES) + 7) >> 3), tmem,        \
        rtile, pal, cmt, maskt, shiftt, cms, masks, shifts);                \
    gDPSetTileSize(pkt, rtile,                                              \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                      \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                      \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                      \
        (lrt) << G_TEXTURE_IMAGE_FRAC);                                     \
})


#define gsDPLoadTextureTile(timg, fmt, siz, width, height,              \
                            uls, ult, lrs, lrt, pal,                    \
                            cms, cmt, masks, maskt, shifts, shiftt)     \
    gsDPSetTextureImage(fmt, siz, width, timg),                         \
    gsDPSetTile(fmt, siz,                                               \
        (((((lrs) - (uls) + 1) * siz##_TILE_BYTES) + 7) >> 3), 0,       \
        G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks, shifts),      \
    gsDPLoadSyncInTexLoad                                               \
    gsDPLoadTile(G_TX_LOADTILE,                                         \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                  \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                  \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                  \
        (lrt) << G_TEXTURE_IMAGE_FRAC),                                 \
    gsDPPipeSyncInTexLoad                                               \
    gsDPSetTile(fmt, siz,                                               \
        (((((lrs) - (uls) + 1) * siz##_LINE_BYTES) + 7) >> 3), 0,       \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts),  \
    gsDPSetTileSize(G_TX_RENDERTILE,                                    \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                  \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                  \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                  \
        (lrt) << G_TEXTURE_IMAGE_FRAC)

/**
 *  Load texture tile.  Allows tmem address and render tile to be specified.
 *  Useful for loading multiple tiles.
 */
#define gsDPLoadMultiTile(timg, tmem, rtile, fmt, siz, width, height,      \
                          uls, ult, lrs, lrt, pal,                         \
                          cms, cmt, masks, maskt, shifts, shiftt)          \
    gsDPSetTextureImage(fmt, siz, width, timg),                            \
    gsDPSetTile(fmt, siz,                                                  \
        (((((lrs) - (uls) + 1) * siz##_TILE_BYTES) + 7) >> 3), tmem,       \
        _G_TEXLOADTILE(rtile), 0, cmt, maskt, shiftt, cms, masks, shifts), \
    gsDPLoadSyncInTexLoad                                                  \
    gsDPLoadTile(_G_TEXLOADTILE(rtile),                                    \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                     \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                     \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                     \
        (lrt) << G_TEXTURE_IMAGE_FRAC),                                    \
    gsDPPipeSyncInTexLoad                                                  \
    gsDPSetTile(fmt, siz,                                                  \
        (((((lrs) - (uls) + 1) * siz##_LINE_BYTES) + 7) >> 3),             \
        tmem, rtile, pal, cmt, maskt, shiftt, cms, masks, shifts),         \
    gsDPSetTileSize(rtile,                                                 \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                     \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                     \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                     \
        (lrt) << G_TEXTURE_IMAGE_FRAC)

#define gDPLoadTextureTile_4b(pkt, timg, fmt, width, height,                \
                                   uls, ult, lrs, lrt, pal,                 \
                                   cms, cmt, masks, maskt, shifts, shiftt)  \
_DW({                                                                       \
    gDPSetTextureImage(pkt, fmt, G_IM_SIZ_8b, ((width) >> 1), timg);        \
    gDPSetTile(pkt, fmt, G_IM_SIZ_8b,                                       \
        (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0,                         \
        G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks, shifts);          \
    gDPLoadSyncInTexLoad(pkt);                                              \
    gDPLoadTile(pkt, G_TX_LOADTILE,                                         \
        (uls) << (G_TEXTURE_IMAGE_FRAC - 1),                                \
        (ult) << (G_TEXTURE_IMAGE_FRAC),                                    \
        (lrs) << (G_TEXTURE_IMAGE_FRAC - 1),                                \
        (lrt) << (G_TEXTURE_IMAGE_FRAC));                                   \
    gDPPipeSyncInTexLoad(pkt);                                              \
    gDPSetTile(pkt, fmt, G_IM_SIZ_4b,                                       \
        (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0,                         \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);      \
    gDPSetTileSize(pkt, G_TX_RENDERTILE,                                    \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                      \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                      \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                      \
        (lrt) << G_TEXTURE_IMAGE_FRAC);                                     \
})

/**
 *  Load texture tile.  Allows tmem address and render tile to be specified.
 *  Useful for loading multiple tiles.
 */
#define gDPLoadMultiTile_4b(pkt, timg, tmem, rtile, fmt, width, height,     \
                                 uls, ult, lrs, lrt, pal,                   \
                                 cms, cmt, masks, maskt, shifts, shiftt)    \
_DW({                                                                       \
    gDPSetTextureImage(pkt, fmt, G_IM_SIZ_8b, ((width) >> 1), timg);        \
    gDPSetTile(pkt, fmt, G_IM_SIZ_8b,                                       \
        (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), tmem,                      \
        _G_TEXLOADTILE(rtile), 0, cmt, maskt, shiftt, cms, masks, shifts);  \
    gDPLoadSyncInTexLoad(pkt);                                              \
    gDPLoadTile(pkt, _G_TEXLOADTILE(rtile),                                 \
        (uls) << (G_TEXTURE_IMAGE_FRAC - 1),                                \
        (ult) << (G_TEXTURE_IMAGE_FRAC),                                    \
        (lrs) << (G_TEXTURE_IMAGE_FRAC - 1),                                \
        (lrt) << (G_TEXTURE_IMAGE_FRAC));                                   \
    gDPPipeSyncInTexLoad(pkt);                                              \
    gDPSetTile(pkt, fmt, G_IM_SIZ_4b,                                       \
        (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), tmem,                      \
        rtile, pal, cmt, maskt, shiftt, cms, masks, shifts);                \
    gDPSetTileSize(pkt, rtile,                                              \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                      \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                      \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                      \
        (lrt) << G_TEXTURE_IMAGE_FRAC);                                     \
})

#define gsDPLoadTextureTile_4b(timg, fmt, width, height,                \
                               uls, ult, lrs, lrt, pal,                 \
                               cms, cmt, masks, maskt, shifts, shiftt)  \
    gsDPSetTextureImage(fmt, G_IM_SIZ_8b, ((width) >> 1), timg),        \
    gsDPSetTile(fmt, G_IM_SIZ_8b,                                       \
        (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0,                     \
        G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks, shifts),      \
    gsDPLoadSyncInTexLoad                                               \
    gsDPLoadTile(G_TX_LOADTILE,                                         \
        (uls) << (G_TEXTURE_IMAGE_FRAC - 1),                            \
        (ult) << (G_TEXTURE_IMAGE_FRAC),                                \
        (lrs) << (G_TEXTURE_IMAGE_FRAC - 1),                            \
        (lrt) << (G_TEXTURE_IMAGE_FRAC)),                               \
    gsDPPipeSyncInTexLoad                                               \
    gsDPSetTile(fmt, G_IM_SIZ_4b,                                       \
        (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), 0,                     \
        G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts),  \
    gsDPSetTileSize(G_TX_RENDERTILE,                                    \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                  \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                  \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                  \
        (lrt) << G_TEXTURE_IMAGE_FRAC)

/**
 * @copydetails gDPLoadMultiTile_4b
 */
#define gsDPLoadMultiTile_4b(timg, tmem, rtile, fmt, width, height,        \
                             uls, ult, lrs, lrt, pal,                      \
                             cms, cmt, masks, maskt, shifts, shiftt)       \
                                                                           \
    gsDPSetTextureImage(fmt, G_IM_SIZ_8b, ((width) >> 1), timg),           \
    gsDPSetTile(fmt, G_IM_SIZ_8b,                                          \
        (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), tmem,                     \
        _G_TEXLOADTILE(rtile), 0, cmt, maskt, shiftt, cms, masks, shifts), \
    gsDPLoadSyncInTexLoad                                                  \
    gsDPLoadTile(_G_TEXLOADTILE(rtile),                                    \
        (uls) << (G_TEXTURE_IMAGE_FRAC - 1),                               \
        (ult) << (G_TEXTURE_IMAGE_FRAC),                                   \
        (lrs) << (G_TEXTURE_IMAGE_FRAC - 1),                               \
        (lrt) << (G_TEXTURE_IMAGE_FRAC)),                                  \
    gsDPPipeSyncInTexLoad                                                  \
    gsDPSetTile(fmt, G_IM_SIZ_4b,                                          \
        (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), tmem,                     \
        rtile, pal, cmt, maskt, shiftt, cms, masks, shifts),               \
    gsDPSetTileSize(rtile,                                                 \
        (uls) << G_TEXTURE_IMAGE_FRAC,                                     \
        (ult) << G_TEXTURE_IMAGE_FRAC,                                     \
        (lrs) << G_TEXTURE_IMAGE_FRAC,                                     \
        (lrt) << G_TEXTURE_IMAGE_FRAC)

/**
 *  Load a 16-entry palette (for 4-bit CI textures)
 *  Assumes a 16 entry tlut is being loaded, palette # is 0-15
 *  With NO_SYNCS_IN_TEXTURE_LOADS: assumes that palette 0 is for multitexture
 *  texture 0 and palette 1 is for texture 1 (uses load tiles 5 and 4)
 */
#define gDPLoadTLUT_pal16(pkt, pal, dram)                            \
_DW({                                                                \
    gDPSetTextureImage(pkt, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dram);   \
    gDPTileSyncInTexLoad(pkt);                                       \
    gDPSetTile(pkt, 0, 0, 0, (256 + (((pal) & 0xF) * 16)),           \
                    _G_PALLOADTILE((pal) & 1), 0, 0, 0, 0, 0, 0, 0); \
    gDPLoadSyncInTexLoad(pkt);                                       \
    gDPLoadTLUTCmd(pkt, _G_PALLOADTILE((pal) & 1), 15);              \
    gDPPipeSyncInTexLoad(pkt);                                       \
})
/**
 * @copydetails gDPLoadTLUT_pal16
 */
#define gsDPLoadTLUT_pal16(pal, dram)                            \
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dram),   \
    gsDPTileSyncInTexLoad                                        \
    gsDPSetTile(0, 0, 0, (256 + (((pal) & 0xF) * 16)),           \
                _G_PALLOADTILE((pal) & 1), 0, 0, 0, 0, 0, 0, 0), \
    gsDPLoadSyncInTexLoad                                        \
    gsDPLoadTLUTCmd(_G_PALLOADTILE((pal) & 1), 15)               \
    gsDPPipeSyncEndOfTexLoad

/**
 *  Load a 256-entry palette (for 8-bit CI textures)
 *  Assumes a 256 entry tlut is being loaded, palette # is not used
 */
#define gDPLoadTLUT_pal256(pkt, dram)                                   \
_DW({                                                                   \
    gDPSetTextureImage(pkt, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dram);      \
    gDPTileSyncInTexLoad(pkt);                                          \
    gDPSetTile(pkt, 0, 0, 0, 256,                                       \
                    _G_PALLOADTILE(0), 0, 0, 0, 0, 0, 0, 0);            \
    gDPLoadSyncInTexLoad(pkt);                                          \
    gDPLoadTLUTCmd(pkt, _G_PALLOADTILE(0), 255);                        \
    gDPPipeSyncInTexLoad(pkt);                                          \
})

/**
 * @copydetails gDPLoadTLUT_pal256
 */
#define gsDPLoadTLUT_pal256(dram)                               \
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dram),  \
    gsDPTileSyncInTexLoad                                       \
    gsDPSetTile(0, 0, 0, 256,                                   \
                _G_PALLOADTILE(0), 0, 0, 0, 0, 0, 0, 0),        \
    gsDPLoadSyncInTexLoad                                       \
    gsDPLoadTLUTCmd(_G_PALLOADTILE(0), 255)                     \
    gsDPPipeSyncEndOfTexLoad

/*
 * Assumes that the starting TMEM address is calculated like in DPLoadTLUT_pal16
 * (which is the only sane way to do it if you are loading two palettes for
 * multitexture)
 */
#define _G_PALTMEMTOTILE(tmemaddr) _G_PALLOADTILE(((tmemaddr) >> 4) & 1)

#define gDPLoadTLUT(pkt, count, tmemaddr, dram)                       \
_DW({                                                                 \
    gDPSetTextureImage(pkt, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dram);    \
    gDPTileSyncInTexLoad(pkt);                                        \
    gDPSetTile(pkt, 0, 0, 0, tmemaddr,                                \
                    _G_PALTMEMTOTILE(tmemaddr), 0, 0, 0, 0, 0, 0, 0); \
    gDPLoadSyncInTexLoad(pkt);                                        \
    gDPLoadTLUTCmd(pkt, _G_PALTMEMTOTILE(tmemaddr), ((count) - 1));   \
    gDPPipeSyncInTexLoad(pkt);                                        \
})

#define gsDPLoadTLUT(count, tmemaddr, dram)                       \
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dram),    \
    gsDPTileSyncInTexLoad                                         \
    gsDPSetTile(0, 0, 0, tmemaddr,                                \
                _G_PALTMEMTOTILE(tmemaddr), 0, 0, 0, 0, 0, 0, 0), \
    gsDPLoadSyncInTexLoad                                         \
    gsDPLoadTLUTCmd(_G_PALTMEMTOTILE(tmemaddr), ((count) - 1))    \
    gsDPPipeSyncEndOfTexLoad



#define gDPSetScissor(pkt, mode, ulx, uly, lrx, lry)                \
_DW({                                                               \
    Gfx *_g = (Gfx *)pkt;                                           \
                                                                    \
    _g->words.w0 = (_SHIFTL(G_SETSCISSOR,               24,  8) |   \
                    _SHIFTL((int)((float)(ulx) * 4.0f), 12, 12) |   \
                    _SHIFTL((int)((float)(uly) * 4.0f),  0, 12));   \
    _g->words.w1 = (_SHIFTL(mode,                       24,  2) |   \
                    _SHIFTL((int)((float)(lrx) * 4.0f), 12, 12) |   \
                    _SHIFTL((int)((float)(lry) * 4.0f),  0, 12));   \
})


#define gDPSetScissorFrac(pkt, mode, ulx, uly, lrx, lry)    \
_DW({                                                       \
    Gfx *_g = (Gfx *)pkt;                                   \
                                                            \
    _g->words.w0 = (_SHIFTL(G_SETSCISSOR, 24,  8) |         \
                    _SHIFTL((int)((ulx)), 12, 12) |         \
                    _SHIFTL((int)((uly)),  0, 12));         \
    _g->words.w1 = (_SHIFTL(mode,         24,  2) |         \
                    _SHIFTL((int)((lrx)), 12, 12) |         \
                    _SHIFTL((int)((lry)),  0, 12));         \
})

#define gsDPSetScissor(mode, ulx, uly, lrx, lry)    \
{                                                   \
   (_SHIFTL(G_SETSCISSOR,               24,  8) |   \
    _SHIFTL((int)((float)(ulx) * 4.0f), 12, 12) |   \
    _SHIFTL((int)((float)(uly) * 4.0f),  0, 12)),   \
   (_SHIFTL(mode,                       24,  2) |   \
    _SHIFTL((int)((float)(lrx) * 4.0f), 12, 12) |   \
    _SHIFTL((int)((float)(lry) * 4.0f),  0, 12))    \
}

#define gsDPSetScissorFrac(mode, ulx, uly, lrx, lry)    \
{                                                       \
   (_SHIFTL(G_SETSCISSOR, 24,  8) |                     \
    _SHIFTL((int)((ulx)), 12, 12) |                     \
    _SHIFTL((int)((uly)),  0, 12)),                     \
   (_SHIFTL(mode,       24,  2) |                       \
    _SHIFTL((int)(lrx), 12, 12) |                       \
    _SHIFTL((int)(lry),  0, 12))                        \
}

/* Fraction never used in fill */
#define gDPFillRectangle(pkt, ulx, uly, lrx, lry)   \
_DW({                                               \
    Gfx *_g = (Gfx *)(pkt);                         \
                                                    \
    _g->words.w0 = (_SHIFTL(G_FILLRECT, 24,  8) |   \
                    _SHIFTL((lrx),      14, 10) |   \
                    _SHIFTL((lry),       2, 10));   \
    _g->words.w1 = (_SHIFTL((ulx), 14, 10) |        \
                    _SHIFTL((uly), 2, 10));         \
})

#define gsDPFillRectangle(ulx, uly, lrx, lry)   \
{                                               \
   (_SHIFTL(G_FILLRECT, 24,  8) |               \
    _SHIFTL((lrx),      14, 10) |               \
    _SHIFTL((lry),       2, 10)),               \
   (_SHIFTL((ulx), 14, 10) |                    \
    _SHIFTL((uly),  2, 10))                     \
}

/* like gDPFillRectangle but accepts negative arguments */
#define gDPScisFillRectangle(pkt, ulx, uly, lrx, lry)   \
_DW({                                                   \
    Gfx *_g = (Gfx *)(pkt);                             \
                                                        \
    _g->words.w0 = (_SHIFTL(G_FILLRECT,    24,  8) |    \
                    _SHIFTL(MAX((lrx), 0), 14, 10) |    \
                    _SHIFTL(MAX((lry), 0),  2, 10));    \
    _g->words.w1 = (_SHIFTL(MAX((ulx), 0), 14, 10) |    \
                    _SHIFTL(MAX((uly), 0),  2, 10));    \
})

#define gDPSetConvert(pkt, k0, k1, k2, k3, k4, k5)  \
_DW({                                               \
    Gfx *_g = (Gfx *)(pkt);                         \
                                                    \
    _g->words.w0 = (_SHIFTL(G_SETCONVERT, 24, 8) |  \
                    _SHIFTL(k0,           13, 9) |  \
                    _SHIFTL(k1,            4, 9) |  \
                    _SHIFTR(k2,            5, 4));  \
    _g->words.w1 = (_SHIFTL(k2, 27, 5) |            \
                    _SHIFTL(k3, 18, 9) |            \
                    _SHIFTL(k4,  9, 9) |            \
                    _SHIFTL(k5,  0, 9));            \
})

#define gsDPSetConvert(k0, k1, k2, k3, k4, k5)  \
{                                               \
   (_SHIFTL(G_SETCONVERT, 24, 8) |              \
    _SHIFTL(k0,           13, 9) |              \
    _SHIFTL(k1,            4, 9) |              \
    _SHIFTL(k2,            5, 4)),              \
   (_SHIFTL(k2, 27, 5) |                        \
    _SHIFTL(k3, 18, 9) |                        \
    _SHIFTL(k4,  9, 9) |                        \
    _SHIFTL(k5,  0, 9))                         \
}

#define gDPSetKeyR(pkt, cR, sR, wR)             \
_DW({                                           \
    Gfx *_g = (Gfx *)(pkt);                     \
                                                \
    _g->words.w0 = _SHIFTL(G_SETKEYR, 24, 8);   \
    _g->words.w1 = (_SHIFTL(wR, 16, 12) |       \
                    _SHIFTL(cR,  8,  8) |       \
                    _SHIFTL(sR,  0,  8));       \
})

#define gsDPSetKeyR(cR, sR, wR) \
{                               \
    _SHIFTL(G_SETKEYR, 24, 8),  \
   (_SHIFTL(wR, 16, 12) |       \
    _SHIFTL(cR,  8,  8) |       \
    _SHIFTL(sR,  0,  8))        \
}

#define gDPSetKeyGB(pkt, cG, sG, wG, cB, sB, wB)    \
_DW({                                               \
    Gfx *_g = (Gfx *)(pkt);                         \
                                                    \
    _g->words.w0 = (_SHIFTL(G_SETKEYGB, 24,  8) |   \
                    _SHIFTL(wG,         12, 12) |   \
                    _SHIFTL(wB,          0, 12));   \
    _g->words.w1 = (_SHIFTL(cG, 24, 8) |            \
                    _SHIFTL(sG, 16, 8) |            \
                    _SHIFTL(cB,  8, 8) |            \
                    _SHIFTL(sB,  0, 8));            \
})

#define gsDPSetKeyGB(cG, sG, wG, cB, sB, wB)    \
{                                               \
   (_SHIFTL(G_SETKEYGB, 24,  8) |               \
    _SHIFTL(wG,         12, 12) |               \
    _SHIFTL(wB,          0, 12)),               \
   (_SHIFTL(cG, 24,  8) |                       \
    _SHIFTL(sG, 16,  8) |                       \
    _SHIFTL(cB,  8,  8) |                       \
    _SHIFTL(sB,  0,  8))                        \
}

#define gDPNoParam(pkt, cmd)            \
_DW({                                   \
    Gfx *_g = (Gfx *)(pkt);             \
                                        \
    _g->words.w0 = _SHIFTL(cmd, 24, 8); \
    _g->words.w1 = 0;                   \
})

#define gsDPNoParam(cmd)    \
{                           \
    _SHIFTL(cmd, 24, 8),    \
    0                       \
}

#define gDPParam(pkt, cmd, param)       \
_DW({                                   \
    Gfx *_g = (Gfx *)(pkt);             \
                                        \
    _g->words.w0 = _SHIFTL(cmd, 24, 8); \
    _g->words.w1 = (param);             \
})

#define gsDPParam(cmd, param)   \
{                               \
    _SHIFTL(cmd, 24, 8),        \
    (param)                     \
}

/**
 * Notice that textured rectangles are 128-bit commands, therefore
 * gsDPTextureRectangle() should not be used in display lists
 * under normal circumstances (use gsSPTextureRectangle()).
 * That is also why there is no gDPTextureRectangle() macros.
 */
#define gsDPTextureRectangle(xl, yl, xh, yh, tile, s, t, dsdx, dtdy)    \
{                                                                       \
   (_SHIFTL(G_TEXRECT, 24,  8) |                                        \
    _SHIFTL(xh,        12, 12) |                                        \
    _SHIFTL(yh,         0, 12)),                                        \
   (_SHIFTL(tile, 24,  3) |                                             \
    _SHIFTL(xl,   12, 12) |                                             \
    _SHIFTL(yl,    0, 12)),                                             \
},                                                                      \
{                                                                       \
   (_SHIFTL(s, 16, 16) |                                                \
    _SHIFTL(t,  0, 16)),                                                \
   (_SHIFTL(dsdx, 16, 16) |                                             \
    _SHIFTL(dtdy,  0, 16))                                              \
}

/**
 * @copydetails gsDPTextureRectangle
 */
#define gDPTextureRectangle(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy)    \
_DW({                                                                       \
    Gfx *_g = (Gfx *)(pkt);                                                 \
    if (pkt);                                                               \
    _g->words.w0 = (_SHIFTL(G_TEXRECT, 24,  8) |                            \
                    _SHIFTL(xh,        12, 12) |                            \
                    _SHIFTL(yh,         0, 12));                            \
    _g->words.w1 = (_SHIFTL(tile, 24,  3) |                                 \
                    _SHIFTL(xl,   12, 12) |                                 \
                    _SHIFTL(yl,    0, 12));                                 \
    _g ++;                                                                  \
    _g->words.w0 = (_SHIFTL(s, 16, 16) |                                    \
                    _SHIFTL(t,  0, 16));                                    \
    _g->words.w1 = (_SHIFTL(dsdx, 16, 16) |                                 \
                    _SHIFTL(dtdy,  0, 16));                                 \
})

#define gsDPTextureRectangleFlip(xl, yl, xh, yh, tile, s, t, dsdx, dtdy)    \
{                                                                           \
   (_SHIFTL(G_TEXRECTFLIP, 24,  8) |                                        \
    _SHIFTL(xh,            12, 12) |                                        \
    _SHIFTL(yh,             0, 12)),                                        \
   (_SHIFTL(tile, 24,  3) |                                                 \
    _SHIFTL(xl,   12, 12) |                                                 \
    _SHIFTL(yl,    0, 12)),                                                 \
},                                                                          \
{                                                                           \
   (_SHIFTL(s, 16, 16) |                                                    \
    _SHIFTL(t,  0, 16)),                                                    \
   (_SHIFTL(dsdx, 16, 16) |                                                 \
    _SHIFTL(dtdy,  0, 16))                                                  \
}

#define gDPTextureRectangleFlip(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy)    \
_DW({                                                                           \
    Gfx *_g = (Gfx *)(pkt);                                                     \
    if (pkt);                                                                   \
    _g->words.w0 = (_SHIFTL(G_TEXRECTFLIP, 24,  8) |                            \
                    _SHIFTL(xh,            12, 12) |                            \
                    _SHIFTL(yh,             0, 12));                            \
    _g->words.w1 = (_SHIFTL(tile, 24,  3) |                                     \
                    _SHIFTL(xl,   12, 12) |                                     \
                    _SHIFTL(yl,    0, 12));                                     \
    _g ++;                                                                      \
    _g->words.w0 = (_SHIFTL(s, 16, 16) |                                        \
                    _SHIFTL(t,  0, 16));                                        \
    _g->words.w1 = (_SHIFTL(dsdx, 16, 16) |                                     \
                    _SHIFTL(dtdy,  0, 16));                                     \
})

#define gsSPTextureRectangle(xl, yl, xh, yh, tile, s, t, dsdx, dtdy)    \
   (_SHIFTL(G_TEXRECT, 24,  8) |                                        \
    _SHIFTL(xh,        12, 12) |                                        \
    _SHIFTL(yh,         0, 12)),                                        \
   (_SHIFTL(tile, 24,  3) |                                             \
    _SHIFTL(xl,   12, 12) |                                             \
    _SHIFTL(yl,    0, 12)),                                             \
   gsImmp1(G_RDPHALF_1,                                                 \
       (_SHIFTL(s, 16, 16) |                                            \
        _SHIFTL(t,  0, 16))),                                           \
   gsImmp1(G_RDPHALF_2,                                                 \
       (_SHIFTL(dsdx, 16, 16) |                                         \
        _SHIFTL(dtdy,  0, 16)))

#define gSPTextureRectangle(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy)    \
_DW({                                                                       \
    Gfx *_g = (Gfx *)(pkt);                                                 \
                                                                            \
    _g->words.w0 = (_SHIFTL(G_TEXRECT, 24,  8) |                            \
                    _SHIFTL(xh,        12, 12) |                            \
                    _SHIFTL(yh,         0, 12));                            \
    _g->words.w1 = (_SHIFTL(tile, 24,  3) |                                 \
                    _SHIFTL(xl,   12, 12) |                                 \
                    _SHIFTL(yl,    0, 12));                                 \
   gImmp1(pkt, G_RDPHALF_1,                                                 \
       (_SHIFTL(s, 16, 16) |                                                \
        _SHIFTL(t,  0, 16)));                                               \
   gImmp1(pkt, G_RDPHALF_2,                                                 \
       (_SHIFTL(dsdx, 16, 16) |                                             \
        _SHIFTL(dtdy,  0, 16)));                                            \
})

/* like gSPTextureRectangle but accepts negative position arguments */
#define gSPScisTextureRectangle(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy)        \
_DW({                                                                               \
    Gfx *_g = (Gfx *)(pkt);                                                         \
                                                                                    \
    _g->words.w0 = (_SHIFTL(G_TEXRECT,        24,  8) |                             \
                    _SHIFTL(MAX((s16)(xh),0), 12, 12) |                             \
                    _SHIFTL(MAX((s16)(yh),0),  0, 12));                             \
    _g->words.w1 = (_SHIFTL((tile),           24,  3) |                             \
                    _SHIFTL(MAX((s16)(xl),0), 12, 12) |                             \
                    _SHIFTL(MAX((s16)(yl),0),  0, 12));                             \
   gImmp1(pkt, G_RDPHALF_1,                                                         \
       (_SHIFTL(((s) -                                                              \
                   (((s16)(xl)   < 0) ?                                             \
                   (((s16)(dsdx) < 0) ?                                             \
                    (MAX((((s16)(xl) * (s16)(dsdx)) >> 7), 0))  :                   \
                    (MIN((((s16)(xl) * (s16)(dsdx)) >> 7), 0))) : 0)), 16, 16) |    \
        _SHIFTL(((t) -                                                              \
                   ((     (yl)   < 0) ?                                             \
                   (((s16)(dtdy) < 0) ?                                             \
                    (MAX((((s16)(yl) * (s16)(dtdy)) >> 7), 0))  :                   \
                    (MIN((((s16)(yl) * (s16)(dtdy)) >> 7), 0))) : 0)),  0, 16)));   \
   gImmp1(pkt, G_RDPHALF_2,                                                         \
       (_SHIFTL((dsdx), 16, 16) |                                                   \
        _SHIFTL((dtdy),  0, 16)));                                                  \
})

#define gsSPTextureRectangleFlip(xl, yl, xh, yh, tile, s, t, dsdx, dtdy)    \
   (_SHIFTL(G_TEXRECTFLIP, 24,  8) |                                        \
    _SHIFTL(xh,            12, 12) |                                        \
    _SHIFTL(yh,             0, 12)),                                        \
   (_SHIFTL(tile, 24,  3) |                                                 \
    _SHIFTL(xl,   12, 12) |                                                 \
    _SHIFTL(yl,    0, 12)),                                                 \
   gsImmp1(G_RDPHALF_1,                                                     \
       (_SHIFTL(s, 16, 16) |                                                \
        _SHIFTL(t,  0, 16))),                                               \
   gsImmp1(G_RDPHALF_2,                                                     \
       (_SHIFTL(dsdx, 16, 16) |                                             \
        _SHIFTL(dtdy,  0, 16)))

#define gSPTextureRectangleFlip(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy)    \
_DW({                                                                           \
    Gfx *_g = (Gfx *)(pkt);                                                     \
                                                                                \
    _g->words.w0 = (_SHIFTL(G_TEXRECTFLIP, 24,  8) |                            \
                    _SHIFTL(xh,            12, 12) |                            \
                    _SHIFTL(yh,             0, 12));                            \
    _g->words.w1 = (_SHIFTL(tile, 24,  3) |                                     \
                    _SHIFTL(xl,   12, 12) |                                     \
                    _SHIFTL(yl,    0, 12));                                     \
   gImmp1(pkt, G_RDPHALF_1,                                                     \
       (_SHIFTL(s, 16, 16) |                                                    \
        _SHIFTL(t,  0, 16)));                                                   \
   gImmp1(pkt, G_RDPHALF_2,                                                     \
       (_SHIFTL(dsdx, 16, 16) |                                                 \
        _SHIFTL(dtdy,  0, 16)));                                                \
})

#define gsDPWord(wordhi, wordlo)                    \
    gsImmp1(G_RDPHALF_1, (unsigned int)(wordhi)),   \
    gsImmp1(G_RDPHALF_2, (unsigned int)(wordlo))

#define gDPWord(pkt, wordhi, wordlo)                    \
_DW({                                                   \
    Gfx *_g = (Gfx *)(pkt);                             \
                                                        \
    gImmp1(pkt, G_RDPHALF_1, (unsigned int)(wordhi));   \
    gImmp1(pkt, G_RDPHALF_2, (unsigned int)(wordlo));   \
})

#define gDPFullSync(pkt)        gDPNoParam(pkt, G_RDPFULLSYNC)
#define gsDPFullSync()          gsDPNoParam(    G_RDPFULLSYNC)
#define gDPTileSync(pkt)        gDPNoParam(pkt, G_RDPTILESYNC)
#define gsDPTileSync()          gsDPNoParam(    G_RDPTILESYNC)
#define gDPPipeSync(pkt)        gDPNoParam(pkt, G_RDPPIPESYNC)
#define gsDPPipeSync()          gsDPNoParam(    G_RDPPIPESYNC)
#define gDPLoadSync(pkt)        gDPNoParam(pkt, G_RDPLOADSYNC)
#define gsDPLoadSync()          gsDPNoParam(    G_RDPLOADSYNC)
#define gDPNoOp(pkt)            gDPNoParam(pkt, G_NOOP)
#define gsDPNoOp()              gsDPNoParam(    G_NOOP)
#define gDPNoOpTag(pkt, tag)    gDPParam(pkt,   G_NOOP, tag)
#define gsDPNoOpTag(tag)        gsDPParam(      G_NOOP, tag)

#define gDPNoOpHere(pkt, file, line)        gDma1p(pkt, G_NOOP, file, line, 1)
#define gDPNoOpString(pkt, data, n)         gDma1p(pkt, G_NOOP, data, n, 2)
#define gDPNoOpWord(pkt, data, n)           gDma1p(pkt, G_NOOP, data, n, 3)
#define gDPNoOpFloat(pkt, data, n)          gDma1p(pkt, G_NOOP, data, n, 4)
#define gDPNoOpQuiet(pkt)                   gDma1p(pkt, G_NOOP, 0, 0, 5)
#define gDPNoOpVerbose(pkt, n)              gDma1p(pkt, G_NOOP, 0, n, 5)
#define gDPNoOpCallBack(pkt, callback, arg) gDma1p(pkt, G_NOOP, callback, arg, 6)
#define gDPNoOpOpenDisp(pkt, file, line)    gDma1p(pkt, G_NOOP, file, line, 7)
#define gDPNoOpCloseDisp(pkt, file, line)   gDma1p(pkt, G_NOOP, file, line, 8)
#define gDPNoOpTag3(pkt, type, data, n)     gDma1p(pkt, G_NOOP, data, n, type)

#endif /* F3DEX3_H */
