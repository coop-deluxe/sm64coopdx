#include <stdio.h>
#include "PR/gbi.h"
#include "gfx_cc.h"
#include "gfx_pc.h"

static u8 sAllowCCPrint = 1;
void gfx_cc_get_features(uint32_t shader_id, struct CCFeatures *cc_features) {
    // DO NOT COMMIT: TODO - need to fix this
    for (int32_t i = 0; i < 4; i++) {
        cc_features->c[0][i] = (shader_id >> (i * 3)) & 7;
        cc_features->c[1][i] = (shader_id >> (12 + i * 3)) & 7;
    }

    cc_features->opt_alpha = (shader_id & SHADER_OPT_ALPHA) != 0;
    cc_features->opt_fog = (shader_id & SHADER_OPT_FOG) != 0;
    cc_features->opt_texture_edge = (shader_id & SHADER_OPT_TEXTURE_EDGE) != 0;
    cc_features->opt_noise = (shader_id & SHADER_OPT_NOISE) != 0;

    cc_features->used_textures[0] = false;
    cc_features->used_textures[1] = false;
    cc_features->num_inputs = 0;

    for (int32_t i = 0; i < 2; i++) {
        for (int32_t j = 0; j < 4; j++) {
            if (cc_features->c[i][j] >= SHADER_INPUT_1 && cc_features->c[i][j] <= SHADER_INPUT_8) {
                if (cc_features->c[i][j] > cc_features->num_inputs) {
                    cc_features->num_inputs = cc_features->c[i][j];
                }
            }
            if (cc_features->c[i][j] == SHADER_TEXEL0 || cc_features->c[i][j] == SHADER_TEXEL0A) {
                cc_features->used_textures[0] = true;
            }
            if (cc_features->c[i][j] == SHADER_TEXEL1 || cc_features->c[i][j] == SHADER_TEXEL1A) {
                cc_features->used_textures[1] = true;
            }
        }
    }

    cc_features->do_single[0] = cc_features->c[0][2] == 0;
    cc_features->do_single[1] = cc_features->c[1][2] == 0;
    cc_features->do_multiply[0] = cc_features->c[0][1] == 0 && cc_features->c[0][3] == 0;
    cc_features->do_multiply[1] = cc_features->c[1][1] == 0 && cc_features->c[1][3] == 0;
    cc_features->do_mix[0] = cc_features->c[0][1] == cc_features->c[0][3];
    cc_features->do_mix[1] = cc_features->c[1][1] == cc_features->c[1][3];
    cc_features->color_alpha_same = (shader_id & 0xfff) == ((shader_id >> 12) & 0xfff);
}

void gfx_cc_print(struct ColorCombiner *cc) {
    if (!sAllowCCPrint) { return; }
    printf("\n>> gfx_pc_precomp_shader(");

    struct CombineMode* cm = &cc->cm;
    printf("0x%08x, ", cm->rgb1);
    printf("0x%08x, ", cm->alpha1);
    printf("0x%08x, ", cm->rgb2);
    printf("0x%08x, ", cm->alpha2);
    printf("0x%08x",   cm->flags);

    printf(");");
    printf("    // %016lx", cm->hash);
    printf("\n");
}

void gfx_cc_precomp(void) {
    sAllowCCPrint = 0;

    // DO NOT COMMIT - TODO - need to add an exhaustive list
    // .. need to save the cc_prints to a file if dev mode and vanilla
    // .. also what happens when we run out of ccs/shaders?
    gfx_pc_precomp_shader(0x00030001, 0x02000000, 0x000a0004, 0x0a000b0b, 0x00000011);    // 741f2ad014006ca1
    gfx_pc_precomp_shader(0x00040001, 0x00010005, 0x00040002, 0x0b020b05, 0x00000001);    // 110404410ba7b38b
    gfx_pc_precomp_shader(0x00040001, 0x00030001, 0x00040002, 0x0b030b02, 0x00000001);    // 110404410be9b307
    gfx_pc_precomp_shader(0x00040001, 0x00040001, 0x00040002, 0x0b040b02, 0x00000000);    // 0084002100596a45
    gfx_pc_precomp_shader(0x00040001, 0x00040001, 0x00040002, 0x0b040b02, 0x00000001);    // 110404410c0ab307
    gfx_pc_precomp_shader(0x00040001, 0x00040001, 0x00040002, 0x0b040b02, 0x00000005);    // 110404410c0ab30b
    gfx_pc_precomp_shader(0x00040001, 0x00050001, 0x00040002, 0x0b050b02, 0x00000001);    // 110404410c2bb307
    gfx_pc_precomp_shader(0x00040001, 0x00050001, 0x00040002, 0x0b050b02, 0x00000009);    // 110404410c2bb30f
    gfx_pc_precomp_shader(0x00040001, 0x01000000, 0x00040002, 0x02000b0b, 0x00000001);    // 110404412c86b2e6
    gfx_pc_precomp_shader(0x00040001, 0x04000000, 0x00040002, 0x04000b0b, 0x00000001);    // 110404418f86b2e6
    gfx_pc_precomp_shader(0x00040001, 0x04000000, 0x0a000000, 0x0a000b0b, 0x00000013);    // ec161ae4d6006ca3
    gfx_pc_precomp_shader(0x00040001, 0x05000000, 0x00040002, 0x05000b0b, 0x00000001);    // 11040441b086b2e6
    gfx_pc_precomp_shader(0x00040001, 0x05000000, 0x00040002, 0x05000b0b, 0x00000009);    // 11040441b086b2ee
    gfx_pc_precomp_shader(0x00040001, 0x05000000, 0x0a000000, 0x0a000b0b, 0x00000013);    // ec161b7137006ca3
    gfx_pc_precomp_shader(0x00050001, 0x00050001, 0x00050002, 0x0b050b02, 0x00000001);    // 154504410c2bb307
    gfx_pc_precomp_shader(0x00050004, 0x00050004, 0x00050004, 0x0b050b04, 0x00000001);    // 154511040c2bb36a
    gfx_pc_precomp_shader(0x01000000, 0x00050001, 0x02000000, 0x0b050b02, 0x00000001);    // 410000000c2bb307
    gfx_pc_precomp_shader(0x01000000, 0x01000000, 0x02000000, 0x02000000, 0x00000001);    // 410000002c86b2e6
    gfx_pc_precomp_shader(0x01000000, 0x01000000, 0x02000000, 0x02000b0b, 0x00000005);    // 410000002c86b2ea
    gfx_pc_precomp_shader(0x01000000, 0x01000000, 0x0a000000, 0x0a000b0b, 0x00000017);    // 0b0000beb3006ca7
    gfx_pc_precomp_shader(0x01000000, 0x04000000, 0x02000000, 0x04000b0b, 0x00000000);    // 2100000000596a45
    gfx_pc_precomp_shader(0x01000000, 0x04000000, 0x0a000000, 0x0a000b0b, 0x00000013);    // 0b000263d6006ca3
    gfx_pc_precomp_shader(0x01000000, 0x05000000, 0x02000000, 0x05000b0b, 0x00000001);    // 41000000b086b2e6
    gfx_pc_precomp_shader(0x01000000, 0x05000000, 0x0a000000, 0x0a000b0b, 0x00000013);    // 0b0002f037006ca3
    gfx_pc_precomp_shader(0x01070102, 0x01000102, 0x0a000000, 0x04000b0b, 0x00000011);    // c8c3b2bfed8de663
    gfx_pc_precomp_shader(0x04000000, 0x04000000, 0x04000000, 0x04000000, 0x00000001);    // 040000008f86b2e6
    gfx_pc_precomp_shader(0x04000000, 0x04000000, 0x04000000, 0x04000b0b, 0x00000000);    // 8400000000596a45
    gfx_pc_precomp_shader(0x04000000, 0x04000000, 0x04000000, 0x04000b0b, 0x00000005);    // 040000008f86b2ea
    gfx_pc_precomp_shader(0x04000000, 0x04000000, 0x0a000000, 0x0a000b0b, 0x00000013);    // 8e000263d6006ca3
    gfx_pc_precomp_shader(0x04000000, 0x05000000, 0x04000000, 0x05000b0b, 0x00000001);    // 04000000b086b2e6
    gfx_pc_precomp_shader(0x04000000, 0x05000000, 0x04000000, 0x05000b0b, 0x00000005);    // 04000000b086b2ea
    gfx_pc_precomp_shader(0x04000000, 0x05000000, 0x04000000, 0x05000b0b, 0x00000009);    // 04000000b086b2ee
    gfx_pc_precomp_shader(0x04060401, 0x04000000, 0x04060402, 0x04000b0b, 0x00000000);    // 84c6842100596a45
    gfx_pc_precomp_shader(0x04060401, 0x05000000, 0x04060402, 0x05000b0b, 0x00000001);    // 1d970841b086b2e6
    gfx_pc_precomp_shader(0x01000000, 0x04000000, 0x02000000, 0x04000b0b, 0x00000001);    // 410000008f86b2e6


    sAllowCCPrint = 1;
}