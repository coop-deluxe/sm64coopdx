#ifndef miniaudio_sdl_inl
#define miniaudio_sdl_inl

/* Support SDL on everything. */
#define MA_SUPPORT_SDL

/*
Only enable SDL if it's hasn't been explicitly disabled (MA_NO_SDL) or enabled (MA_ENABLE_SDL with
MA_ENABLE_ONLY_SPECIFIC_BACKENDS) and it's supported at compile time (MA_SUPPORT_SDL).
*/
#if defined(MA_SUPPORT_SDL) && !defined(MA_NO_SDL) && (!defined(MA_ENABLE_ONLY_SPECIFIC_BACKENDS) || defined(MA_ENABLE_SDL))
    #define MA_HAS_SDL
#endif

#if defined(MA_HAS_SDL)
    /* SDL headers are necessary if using compile-time linking. */
    #ifdef MA_NO_RUNTIME_LINKING
        #ifdef __has_include
            #ifdef MA_EMSCRIPTEN
                #if !__has_include(<SDL/SDL_audio.h>)
                    #undef MA_HAS_SDL
                #endif
            #else
                #if !__has_include(<SDL2/SDL_audio.h>)
                    #undef MA_HAS_SDL
                #endif
            #endif
        #endif
    #endif
#endif

typedef struct {
    ma_context context; /* Make this the first member so we can cast between ma_context and ma_context_sdl. */
#if defined(MA_SUPPORT_SDL)
    struct {
        ma_handle hSDL; /* A handle to the SDL2 shared object. We dynamically load function pointers at runtime so we can avoid linking. */
        ma_proc SDL_InitSubSystem;
        ma_proc SDL_QuitSubSystem;
        ma_proc SDL_GetNumAudioDevices;
        ma_proc SDL_GetAudioDeviceName;
        ma_proc SDL_CloseAudioDevice;
        ma_proc SDL_OpenAudioDevice;
        ma_proc SDL_PauseAudioDevice;
    } sdl;
#endif
} ma_context_sdl;

typedef struct {
    ma_device device;   /* Make this the first member so we can cast between ma_device and ma_device_sdl. */
#if defined(MA_SUPPORT_SDL)
    struct {
        int deviceIDPlayback;
        int deviceIDCapture;
    } sdl;
#endif
} ma_device_sdl;

#if defined(MA_HAS_SDL)
#define MA_SDL_INIT_AUDIO                       0x00000010
#define MA_AUDIO_U8                             0x0008
#define MA_AUDIO_S16                            0x8010
#define MA_AUDIO_S32                            0x8020
#define MA_AUDIO_F32                            0x8120
#define MA_SDL_AUDIO_ALLOW_FREQUENCY_CHANGE     0x00000001
#define MA_SDL_AUDIO_ALLOW_FORMAT_CHANGE        0x00000002
#define MA_SDL_AUDIO_ALLOW_CHANNELS_CHANGE      0x00000004
#define MA_SDL_AUDIO_ALLOW_ANY_CHANGE           (MA_SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | MA_SDL_AUDIO_ALLOW_FORMAT_CHANGE | MA_SDL_AUDIO_ALLOW_CHANNELS_CHANGE)

ma_result ma_context_init__sdl(ma_context *pContext, const ma_context_config *pConfig, ma_backend_callbacks *pCallbacks);
ma_result ma_context_uninit__sdl(ma_context *pContext);
ma_result ma_device_init__sdl(ma_device *pDevice, const ma_device_config *pConfig, ma_device_descriptor *pDescriptorPlayback, ma_device_descriptor *pDescriptorCapture);
ma_result ma_device_uninit__sdl(ma_device *pDevice);
ma_result ma_device_start__sdl(ma_device *pDevice);
ma_result ma_device_stop__sdl(ma_device *pDevice);

ma_result ma_context_enumerate_devices__sdl(ma_context *pContext, ma_enum_devices_callback_proc callback, void *pUserData);
ma_result ma_context_get_device_info__sdl(ma_context *pContext, ma_device_type deviceType, const ma_device_id *pDeviceID, ma_device_info *pDeviceInfo);

#endif // MA_HAS_SDL

#if defined(MA_HAS_SDL)

/* If we are linking at compile time we'll just #include SDL.h. Otherwise we can just redeclare some stuff to avoid the need for development packages to be installed. */
#ifdef MA_NO_RUNTIME_LINKING
    #define SDL_MAIN_HANDLED
    #ifdef MA_EMSCRIPTEN
        #include <SDL/SDL.h>
    #else
        #include <SDL2/SDL.h>
    #endif

    typedef SDL_AudioCallback   MA_SDL_AudioCallback;
    typedef SDL_AudioSpec       MA_SDL_AudioSpec;
    typedef SDL_AudioFormat     MA_SDL_AudioFormat;
    typedef SDL_AudioDeviceID   MA_SDL_AudioDeviceID;
#else
    typedef void (* MA_SDL_AudioCallback)(void* userdata, ma_uint8* stream, int len);
    typedef ma_uint16 MA_SDL_AudioFormat;
    typedef ma_uint32 MA_SDL_AudioDeviceID;

    typedef struct MA_SDL_AudioSpec
    {
        int freq;
        MA_SDL_AudioFormat format;
        ma_uint8 channels;
        ma_uint8 silence;
        ma_uint16 samples;
        ma_uint16 padding;
        ma_uint32 size;
        MA_SDL_AudioCallback callback;
        void* userdata;
    } MA_SDL_AudioSpec;
#endif

typedef int                  (* MA_PFN_SDL_InitSubSystem)(ma_uint32 flags);
typedef void                 (* MA_PFN_SDL_QuitSubSystem)(ma_uint32 flags);
typedef int                  (* MA_PFN_SDL_GetNumAudioDevices)(int iscapture);
typedef const char*          (* MA_PFN_SDL_GetAudioDeviceName)(int index, int iscapture);
typedef void                 (* MA_PFN_SDL_CloseAudioDevice)(MA_SDL_AudioDeviceID dev);
typedef MA_SDL_AudioDeviceID (* MA_PFN_SDL_OpenAudioDevice)(const char* device, int iscapture, const MA_SDL_AudioSpec* desired, MA_SDL_AudioSpec* obtained, int allowed_changes);
typedef void                 (* MA_PFN_SDL_PauseAudioDevice)(MA_SDL_AudioDeviceID dev, int pause_on);

MA_SDL_AudioFormat ma_format_to_sdl(ma_format format) {
    switch (format)
    {
        case ma_format_unknown: return 0;
        case ma_format_u8:      return MA_AUDIO_U8;
        case ma_format_s16:     return MA_AUDIO_S16;
        case ma_format_s24:     return MA_AUDIO_S32;  /* Closest match. */
        case ma_format_s32:     return MA_AUDIO_S32;
        case ma_format_f32:     return MA_AUDIO_F32;
        default:                return 0;
    }
}

ma_format ma_format_from_sdl(MA_SDL_AudioFormat format) {
    switch (format)
    {
        case MA_AUDIO_U8:  return ma_format_u8;
        case MA_AUDIO_S16: return ma_format_s16;
        case MA_AUDIO_S32: return ma_format_s32;
        case MA_AUDIO_F32: return ma_format_f32;
        default:           return ma_format_unknown;
    }
}

ma_result ma_context_enumerate_devices__sdl(ma_context *pContext, ma_enum_devices_callback_proc callback, void* pUserData) {
    ma_context_sdl *pContextEx = (ma_context_sdl *)pContext;
    ma_bool32 isTerminated = MA_FALSE;

    /* Playback */
    if (!isTerminated) {
        int deviceCount = ((MA_PFN_SDL_GetNumAudioDevices)pContextEx->sdl.SDL_GetNumAudioDevices)(0);
        for (int iDevice = 0; iDevice < deviceCount; ++iDevice) {
            ma_device_info deviceInfo;
            MA_ZERO_OBJECT(&deviceInfo);

            deviceInfo.id.custom.i = iDevice;
            ma_strncpy_s(deviceInfo.name, sizeof(deviceInfo.name), ((MA_PFN_SDL_GetAudioDeviceName)pContextEx->sdl.SDL_GetAudioDeviceName)(iDevice, 0), (size_t)-1);

            if (iDevice == 0) {
                deviceInfo.isDefault = MA_TRUE;
            }

            ma_bool32 cbResult = callback(pContext, ma_device_type_playback, &deviceInfo, pUserData);
            if (cbResult == MA_FALSE) {
                isTerminated = MA_TRUE;
                break;
            }
        }
    }

    /* Capture */
    if (!isTerminated) {
        int deviceCount = ((MA_PFN_SDL_GetNumAudioDevices)pContextEx->sdl.SDL_GetNumAudioDevices)(1);
        for (int iDevice = 0; iDevice < deviceCount; ++iDevice) {
            ma_device_info deviceInfo;
            MA_ZERO_OBJECT(&deviceInfo);

            deviceInfo.id.custom.i = iDevice;
            ma_strncpy_s(deviceInfo.name, sizeof(deviceInfo.name), ((MA_PFN_SDL_GetAudioDeviceName)pContextEx->sdl.SDL_GetAudioDeviceName)(iDevice, 1), (size_t)-1);

            if (iDevice == 0) {
                deviceInfo.isDefault = MA_TRUE;
            }

            ma_bool32 cbResult = callback(pContext, ma_device_type_capture, &deviceInfo, pUserData);
            if (cbResult == MA_FALSE) {
                isTerminated = MA_TRUE;
                break;
            }
        }
    }

    return MA_SUCCESS;
}

ma_result ma_context_get_device_info__sdl(ma_context *pContext, ma_device_type deviceType, const ma_device_id *pDeviceID, ma_device_info *pDeviceInfo) {
    ma_context_sdl *pContextEx = (ma_context_sdl *)pContext;

#if !defined(__EMSCRIPTEN__)
    MA_SDL_AudioSpec desiredSpec;
    MA_SDL_AudioSpec obtainedSpec;
    MA_SDL_AudioDeviceID tempDeviceID;
    const char* pDeviceName;
#endif

    if (pDeviceID == NULL) {
        if (deviceType == ma_device_type_playback) {
            pDeviceInfo->id.custom.i = 0;
            ma_strncpy_s(pDeviceInfo->name, sizeof(pDeviceInfo->name), MA_DEFAULT_PLAYBACK_DEVICE_NAME, (size_t)-1);
        } else {
            pDeviceInfo->id.custom.i = 0;
            ma_strncpy_s(pDeviceInfo->name, sizeof(pDeviceInfo->name), MA_DEFAULT_CAPTURE_DEVICE_NAME, (size_t)-1);
        }
    } else {
        pDeviceInfo->id.custom.i = pDeviceID->custom.i;
        ma_strncpy_s(pDeviceInfo->name, sizeof(pDeviceInfo->name), ((MA_PFN_SDL_GetAudioDeviceName)pContextEx->sdl.SDL_GetAudioDeviceName)(pDeviceID->custom.i, (deviceType == ma_device_type_playback) ? 0 : 1), (size_t)-1);
    }

    if (pDeviceInfo->id.custom.i == 0) {
        pDeviceInfo->isDefault = MA_TRUE;
    }

    /*
    To get an accurate idea on the backend's native format we need to open the device. Not ideal, but it's the only way. An
    alternative to this is to report all channel counts, sample rates and formats, but that doesn't offer a good representation
    of the device's _actual_ ideal format.
    
    Note: With Emscripten, it looks like non-zero values need to be specified for desiredSpec. Whatever is specified in
    desiredSpec will be used by SDL since it uses it just does its own format conversion internally. Therefore, from what
    I can tell, there's no real way to know the device's actual format which means I'm just going to fall back to the full
    range of channels and sample rates on Emscripten builds.
    */
#if defined(__EMSCRIPTEN__)
    /* Good practice to prioritize the best format first so that the application can use the first data format as their chosen one if desired. */
    pDeviceInfo->nativeDataFormatCount = 3;
    pDeviceInfo->nativeDataFormats[0].format     = ma_format_s16;
    pDeviceInfo->nativeDataFormats[0].channels   = 0;   /* All channel counts supported. */
    pDeviceInfo->nativeDataFormats[0].sampleRate = 0;   /* All sample rates supported. */
    pDeviceInfo->nativeDataFormats[0].flags      = 0;
    pDeviceInfo->nativeDataFormats[1].format     = ma_format_s32;
    pDeviceInfo->nativeDataFormats[1].channels   = 0;   /* All channel counts supported. */
    pDeviceInfo->nativeDataFormats[1].sampleRate = 0;   /* All sample rates supported. */
    pDeviceInfo->nativeDataFormats[1].flags      = 0;
    pDeviceInfo->nativeDataFormats[2].format     = ma_format_u8;
    pDeviceInfo->nativeDataFormats[2].channels   = 0;   /* All channel counts supported. */
    pDeviceInfo->nativeDataFormats[2].sampleRate = 0;   /* All sample rates supported. */
    pDeviceInfo->nativeDataFormats[2].flags      = 0;
#else
    MA_ZERO_MEMORY(&desiredSpec, sizeof(desiredSpec));

    pDeviceName = NULL;
    if (pDeviceID != NULL) {
        pDeviceName = ((MA_PFN_SDL_GetAudioDeviceName)pContextEx->sdl.SDL_GetAudioDeviceName)(pDeviceID->custom.i, (deviceType == ma_device_type_playback) ? 0 : 1);
    }

    tempDeviceID = ((MA_PFN_SDL_OpenAudioDevice)pContextEx->sdl.SDL_OpenAudioDevice)(pDeviceName, (deviceType == ma_device_type_playback) ? 0 : 1, &desiredSpec, &obtainedSpec, MA_SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (tempDeviceID == 0) {
        ma_log_postf(ma_context_get_log(pContext), MA_LOG_LEVEL_ERROR, "Failed to open SDL device.");
        return MA_FAILED_TO_OPEN_BACKEND_DEVICE;
    }

    ((MA_PFN_SDL_CloseAudioDevice)pContextEx->sdl.SDL_CloseAudioDevice)(tempDeviceID);

    /* Only reporting a single native data format. It'll be whatever SDL decides is the best. */
    pDeviceInfo->nativeDataFormatCount = 1;
    pDeviceInfo->nativeDataFormats[0].format     = ma_format_from_sdl(obtainedSpec.format);
    pDeviceInfo->nativeDataFormats[0].channels   = obtainedSpec.channels;
    pDeviceInfo->nativeDataFormats[0].sampleRate = obtainedSpec.freq;
    pDeviceInfo->nativeDataFormats[0].flags      = 0;

    /* If miniaudio does not support the format, just use f32 as the native format (SDL will do the necessary conversions for us). */
    if (pDeviceInfo->nativeDataFormats[0].format == ma_format_unknown) {
        pDeviceInfo->nativeDataFormats[0].format = ma_format_f32;
    }
#endif  /* __EMSCRIPTEN__ */

    return MA_SUCCESS;
}

void ma_audio_callback_capture__sdl(void* pUserData, ma_uint8* pBuffer, int bufferSizeInBytes) {
    ma_device_sdl *pDeviceEx = (ma_device_sdl *)pUserData;
    ma_device_handle_backend_data_callback((ma_device *)pDeviceEx, NULL, pBuffer, (ma_uint32)bufferSizeInBytes / ma_get_bytes_per_frame(pDeviceEx->device.capture.internalFormat, pDeviceEx->device.capture.internalChannels));
}

void ma_audio_callback_playback__sdl(void* pUserData, ma_uint8* pBuffer, int bufferSizeInBytes) {
    ma_device_sdl *pDeviceEx = (ma_device_sdl *)pUserData;
    ma_device_handle_backend_data_callback((ma_device *)pDeviceEx, pBuffer, NULL, (ma_uint32)bufferSizeInBytes / ma_get_bytes_per_frame(pDeviceEx->device.playback.internalFormat, pDeviceEx->device.playback.internalChannels));
}

static ma_result ma_device_init_internal__sdl(ma_device_sdl *pDeviceEx, const ma_device_config *pConfig, ma_device_descriptor *pDescriptor) {
    ma_context_sdl *pContextEx = (ma_context_sdl *)pDeviceEx->device.pContext;

    /*
    SDL is a little bit awkward with specifying the buffer size, You need to specify the size of the buffer in frames, but since we may
    have requested a period size in milliseconds we'll need to convert, which depends on the sample rate. But there's a possibility that
    the sample rate just set to 0, which indicates that the native sample rate should be used. There's no practical way to calculate this
    that I can think of right now so I'm just using MA_DEFAULT_SAMPLE_RATE.
    */
    if (pDescriptor->sampleRate == 0) {
        pDescriptor->sampleRate = MA_DEFAULT_SAMPLE_RATE;
    }

    /*
    When determining the period size, you need to take defaults into account. This is how the size of the period should be determined.

        1) If periodSizeInFrames is not 0, use periodSizeInFrames; else
        2) If periodSizeInMilliseconds is not 0, use periodSizeInMilliseconds; else
        3) If both periodSizeInFrames and periodSizeInMilliseconds is 0, use the backend's default. If the backend does not allow a default
           buffer size, use a default value of MA_DEFAULT_PERIOD_SIZE_IN_MILLISECONDS_LOW_LATENCY or 
           MA_DEFAULT_PERIOD_SIZE_IN_MILLISECONDS_CONSERVATIVE depending on the value of pConfig->performanceProfile.

    Note that options 2 and 3 require knowledge of the sample rate in order to convert it to a frame count. You should try to keep the
    calculation of the period size as accurate as possible, but sometimes it's just not practical so just use whatever you can.

    A helper function called ma_calculate_buffer_size_in_frames_from_descriptor() is available to do all of this for you which is what
    we'll be using here.
    */
    pDescriptor->periodSizeInFrames = ma_calculate_buffer_size_in_frames_from_descriptor(pDescriptor, pDescriptor->sampleRate, pConfig->performanceProfile);

    /* SDL wants the buffer size to be a power of 2 for some reason. */
    if (pDescriptor->periodSizeInFrames > 32768) {
        pDescriptor->periodSizeInFrames = 32768;
    } else {
        pDescriptor->periodSizeInFrames = ma_next_power_of_2(pDescriptor->periodSizeInFrames);
    }


    /* We now have enough information to set up the device. */
    MA_SDL_AudioSpec desiredSpec;
    MA_ZERO_OBJECT(&desiredSpec);
    desiredSpec.freq     = (int)pDescriptor->sampleRate;
    desiredSpec.format   = ma_format_to_sdl(pDescriptor->format);
    desiredSpec.channels = (ma_uint8)pDescriptor->channels;
    desiredSpec.samples  = (ma_uint16)pDescriptor->periodSizeInFrames;
    desiredSpec.callback = (pConfig->deviceType == ma_device_type_capture) ? ma_audio_callback_capture__sdl : ma_audio_callback_playback__sdl;
    desiredSpec.userdata = pDeviceEx;

    /* We'll fall back to f32 if we don't have an appropriate mapping between SDL and miniaudio. */
    if (desiredSpec.format == 0) {
        desiredSpec.format = MA_AUDIO_F32;
    }

    const char *pDeviceName = NULL;
    if (pDescriptor->pDeviceID != NULL) {
        pDeviceName = ((MA_PFN_SDL_GetAudioDeviceName)pContextEx->sdl.SDL_GetAudioDeviceName)(pDescriptor->pDeviceID->custom.i, (pConfig->deviceType == ma_device_type_playback) ? 0 : 1);
    }

    MA_SDL_AudioSpec obtainedSpec;
    int deviceID = ((MA_PFN_SDL_OpenAudioDevice)pContextEx->sdl.SDL_OpenAudioDevice)(pDeviceName, (pConfig->deviceType == ma_device_type_playback) ? 0 : 1, &desiredSpec, &obtainedSpec, MA_SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (deviceID == 0) {
        ma_log_postf(ma_device_get_log((ma_device*)pDeviceEx), MA_LOG_LEVEL_ERROR, "Failed to open SDL2 device.");
        return MA_FAILED_TO_OPEN_BACKEND_DEVICE;
    }

    if (pConfig->deviceType == ma_device_type_playback) {
        pDeviceEx->sdl.deviceIDPlayback = deviceID;
    } else {
        pDeviceEx->sdl.deviceIDCapture = deviceID;
    }

    /* The descriptor needs to be updated with our actual settings. */
    pDescriptor->format             = ma_format_from_sdl(obtainedSpec.format);
    pDescriptor->channels           = obtainedSpec.channels;
    pDescriptor->sampleRate         = (ma_uint32)obtainedSpec.freq;
    ma_channel_map_init_standard(ma_standard_channel_map_default, pDescriptor->channelMap, ma_countof(pDescriptor->channelMap), pDescriptor->channels);
    pDescriptor->periodSizeInFrames = obtainedSpec.samples;
    pDescriptor->periodCount        = 1;    /* SDL doesn't use the notion of period counts, so just set to 1. */

    return MA_SUCCESS;
}

ma_result ma_device_init__sdl(ma_device *pDevice, const ma_device_config *pConfig, ma_device_descriptor *pDescriptorPlayback, ma_device_descriptor *pDescriptorCapture) {
    ma_device_sdl *pDeviceEx = (ma_device_sdl *)pDevice;
    ma_context_sdl *pContextEx = (ma_context_sdl *)pDevice->pContext;
    ma_result result;

    /* SDL does not support loopback mode, so must return MA_DEVICE_TYPE_NOT_SUPPORTED if it's requested. */
    if (pConfig->deviceType == ma_device_type_loopback) {
        return MA_DEVICE_TYPE_NOT_SUPPORTED;
    }

    if (pConfig->deviceType == ma_device_type_capture || pConfig->deviceType == ma_device_type_duplex) {
        result = ma_device_init_internal__sdl(pDeviceEx, pConfig, pDescriptorCapture);
        if (result != MA_SUCCESS) {
            return result;
        }
    }

    if (pConfig->deviceType == ma_device_type_playback || pConfig->deviceType == ma_device_type_duplex) {
        result = ma_device_init_internal__sdl(pDeviceEx, pConfig, pDescriptorPlayback);
        if (result != MA_SUCCESS) {
            if (pConfig->deviceType == ma_device_type_duplex) {
                ((MA_PFN_SDL_CloseAudioDevice)pContextEx->sdl.SDL_CloseAudioDevice)(pDeviceEx->sdl.deviceIDCapture);
            }

            return result;
        }
    }

    return MA_SUCCESS;
}

ma_result ma_device_uninit__sdl(ma_device *pDevice) {
    ma_device_sdl *pDeviceEx = (ma_device_sdl *)pDevice;
    ma_context_sdl *pContextEx = (ma_context_sdl *)pDevice->pContext;

    if (pDevice->type == ma_device_type_capture || pDevice->type == ma_device_type_duplex) {
        ((MA_PFN_SDL_CloseAudioDevice)pContextEx->sdl.SDL_CloseAudioDevice)(pDeviceEx->sdl.deviceIDCapture);
    }

    if (pDevice->type == ma_device_type_playback || pDevice->type == ma_device_type_duplex) {
        ((MA_PFN_SDL_CloseAudioDevice)pContextEx->sdl.SDL_CloseAudioDevice)(pDeviceEx->sdl.deviceIDCapture);
    }

    return MA_SUCCESS;
}

ma_result ma_device_start__sdl(ma_device *pDevice) {
    ma_device_sdl *pDeviceEx = (ma_device_sdl *)pDevice;
    ma_context_sdl *pContextEx = (ma_context_sdl *)pDevice->pContext;

    if (pDevice->type == ma_device_type_capture || pDevice->type == ma_device_type_duplex) {
        ((MA_PFN_SDL_PauseAudioDevice)pContextEx->sdl.SDL_PauseAudioDevice)(pDeviceEx->sdl.deviceIDCapture, 0);
    }

    if (pDevice->type == ma_device_type_playback || pDevice->type == ma_device_type_duplex) {
        ((MA_PFN_SDL_PauseAudioDevice)pContextEx->sdl.SDL_PauseAudioDevice)(pDeviceEx->sdl.deviceIDPlayback, 0);
    }

    return MA_SUCCESS;
}

ma_result ma_device_stop__sdl(ma_device *pDevice) {
    ma_device_sdl *pDeviceEx = (ma_device_sdl *)pDevice;
    ma_context_sdl *pContextEx = (ma_context_sdl *)pDevice->pContext;

    if (pDevice->type == ma_device_type_capture || pDevice->type == ma_device_type_duplex) {
        ((MA_PFN_SDL_PauseAudioDevice)pContextEx->sdl.SDL_PauseAudioDevice)(pDeviceEx->sdl.deviceIDCapture, 1);
    }

    if (pDevice->type == ma_device_type_playback || pDevice->type == ma_device_type_duplex) {
        ((MA_PFN_SDL_PauseAudioDevice)pContextEx->sdl.SDL_PauseAudioDevice)(pDeviceEx->sdl.deviceIDPlayback, 1);
    }

    return MA_SUCCESS;
}

ma_result ma_context_uninit__sdl(ma_context *pContext) {
    ma_context_sdl *pContextEx = (ma_context_sdl *)pContext;

    ((MA_PFN_SDL_QuitSubSystem)pContextEx->sdl.SDL_QuitSubSystem)(MA_SDL_INIT_AUDIO);

    /* Close the handle to the SDL shared object last. */
#ifndef MA_NO_RUNTIME_LINKING
    ma_dlclose(ma_context_get_log(pContext), pContextEx->sdl.hSDL);
#endif
    pContextEx->sdl.hSDL = NULL;

    return MA_SUCCESS;
}

ma_result ma_context_init__sdl(ma_context *pContext, const ma_context_config *pConfig, ma_backend_callbacks *pCallbacks) {
    ma_context_sdl *pContextEx = (ma_context_sdl *)pContext;
    
#ifndef MA_NO_RUNTIME_LINKING
    /* We'll use a list of possible shared object names for easier extensibility. */
    const char* pSDLNames[] = {
#if defined(_WIN32)
        "SDL2.dll"
#elif defined(__APPLE__)
        "SDL2.framework/SDL2"
#else
        "libSDL2-2.0.so.0"
#endif
    };

    (void)pConfig;

    /* Check if we have SDL2 installed somewhere. If not it's not usable and we need to abort. */
    for (size_t iName = 0; iName < ma_countof(pSDLNames); iName += 1) {
        pContextEx->sdl.hSDL = ma_dlopen(ma_context_get_log(pContext), pSDLNames[iName]);
        if (pContextEx->sdl.hSDL != NULL) {
            break;
        }
    }

    if (pContextEx->sdl.hSDL == NULL) {
        return MA_NO_BACKEND;   /* SDL2 could not be loaded. */
    }

    /* Now that we have the handle to the shared object we can go ahead and load some function pointers. */
    pContextEx->sdl.SDL_InitSubSystem      = ma_dlsym(ma_context_get_log(pContext), pContextEx->sdl.hSDL, "SDL_InitSubSystem");
    pContextEx->sdl.SDL_QuitSubSystem      = ma_dlsym(ma_context_get_log(pContext), pContextEx->sdl.hSDL, "SDL_QuitSubSystem");
    pContextEx->sdl.SDL_GetNumAudioDevices = ma_dlsym(ma_context_get_log(pContext), pContextEx->sdl.hSDL, "SDL_GetNumAudioDevices");
    pContextEx->sdl.SDL_GetAudioDeviceName = ma_dlsym(ma_context_get_log(pContext), pContextEx->sdl.hSDL, "SDL_GetAudioDeviceName");
    pContextEx->sdl.SDL_CloseAudioDevice   = ma_dlsym(ma_context_get_log(pContext), pContextEx->sdl.hSDL, "SDL_CloseAudioDevice");
    pContextEx->sdl.SDL_OpenAudioDevice    = ma_dlsym(ma_context_get_log(pContext), pContextEx->sdl.hSDL, "SDL_OpenAudioDevice");
    pContextEx->sdl.SDL_PauseAudioDevice   = ma_dlsym(ma_context_get_log(pContext), pContextEx->sdl.hSDL, "SDL_PauseAudioDevice");
#else
    pContextEx->sdl.SDL_InitSubSystem      = (ma_proc)SDL_InitSubSystem;
    pContextEx->sdl.SDL_QuitSubSystem      = (ma_proc)SDL_QuitSubSystem;
    pContextEx->sdl.SDL_GetNumAudioDevices = (ma_proc)SDL_GetNumAudioDevices;
    pContextEx->sdl.SDL_GetAudioDeviceName = (ma_proc)SDL_GetAudioDeviceName;
    pContextEx->sdl.SDL_CloseAudioDevice   = (ma_proc)SDL_CloseAudioDevice;
    pContextEx->sdl.SDL_OpenAudioDevice    = (ma_proc)SDL_OpenAudioDevice;
    pContextEx->sdl.SDL_PauseAudioDevice   = (ma_proc)SDL_PauseAudioDevice;
#endif  /* MA_NO_RUNTIME_LINKING */

    int resultSDL = ((MA_PFN_SDL_InitSubSystem)pContextEx->sdl.SDL_InitSubSystem)(MA_SDL_INIT_AUDIO);
    if (resultSDL != 0) {
        ma_dlclose(ma_context_get_log(pContext), pContextEx->sdl.hSDL);
        return MA_ERROR;
    }

    /*
    The last step is to make sure the callbacks are set properly in pCallbacks. Internally, miniaudio will copy these callbacks into the
    context object and then use them for then on for calling into our custom backend.
    */
    pCallbacks->onContextInit             = ma_context_init__sdl;
    pCallbacks->onContextUninit           = ma_context_uninit__sdl;
    pCallbacks->onContextEnumerateDevices = ma_context_enumerate_devices__sdl;
    pCallbacks->onContextGetDeviceInfo    = ma_context_get_device_info__sdl;
    pCallbacks->onDeviceInit              = ma_device_init__sdl;
    pCallbacks->onDeviceUninit            = ma_device_uninit__sdl;
    pCallbacks->onDeviceStart             = ma_device_start__sdl;
    pCallbacks->onDeviceStop              = ma_device_stop__sdl;

    return MA_SUCCESS;
}

#endif  /* MA_HAS_SDL */

#endif // miniaudio_sdl_inl