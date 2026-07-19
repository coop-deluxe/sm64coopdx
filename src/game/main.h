#ifndef MAIN_H
#define MAIN_H

struct RumbleData {
    u8 comm;
    u8 level;
    s16 time;
    s16 decay;
};

struct RumbleSettings {
    s16 event;
    s16 level;
    s16 timer;
    s16 count;
    s16 start;
    s16 slip;
    s16 vibrate;
    s16 decay;
};

extern OSThread D_80339210;
extern OSThread gIdleThread;
extern OSThread gMainThread;
extern OSThread gGameLoopThread;
extern OSThread gSoundThread;

extern OSMesgQueue gPIMesgQueue;
extern OSMesgQueue gIntrMesgQueue;
extern OSMesgQueue gSPTaskMesgQueue;

extern OSMesg gDmaMesgBuf[1];
extern OSMesg gPIMesgBuf[32];
extern OSMesg gSIEventMesgBuf[1];
extern OSMesg gIntrMesgBuf[16];
extern OSMesg gUnknownMesgBuf[16];
extern OSIoMesg gDmaIoMesg;
extern OSMesg D_80339BEC;
extern OSMesgQueue gDmaMesgQueue;
extern OSMesgQueue gSIEventMesgQueue;

#ifdef VERSION_SH
extern OSThread gRumblePakThread;
extern OSMesg gRumblePakSchedulerMesgBuf[1];
extern OSMesg gRumbleThreadVIMesgBuf[1];
extern OSMesgQueue gRumblePakSchedulerMesgQueue;
extern OSMesgQueue gRumbleThreadVIMesgQueue;
#endif

extern s32 gRumblePakPfs; // Actually an OSPfs but we don't have that header yet
extern struct RumbleData gRumbleDataQueue[3];
extern struct RumbleSettings gCurrRumbleSettings;

extern struct VblankHandler *gVblankHandler1;
extern struct VblankHandler *gVblankHandler2;
extern struct SPTask *gActiveSPTask;
extern u32 gNumVblanks;
extern s8 gResetTimer;
extern s8 D_8032C648;
extern s8 gDebugLevelSelect;
extern s8 D_8032C650;
extern s8 gShowProfiler;
extern s8 gShowDebugText;

void set_vblank_handler(s32 index, struct VblankHandler *handler, OSMesgQueue *queue, OSMesg *msg);
void dispatch_audio_sptask(struct SPTask *spTask);
void send_display_list(struct SPTask *spTask);

#endif // MAIN_H
