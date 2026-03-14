// SSGI Ambient Occlusion post-processing pass for sm64coopdx
// Phase 1: AO-only using GLSL 1.20 shaders, compatible with GL 2.1+

#include "gfx_ssgi.h"
#include "gfx_rendering_api.h"
#include "gfx.h"

#ifdef USE_GLES
#include <SDL2/SDL_opengles2.h>
#else
#include <SDL2/SDL_opengl.h>
#endif

#include <string.h>
#include <stdio.h>
#include <math.h>

#ifdef USE_GLES
#include <emscripten/html5.h>
#endif

// ---- Shader sources (embedded) ----

// Use #version 100 (GLSL ES 1.00) for WebGL compatibility.
// On desktop GL, #version 120 would work but ES 1.00 is a subset that works everywhere.
#ifdef USE_GLES
#define SHADER_VERSION "#version 100\n" "precision mediump float;\n"
#else
#define SHADER_VERSION "#version 120\n"
#endif

static const char *vert_src =
    SHADER_VERSION
    "attribute vec2 aPosition;\n"
    "varying vec2 vUv;\n"
    "void main() {\n"
    "    vUv = aPosition * 0.5 + 0.5;\n"
    "    gl_Position = vec4(aPosition, 0.0, 1.0);\n"
    "}\n";

static const char *ao_frag_src =
    SHADER_VERSION
    "#define PI 3.14159265\n"
    "#define HALF_PI 1.57079632\n"
    "#define SLICE_COUNT 2\n"
    "#define STEP_COUNT 6\n"
    "uniform sampler2D tDepth;\n"
    "uniform vec2 uResolution;\n"
    "uniform float uHalfProjScale;\n"
    "uniform mat4 uProjMatrixInverse;\n"
    "uniform float uCameraNear;\n"
    "uniform float uCameraFar;\n"
    "uniform float uAoIntensity;\n"
    "uniform float uRadius;\n"
    "uniform float uExpFactor;\n"
    "uniform float uThickness;\n"
    "uniform float uTemporalDirection;\n"
    "uniform float uTemporalOffset;\n"
    "uniform vec2 uProjScaleXY;\n"  // P[0][0], P[1][1]
    "varying vec2 vUv;\n"
    "float linearizeDepth(float d) {\n"
    "    float z_ndc = d * 2.0 - 1.0;\n"
    "    return (2.0 * uCameraNear * uCameraFar) / (uCameraFar + uCameraNear - z_ndc * (uCameraFar - uCameraNear));\n"
    "}\n"
    "vec3 getViewPosition(vec2 uv, float d) {\n"
    "    float z = -linearizeDepth(d);\n"  // negative: camera looks down -Z
    "    vec2 ndc = uv * 2.0 - 1.0;\n"
    "    float x = ndc.x * (-z) / uProjScaleXY.x;\n"
    "    float y = ndc.y * (-z) / uProjScaleXY.y;\n"
    "    return vec3(x, y, z);\n"
    "}\n"
    "float interleavedGradientNoise(vec2 p) {\n"
    "    return fract(52.9829189*fract(dot(p,vec2(0.06711056,0.00583715))));\n"
    "}\n"
    "float spatialOffsetsFunc(vec2 p) {\n"
    "    return 0.25*mod(floor(p.y-p.x),4.0);\n"
    "}\n"
    "float rand(vec2 co) {\n"
    "    return fract(sin(mod(dot(co,vec2(12.9898,78.233)),PI))*43758.5453);\n"
    "}\n"
    "vec3 getNormalFromDepth(vec2 uv) {\n"
    "    vec2 inv = 1.0/uResolution;\n"
    "    float c0 = texture2D(tDepth, uv).r;\n"
    "    vec3 ce = getViewPosition(uv, c0);\n"
    "    vec3 dpdx = getViewPosition(uv+vec2(inv.x,0.0), texture2D(tDepth, uv+vec2(inv.x,0.0)).r) - ce;\n"
    "    vec3 dpdy = getViewPosition(uv+vec2(0.0,inv.y), texture2D(tDepth, uv+vec2(0.0,inv.y)).r) - ce;\n"
    "    vec3 dpdxA = ce - getViewPosition(uv-vec2(inv.x,0.0), texture2D(tDepth, uv-vec2(inv.x,0.0)).r);\n"
    "    vec3 dpdyA = ce - getViewPosition(uv-vec2(0.0,inv.y), texture2D(tDepth, uv-vec2(0.0,inv.y)).r);\n"
    "    if(abs(dpdxA.z)<abs(dpdx.z)) dpdx=dpdxA;\n"
    "    if(abs(dpdyA.z)<abs(dpdy.z)) dpdy=dpdyA;\n"
    "    return normalize(cross(dpdx,dpdy));\n"
    "}\n"
    "float findMaxHorizon(vec2 ud, float R, vec3 vp, vec2 sdt, float irs, vec2 uv, vec3 vd) {\n"
    "    float sr=R*(uResolution.x/2.0)/16.0;\n"
    "    sr/=float(STEP_COUNT)+1.0;\n"
    "    float rvs=max(1.0,float(STEP_COUNT-1))*sr;\n"
    "    float mhc=-1.0;\n"
    "    for(int i=0;i<STEP_COUNT;i++) {\n"
    "        float fi=float(i);\n"
    "        float ro=sr*(fi+irs);\n"
    "        float off=pow(abs(ro/rvs),uExpFactor)*rvs;\n"
    "        vec2 uo=sdt*max(off,fi+1.0);\n"
    "        vec2 su=uv+uo*ud;\n"
    "        if(su.x<=0.0||su.y<=0.0||su.x>=1.0||su.y>=1.0) break;\n"
    "        float sd2=texture2D(tDepth,su).r;\n"
    "        vec3 sv=getViewPosition(su,sd2);\n"
    "        vec3 hd=sv-vp;\n"
    "        float hl=length(hd);\n"
    "        if(hl>0.001) {\n"
    "            float hc=dot(hd/hl,vd);\n"
    "            float fade=1.0-clamp(hl/uThickness,0.0,1.0);\n"
    "            hc=mix(-1.0,hc,fade);\n"
    "            mhc=max(mhc,hc);\n"
    "        }\n"
    "    }\n"
    "    return mhc;\n"
    "}\n"
    "void main() {\n"
    "    float depth=texture2D(tDepth,vUv).r;\n"
    "    if(depth>=1.0){gl_FragColor=vec4(1.0);return;}\n"
    "    vec3 vp=getViewPosition(vUv,depth);\n"
    "    vec3 vn=getNormalFromDepth(vUv);\n"
    "    vec3 vd=normalize(-vp);\n"
    "    vec2 sc=gl_FragCoord.xy;\n"
    "    float no=spatialOffsetsFunc(sc);\n"
    "    float nd=interleavedGradientNoise(sc);\n"
    "    float irs=fract(no+uTemporalOffset)+rand((vUv+vec2(uTemporalDirection*0.02))*2.0-1.0);\n"
    "    float ao=0.0;\n"
    "    float dbg_h1=0.0,dbg_h2=0.0,dbg_n=0.0,dbg_mhcR=0.0,dbg_mhcL=0.0;\n"
    "    for(int i=0;i<SLICE_COUNT;i++) {\n"
    "        float fi=float(i);\n"
    "        float ra=(fi+nd+uTemporalDirection)*PI/float(SLICE_COUNT);\n"
    "        vec3 sd=vec3(cos(ra),sin(ra),0.0);\n"
    "        vec2 sdt=sd.xy/uResolution;\n"
    "        vec3 pn=normalize(cross(sd,vd));\n"
    "        vec3 tn=cross(vd,pn);\n"
    "        vec3 prn=vn-pn*dot(vn,pn);\n"
    "        vec3 prnn=normalize(prn);\n"
    "        float cn=clamp(dot(prnn,vd),-1.0,1.0);\n"
    "        float n=-sign(dot(prn,tn))*acos(cn);\n"
    "        float mhcR=findMaxHorizon(vec2(1.0,1.0),uRadius,vp,sdt,irs,vUv,vd);\n"
    "        float mhcL=findMaxHorizon(vec2(-1.0,-1.0),uRadius,vp,sdt,irs,vUv,vd);\n"
    "        float h1=max(0.0,asin(clamp(mhcR,-1.0,1.0)));\n"
    "        float h2=max(0.0,asin(clamp(mhcL,-1.0,1.0)));\n"
    "        dbg_h1=h1; dbg_h2=h2; dbg_n=n; dbg_mhcR=mhcR; dbg_mhcL=mhcL;\n"
    "        ao+=0.25*(-cos(2.0*h1-n)+cos(n)+2.0*h1*sin(n));\n"
    "        ao+=0.25*(-cos(2.0*h2+n)+cos(n)-2.0*h2*sin(n));\n"
    "    }\n"
    "    ao/=float(SLICE_COUNT);\n"
    "    float vis=clamp(pow(clamp(1.0-ao,0.0,1.0),uAoIntensity),0.0,1.0);\n"
    "    // Debug: R=raw maxHorizonCos_R [-1,1]→[0,1], G=raw maxHorizonCos_L, B=raw ao, A=1\n"
    "    gl_FragColor=vec4(dbg_mhcR*0.5+0.5, dbg_mhcL*0.5+0.5, ao, 1.0);\n"
    "}\n";

static const char *composite_frag_src =
    SHADER_VERSION
    "uniform sampler2D tScene;\n"
    "uniform sampler2D tAO;\n"
    "uniform sampler2D tDepth;\n"
    "uniform vec2 uDbgResolution;\n"
    "uniform float uDbgNear;\n"
    "uniform float uDbgFar;\n"
    "uniform vec2 uDbgProjScale;\n"
    "varying vec2 vUv;\n"
    "\n"
    "float dbgLinZ(float d) {\n"
    "    float z_ndc = d * 2.0 - 1.0;\n"
    "    return (2.0*uDbgNear*uDbgFar)/(uDbgFar+uDbgNear-z_ndc*(uDbgFar-uDbgNear));\n"
    "}\n"
    "vec3 dbgVP(vec2 uv, float d) {\n"
    "    float z = -dbgLinZ(d);\n"
    "    vec2 ndc = uv*2.0-1.0;\n"
    "    return vec3(ndc.x*(-z)/uDbgProjScale.x, ndc.y*(-z)/uDbgProjScale.y, z);\n"
    "}\n"
    "vec3 dbgN(vec2 uv) {\n"
    "    vec2 inv = 1.0/uDbgResolution;\n"
    "    vec3 c = dbgVP(uv, texture2D(tDepth,uv).r);\n"
    "    vec3 dx = dbgVP(uv+vec2(inv.x,0.0), texture2D(tDepth,uv+vec2(inv.x,0.0)).r)-c;\n"
    "    vec3 dy = dbgVP(uv+vec2(0.0,inv.y), texture2D(tDepth,uv+vec2(0.0,inv.y)).r)-c;\n"
    "    return normalize(cross(dx,dy));\n"
    "}\n"
    "\n"
    "void main() {\n"
    "    vec4 scene = texture2D(tScene, vUv);\n"
    "    vec4 aoData = texture2D(tAO, vUv);\n"
    "    // R=occluded fraction, G=h1/halfpi, B=h2/halfpi\n"
    "    float vis = clamp(1.0 - aoData.r, 0.0, 1.0);\n"
    "    vec4 result = vec4(scene.rgb * vis, scene.a);\n"
    "\n"
    "    // Debug thumbnails: raw AO channels, visibility, normals\n"
    "    float thumbS = 0.15;\n"
    "    if (vUv.y < thumbS) {\n"
    "        float panel = vUv.x * 5.0;\n"
    "        int idx = int(floor(panel));\n"
    "        vec2 tuv = vec2(fract(panel), vUv.y / thumbS);\n"
    "        vec4 ad = texture2D(tAO, tuv);\n"
    "        if (idx == 0) {\n"
    "            result = vec4(vec3(ad.r), 1.0);\n"  // maxHorizonCos Right (0.5=tangent, >0.5=occluded)
    "        } else if (idx == 1) {\n"
    "            result = vec4(vec3(ad.g), 1.0);\n"  // maxHorizonCos Left
    "        } else if (idx == 2) {\n"
    "            result = vec4(vec3(ad.b), 1.0);\n"  // Raw ao (occluded fraction)
    "        } else if (idx == 3) {\n"
    "            result = vec4(vec3(1.0-ad.b), 1.0);\n"  // Visibility (1-ao)
    "        } else {\n"
    "            result = vec4(dbgN(tuv)*0.5+0.5, 1.0);\n"  // Normals
    "        }\n"
    "    } else if (vUv.x > (1.0 - thumbS*2.0) && vUv.x <= (1.0 - thumbS) && vUv.y < thumbS*2.0) {\n"
    "        vec2 tuv = vec2((vUv.x-(1.0-thumbS*2.0))/thumbS, (vUv.y-thumbS)/thumbS);\n"
    "        result = vec4(dbgN(tuv)*0.5+0.5, 1.0);\n"
    "    }\n"
    "\n"
    "    gl_FragColor = result;\n"
    "}\n";

// ---- State ----

static bool ssgi_initialized = false;
static bool ssgi_enabled = true;

// Tunable parameters (unsigned int × 10 for DJUI slider compatibility)
unsigned int gSSGI_AoIntensity = 15;  // ÷10 → 1.5
unsigned int gSSGI_Radius      = 15;  // ÷10 → 1.5
unsigned int gSSGI_Thickness   = 3;   // ÷10 → 0.3
unsigned int gSSGI_Enabled     = 0;   // 0=off, 1=on (disabled by default)

static GLuint ssgi_scene_fbo;
static GLuint ssgi_scene_color_tex;
static GLuint ssgi_scene_depth_tex;
static GLuint ssgi_ao_fbo;
static GLuint ssgi_ao_tex;
static int ssgi_width = 0, ssgi_height = 0;

static GLuint ssgi_quad_vbo;
static GLuint ssgi_ao_program;
static GLuint ssgi_composite_program;

// AO program uniforms
static GLint loc_ao_tDepth, loc_ao_uResolution, loc_ao_uHalfProjScale;
static GLint loc_ao_uProjMatrixInverse, loc_ao_uCameraNear, loc_ao_uCameraFar, loc_ao_uProjScaleXY;
static GLint loc_ao_uAoIntensity, loc_ao_uRadius, loc_ao_uExpFactor, loc_ao_uThickness;
static GLint loc_ao_uTemporalDirection, loc_ao_uTemporalOffset;

// Composite program uniforms
static GLint loc_comp_tScene, loc_comp_tAO, loc_comp_tDepth, loc_comp_uDbgResolution, loc_comp_uDbgNear, loc_comp_uDbgFar, loc_comp_uDbgProjScale;

// Projection parameters from rendering_graph_node.c
static float ssgi_proj_matrix[4][4];
static bool ssgi_proj_valid = false;
static float ssgi_near = 100.0f, ssgi_far = 12800.0f;
static float ssgi_fov = 45.0f, ssgi_aspect = 1.333f;
static bool ssgi_persp_valid = false;
static bool ssgi_scene_fbo_bound = false;
static uint32_t ssgi_frame_count = 0;

// ---- Helpers ----

static GLuint compile_shader(GLenum type, const char *src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, NULL);
    glCompileShader(s);
    GLint ok;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetShaderInfoLog(s, sizeof(log), NULL, log);
        printf("[SSGI] Shader compile error: %s\n", log);
    }
    return s;
}

static GLuint link_program(const char *vsrc, const char *fsrc) {
    GLuint vs = compile_shader(GL_VERTEX_SHADER, vsrc);
    GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fsrc);
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glBindAttribLocation(prog, 0, "aPosition");
    glLinkProgram(prog);
    GLint ok;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetProgramInfoLog(prog, sizeof(log), NULL, log);
        printf("[SSGI] Program link error: %s\n", log);
    }
    glDeleteShader(vs);
    glDeleteShader(fs);
    return prog;
}

static void invert_matrix(const float m[16], float inv[16]) {
    // Generic 4x4 matrix inversion
    float t[16];
    float det;
    t[0]  =  m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15] + m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
    t[4]  = -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15] - m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
    t[8]  =  m[4]*m[9]*m[15]  - m[4]*m[11]*m[13] - m[8]*m[5]*m[15] + m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
    t[12] = -m[4]*m[9]*m[14]  + m[4]*m[10]*m[13] + m[8]*m[5]*m[14] - m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];
    t[1]  = -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15] - m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
    t[5]  =  m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15] + m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
    t[9]  = -m[0]*m[9]*m[15]  + m[0]*m[11]*m[13] + m[8]*m[1]*m[15] - m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
    t[13] =  m[0]*m[9]*m[14]  - m[0]*m[10]*m[13] - m[8]*m[1]*m[14] + m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];
    t[2]  =  m[1]*m[6]*m[15]  - m[1]*m[7]*m[14]  - m[5]*m[2]*m[15] + m[5]*m[3]*m[14] + m[13]*m[2]*m[7]  - m[13]*m[3]*m[6];
    t[6]  = -m[0]*m[6]*m[15]  + m[0]*m[7]*m[14]  + m[4]*m[2]*m[15] - m[4]*m[3]*m[14] - m[12]*m[2]*m[7]  + m[12]*m[3]*m[6];
    t[10] =  m[0]*m[5]*m[15]  - m[0]*m[7]*m[13]  - m[4]*m[1]*m[15] + m[4]*m[3]*m[13] + m[12]*m[1]*m[7]  - m[12]*m[3]*m[5];
    t[14] = -m[0]*m[5]*m[14]  + m[0]*m[6]*m[13]  + m[4]*m[1]*m[14] - m[4]*m[2]*m[13] - m[12]*m[1]*m[6]  + m[12]*m[2]*m[5];
    t[3]  = -m[1]*m[6]*m[11]  + m[1]*m[7]*m[10]  + m[5]*m[2]*m[11] - m[5]*m[3]*m[10] - m[9]*m[2]*m[7]   + m[9]*m[3]*m[6];
    t[7]  =  m[0]*m[6]*m[11]  - m[0]*m[7]*m[10]  - m[4]*m[2]*m[11] + m[4]*m[3]*m[10] + m[8]*m[2]*m[7]   - m[8]*m[3]*m[6];
    t[11] = -m[0]*m[5]*m[11]  + m[0]*m[7]*m[9]   + m[4]*m[1]*m[11] - m[4]*m[3]*m[9]  - m[8]*m[1]*m[7]   + m[8]*m[3]*m[5];
    t[15] =  m[0]*m[5]*m[10]  - m[0]*m[6]*m[9]   - m[4]*m[1]*m[10] + m[4]*m[2]*m[9]  + m[8]*m[1]*m[6]   - m[8]*m[2]*m[5];
    det = m[0]*t[0] + m[1]*t[4] + m[2]*t[8] + m[3]*t[12];
    if (fabsf(det) < 1e-10f) { memcpy(inv, m, 16 * sizeof(float)); return; }
    det = 1.0f / det;
    for (int i = 0; i < 16; i++) inv[i] = t[i] * det;
}

// ---- FBO setup ----

static void ssgi_create_fbos(int w, int h) {
    ssgi_width = w;
    ssgi_height = h;

    // Scene FBO
    glGenFramebuffers(1, &ssgi_scene_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, ssgi_scene_fbo);

    glGenTextures(1, &ssgi_scene_color_tex);
    glBindTexture(GL_TEXTURE_2D, ssgi_scene_color_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssgi_scene_color_tex, 0);

    glGenTextures(1, &ssgi_scene_depth_tex);
    glBindTexture(GL_TEXTURE_2D, ssgi_scene_depth_tex);
#ifdef USE_GLES
    // WebGL 2 / GLES 3: use GL_DEPTH_COMPONENT24 (0x81A6) as internal format
    // This is core in WebGL 2 and doesn't need the depth texture extension.
    #ifndef GL_DEPTH_COMPONENT24
    #define GL_DEPTH_COMPONENT24 0x81A6
    #endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
#else
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
#endif
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ssgi_scene_depth_tex, 0);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        printf("[SSGI] Scene FBO incomplete: 0x%x — disabling SSGI\n", status);
        ssgi_enabled = false;
    }

    // AO FBO
    glGenFramebuffers(1, &ssgi_ao_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, ssgi_ao_fbo);

    glGenTextures(1, &ssgi_ao_tex);
    glBindTexture(GL_TEXTURE_2D, ssgi_ao_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssgi_ao_tex, 0);

    status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        printf("[SSGI] AO FBO incomplete: 0x%x — disabling SSGI\n", status);
        ssgi_enabled = false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

static void ssgi_destroy_fbos(void) {
    if (ssgi_scene_fbo) { glDeleteFramebuffers(1, &ssgi_scene_fbo); ssgi_scene_fbo = 0; }
    if (ssgi_scene_color_tex) { glDeleteTextures(1, &ssgi_scene_color_tex); ssgi_scene_color_tex = 0; }
    if (ssgi_scene_depth_tex) { glDeleteTextures(1, &ssgi_scene_depth_tex); ssgi_scene_depth_tex = 0; }
    if (ssgi_ao_fbo) { glDeleteFramebuffers(1, &ssgi_ao_fbo); ssgi_ao_fbo = 0; }
    if (ssgi_ao_tex) { glDeleteTextures(1, &ssgi_ao_tex); ssgi_ao_tex = 0; }
}

// ---- Public API ----

void ssgi_init(void) {
    if (ssgi_initialized) return;

#ifdef USE_GLES
    // WebGL 1 requires WEBGL_depth_texture extension for depth texture FBO attachments.
    // WebGL 2 has depth textures as core — no extension needed.
    // Try to enable the extension; if it fails, we may be on WebGL 2 where it's built-in.
    {
        EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_get_current_context();
        EM_BOOL hasExt = emscripten_webgl_enable_extension(ctx, "WEBGL_depth_texture");
        if (!hasExt) hasExt = emscripten_webgl_enable_extension(ctx, "OES_depth_texture");

        // Check WebGL version — if 2+, depth textures are core
        int webglVersion = EM_ASM_INT({
            var c = document.getElementById('canvas');
            var gl = c.getContext('webgl2');
            return gl ? 2 : 1;
        });

        if (!hasExt && webglVersion < 2) {
            printf("[SSGI] Depth texture extension not available and WebGL < 2 — disabling SSGI\n");
            ssgi_enabled = false;
            return;
        }
        printf("[SSGI] Depth textures available (WebGL %d)\n", webglVersion);
    }
#endif

    // Compile shaders
    ssgi_ao_program = link_program(vert_src, ao_frag_src);
    ssgi_composite_program = link_program(vert_src, composite_frag_src);

    if (!ssgi_ao_program || !ssgi_composite_program) {
        printf("[SSGI] Shader compilation failed — disabling SSGI\n");
        ssgi_enabled = false;
        return;
    }

    // Cache uniform locations
    loc_ao_tDepth = glGetUniformLocation(ssgi_ao_program, "tDepth");
    loc_ao_uResolution = glGetUniformLocation(ssgi_ao_program, "uResolution");
    loc_ao_uHalfProjScale = glGetUniformLocation(ssgi_ao_program, "uHalfProjScale");
    loc_ao_uProjMatrixInverse = glGetUniformLocation(ssgi_ao_program, "uProjMatrixInverse");
    loc_ao_uProjScaleXY = glGetUniformLocation(ssgi_ao_program, "uProjScaleXY");
    loc_ao_uCameraNear = glGetUniformLocation(ssgi_ao_program, "uCameraNear");
    loc_ao_uCameraFar = glGetUniformLocation(ssgi_ao_program, "uCameraFar");
    loc_ao_uAoIntensity = glGetUniformLocation(ssgi_ao_program, "uAoIntensity");
    loc_ao_uRadius = glGetUniformLocation(ssgi_ao_program, "uRadius");
    loc_ao_uExpFactor = glGetUniformLocation(ssgi_ao_program, "uExpFactor");
    loc_ao_uThickness = glGetUniformLocation(ssgi_ao_program, "uThickness");
    loc_ao_uTemporalDirection = glGetUniformLocation(ssgi_ao_program, "uTemporalDirection");
    loc_ao_uTemporalOffset = glGetUniformLocation(ssgi_ao_program, "uTemporalOffset");

    loc_comp_tScene = glGetUniformLocation(ssgi_composite_program, "tScene");
    loc_comp_tAO = glGetUniformLocation(ssgi_composite_program, "tAO");
    loc_comp_tDepth = glGetUniformLocation(ssgi_composite_program, "tDepth");
    loc_comp_uDbgResolution = glGetUniformLocation(ssgi_composite_program, "uDbgResolution");
    loc_comp_uDbgNear = glGetUniformLocation(ssgi_composite_program, "uDbgNear");
    loc_comp_uDbgFar = glGetUniformLocation(ssgi_composite_program, "uDbgFar");
    loc_comp_uDbgProjScale = glGetUniformLocation(ssgi_composite_program, "uDbgProjScale");

    // Fullscreen quad VBO — save/restore existing VBO binding
    GLint prev_vbo;
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &prev_vbo);
    float quad[] = { -1, -1,  1, -1,  -1, 1,  1, 1 };
    glGenBuffers(1, &ssgi_quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, ssgi_quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, prev_vbo);

    ssgi_initialized = true;
    printf("[SSGI] Initialized (AO-only, GLSL 1.20)\n");
}

void ssgi_resize(int width, int height) {
    if (width <= 0 || height <= 0) return;
    if (width == ssgi_width && height == ssgi_height) return;
    ssgi_destroy_fbos();
    ssgi_create_fbos(width, height);
    printf("[SSGI] Resized to %dx%d\n", width, height);
}

void ssgi_start_frame(void) {
    if (!ssgi_enabled || !ssgi_initialized || !gSSGI_Enabled) return;

    // Ensure FBOs match current window size
    int w = gfx_current_dimensions.width;
    int h = gfx_current_dimensions.height;
    if (w > 0 && h > 0 && (w != ssgi_width || h != ssgi_height)) {
        ssgi_resize(w, h);
    }

    // After resize, check if SSGI was disabled due to FBO failure
    if (!ssgi_enabled) return;
    if (ssgi_width <= 0 || ssgi_height <= 0) return;
    if (!ssgi_scene_fbo) return;

    // Redirect rendering into the scene FBO
    glBindFramebuffer(GL_FRAMEBUFFER, ssgi_scene_fbo);
    ssgi_scene_fbo_bound = true;
}

static void draw_fullscreen_quad(void) {
    glBindBuffer(GL_ARRAY_BUFFER, ssgi_quad_vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(0);
}

void ssgi_render(void) {
    if (!ssgi_enabled || !ssgi_initialized || !gSSGI_Enabled || !ssgi_persp_valid) return;
    if (ssgi_width <= 0 || ssgi_height <= 0) return;

    ssgi_frame_count++;

    // Debug: print projection matrix once
    static bool printed_matrix = false;
    if (!printed_matrix) {
        printed_matrix = true;
        printf("[SSGI] Projection matrix (row-major P[row][col]):\n");
        for (int r = 0; r < 4; r++) {
            printf("[SSGI]   [%f, %f, %f, %f]\n",
                ssgi_proj_matrix[r][0], ssgi_proj_matrix[r][1],
                ssgi_proj_matrix[r][2], ssgi_proj_matrix[r][3]);
        }
        printf("[SSGI] P[2][2]=%f P[2][3]=%f P[3][2]=%f\n",
            ssgi_proj_matrix[2][2], ssgi_proj_matrix[2][3], ssgi_proj_matrix[3][2]);
        float dbg_P22 = ssgi_proj_matrix[2][2];
        float dbg_P32 = ssgi_proj_matrix[3][2];
        float dbg_near = dbg_P32 / (dbg_P22 - 1.0f);
        float dbg_far  = dbg_P32 / (dbg_P22 + 1.0f);
        printf("[SSGI] Extracted near=%f far=%f\n", dbg_near, dbg_far);
        printf("[SSGI] P[0][0]=%f P[1][1]=%f (xy projection scales)\n",
            ssgi_proj_matrix[0][0], ssgi_proj_matrix[1][1]);
    }

    // Save GL state
    GLint prev_fbo, prev_program, prev_vbo;
    GLboolean prev_depth_test, prev_scissor, prev_blend;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prev_fbo);
    glGetIntegerv(GL_CURRENT_PROGRAM, &prev_program);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &prev_vbo);
    prev_depth_test = glIsEnabled(GL_DEPTH_TEST);
    prev_scissor = glIsEnabled(GL_SCISSOR_TEST);
    prev_blend = glIsEnabled(GL_BLEND);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_BLEND);

    // Use perspective parameters captured from rendering_graph_node.c
    float cam_near = ssgi_near;
    float cam_far  = ssgi_far;
    float fov_rad  = ssgi_fov * 3.14159265f / 180.0f;
    float aspect   = ssgi_aspect > 0.01f ? ssgi_aspect : ((float)ssgi_width / (float)ssgi_height);
    float proj_y   = 1.0f / tanf(fov_rad * 0.5f);
    float proj_x   = proj_y / aspect;
    float half_proj_scale = (float)ssgi_height * proj_y * 0.5f;

    // Also compute inverse projection matrix for potential future use
    float inv_proj[16];
    invert_matrix((const float *)ssgi_proj_matrix, inv_proj);

    // Temporal noise
    static const float temporal_rotations[] = {60, 300, 180, 240, 120, 0};
    static const float spatial_offsets[] = {0, 0.5f, 0.25f, 0.75f};
    float temp_dir = temporal_rotations[ssgi_frame_count % 6] / 360.0f;
    float temp_off = spatial_offsets[ssgi_frame_count % 4];

    // --- AO pass ---
    glBindFramebuffer(GL_FRAMEBUFFER, ssgi_ao_fbo);
    glViewport(0, 0, ssgi_width, ssgi_height);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(ssgi_ao_program);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ssgi_scene_depth_tex);
    glUniform1i(loc_ao_tDepth, 0);

    glUniform2f(loc_ao_uResolution, (float)ssgi_width, (float)ssgi_height);
    glUniform2f(loc_ao_uProjScaleXY, proj_x, proj_y);
    glUniform1f(loc_ao_uCameraNear, cam_near);
    glUniform1f(loc_ao_uCameraFar, cam_far);
    glUniform1f(loc_ao_uHalfProjScale, half_proj_scale);
    glUniform1f(loc_ao_uAoIntensity, (float)gSSGI_AoIntensity / 10.0f);
    glUniform1f(loc_ao_uRadius, (float)gSSGI_Radius / 10.0f);
    glUniform1f(loc_ao_uExpFactor, 2.0f);
    glUniform1f(loc_ao_uThickness, (float)gSSGI_Thickness * 50.0f);  // N64 scale: 50-1000 units
    glUniform1f(loc_ao_uTemporalDirection, temp_dir);
    glUniform1f(loc_ao_uTemporalOffset, temp_off);

    draw_fullscreen_quad();

    // Restore state
    glBindFramebuffer(GL_FRAMEBUFFER, prev_fbo);
    glUseProgram(prev_program);
    glBindBuffer(GL_ARRAY_BUFFER, prev_vbo);
    if (prev_depth_test) glEnable(GL_DEPTH_TEST);
    if (prev_scissor) glEnable(GL_SCISSOR_TEST);
    if (prev_blend) glEnable(GL_BLEND);
}

void ssgi_composite(void) {
    if (!ssgi_enabled || !ssgi_initialized || !gSSGI_Enabled || !ssgi_persp_valid) return;
    if (ssgi_width <= 0 || ssgi_height <= 0) return;

    // Save state
    GLint prev_program, prev_vbo;
    GLboolean prev_depth_test, prev_scissor, prev_blend;
    glGetIntegerv(GL_CURRENT_PROGRAM, &prev_program);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &prev_vbo);
    prev_depth_test = glIsEnabled(GL_DEPTH_TEST);
    prev_scissor = glIsEnabled(GL_SCISSOR_TEST);
    prev_blend = glIsEnabled(GL_BLEND);

    // Render to default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, ssgi_width, ssgi_height);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_BLEND);

    glUseProgram(ssgi_composite_program);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ssgi_scene_color_tex);
    glUniform1i(loc_comp_tScene, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, ssgi_ao_tex);
    glUniform1i(loc_comp_tAO, 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, ssgi_scene_depth_tex);
    glUniform1i(loc_comp_tDepth, 2);

    glUniform2f(loc_comp_uDbgResolution, (float)ssgi_width, (float)ssgi_height);
    {
        float dfov = ssgi_fov * 3.14159265f / 180.0f;
        float dasp = ssgi_aspect > 0.01f ? ssgi_aspect : ((float)ssgi_width / (float)ssgi_height);
        float dpy = 1.0f / tanf(dfov * 0.5f);
        glUniform2f(loc_comp_uDbgProjScale, dpy / dasp, dpy);
    }
    glUniform1f(loc_comp_uDbgNear, ssgi_near);
    glUniform1f(loc_comp_uDbgFar, ssgi_far);

    draw_fullscreen_quad();

    // Restore state
    glUseProgram(prev_program);
    glBindBuffer(GL_ARRAY_BUFFER, prev_vbo);
    if (prev_depth_test) glEnable(GL_DEPTH_TEST);
    if (prev_scissor) glEnable(GL_SCISSOR_TEST);
    if (prev_blend) glEnable(GL_BLEND);
}

void ssgi_set_projection_matrix(const float mtx[4][4]) {
    memcpy(ssgi_proj_matrix, mtx, sizeof(ssgi_proj_matrix));
    ssgi_proj_valid = true;
}

void ssgi_set_perspective(float near, float far, float fov, float aspect) {
    ssgi_near = near;
    ssgi_far = far;
    ssgi_fov = fov;
    ssgi_aspect = aspect;
    ssgi_persp_valid = true;
}

void ssgi_on_ortho_switch(void) {
    // Called when the display list switches from perspective to ortho projection.
    // Flush pending 3D geometry, run SSGI, composite to default FB.
    // Then remaining draws (UI) go directly to default FB without AO.
    if (!ssgi_scene_fbo_bound || !ssgi_enabled || !gSSGI_Enabled) return;

    extern void gfx_flush(void);
    gfx_flush();
    ssgi_render();
    ssgi_composite();
    ssgi_scene_fbo_bound = false;
    // Remaining UI draws now go to default framebuffer (0)
}

bool ssgi_is_enabled(void) {
    return ssgi_enabled && ssgi_initialized;
}
