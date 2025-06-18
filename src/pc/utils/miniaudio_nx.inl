#ifndef miniaudio_nx_inl
#define miniaudio_nx_inl

#include <malloc.h>
#include <stdlib.h>

/* Only enable MA_SUPPORT_NX on Nintendo Switch */
#ifdef __SWITCH__
#define MA_SUPPORT_NX
#endif

/*
Only enable NX if it's hasn't been explicitly disabled (MA_NO_NX) or enabled (MA_ENABLE_NX with
MA_ENABLE_ONLY_SPECIFIC_BACKENDS) and it's supported at compile time (MA_SUPPORT_NX).
*/
#if defined(MA_SUPPORT_NX) && !defined(MA_NO_NX) && (!defined(MA_ENABLE_ONLY_SPECIFIC_BACKENDS) || defined(MA_ENABLE_NX))
    #define MA_HAS_NX
#endif

#if defined(MA_HAS_NX)

ma_result ma_context_init__nx(ma_context *pContext, const ma_context_config *pConfig, ma_backend_callbacks *pCallbacks);
ma_result ma_context_uninit__nx(ma_context *pContext);
ma_result ma_device_init__nx(ma_device *pDevice, const ma_device_config *pConfig, ma_device_descriptor *pDescriptorPlayback, ma_device_descriptor *pDescriptorCapture);
ma_result ma_device_uninit__nx(ma_device *pDevice);
ma_result ma_device_start__nx(ma_device *pDevice);
ma_result ma_device_stop__nx(ma_device *pDevice);

ma_result ma_context_enumerate_devices__nx(ma_context *pContext, ma_enum_devices_callback_proc callback, void *pUserData);
ma_result ma_context_get_device_info__nx(ma_context *pContext, ma_device_type deviceType, const ma_device_id *pDeviceID, ma_device_info *pDeviceInfo);

#endif // MA_HAS_NX

#if defined(MA_HAS_NX)

#include <switch.h>

AudioOutBuffer audout_buf = { 0 };
AudioOutBuffer *released_out_buffer = NULL;
u32 released_out_count = 0;

PcmFormat ma_format_to_nx(ma_format format) {
    switch (format)
    {
        case ma_format_u8:      return PcmFormat_Int8;
        case ma_format_s16:     return PcmFormat_Int16;
        case ma_format_s24:     return PcmFormat_Int24;
        case ma_format_s32:     return PcmFormat_Int32;
        case ma_format_f32:     return PcmFormat_Float;
        default:                return PcmFormat_Invalid;
    }
}

ma_format ma_format_from_nx(PcmFormat format) {
    switch (format)
    {
        case PcmFormat_Int8:  return ma_format_u8;
        case PcmFormat_Int16: return ma_format_s16;
        case PcmFormat_Int24: return ma_format_s24;
        case PcmFormat_Int32: return ma_format_s32;
        case PcmFormat_Float: return ma_format_f32;
        default:              return ma_format_unknown;
    }
}

ma_result ma_context_enumerate_devices__nx(UNUSED ma_context *pContext, UNUSED ma_enum_devices_callback_proc callback, UNUSED void *pUserData) {
    return MA_SUCCESS;
}

ma_result ma_context_get_device_info__nx(UNUSED ma_context *pContext, UNUSED ma_device_type deviceType, UNUSED const ma_device_id *pDeviceID, ma_device_info *pDeviceInfo) {
    pDeviceInfo->id.custom.i = 0;
    pDeviceInfo->isDefault = MA_TRUE;
    ma_strncpy_s(pDeviceInfo->name, sizeof(pDeviceInfo->name), MA_DEFAULT_PLAYBACK_DEVICE_NAME, (size_t)-1);
    
    pDeviceInfo->nativeDataFormatCount = 1;
    pDeviceInfo->nativeDataFormats[0].format = ma_format_s16;
    pDeviceInfo->nativeDataFormats[0].channels = 2;
    pDeviceInfo->nativeDataFormats[0].sampleRate = 48000;
    pDeviceInfo->nativeDataFormats[0].flags = 0;
    
    /* If miniaudio does not support the format, just use f32 as the native format (SDL will do the necessary conversions for us). */
    if (pDeviceInfo->nativeDataFormats[0].format == ma_format_unknown) {
        pDeviceInfo->nativeDataFormats[0].format = ma_format_f32;
    }
    
    return MA_SUCCESS;
}

ma_result ma_device_init__nx(ma_device *pDevice, const ma_device_config *pConfig, UNUSED ma_device_descriptor *pDescriptorPlayback, UNUSED ma_device_descriptor *pDescriptorCapture) {
    /* NX does not support loopback mode, so must return MA_DEVICE_TYPE_NOT_SUPPORTED if it's requested. */
    if (pConfig->deviceType == ma_device_type_loopback) {
        return MA_DEVICE_TYPE_NOT_SUPPORTED;
    }
    
    // Initialize the default audio output device.
    Result rc = audoutInitialize();
    if (!R_SUCCEEDED(rc)) {
        ma_log_postf(ma_device_get_log(pDevice), MA_LOG_LEVEL_ERROR, "[NX] audoutInitialize() returned 0x%x", rc);
        return MA_ERROR;
    }
    
    // Make sure the sample buffer size is aligned to 0x1000 bytes.
    u32 data_size = ((audoutGetSampleRate() / 30) * audoutGetChannelCount() * 2);
    u32 buffer_size = (data_size + 0xfff) & ~0xfff;
    
    // Allocate the buffers.
    u8 *out_buf_data = memalign(0x1000, buffer_size);
    
    // Ensure buffers were properly allocated.
    if (out_buf_data == NULL) {
        rc = MAKERESULT(Module_Libnx, LibnxError_OutOfMemory);
    }
    
    if (!R_SUCCEEDED(rc)) {
        ma_log_postf(ma_device_get_log(pDevice), MA_LOG_LEVEL_ERROR, "[NX] ma_device_init__nx() failed to allocate buffer with error 0x%x", rc);
        audoutExit();
        free(out_buf_data);
        return MA_ERROR;
    }
    
    memset(out_buf_data, 0, buffer_size);
    
    // Prepare the output buffer.
    audout_buf.next = NULL;
    audout_buf.buffer = out_buf_data;
    audout_buf.buffer_size = buffer_size;
    audout_buf.data_size = data_size;
    audout_buf.data_offset = 0;
    
    // Prepare pointers and counters for released buffers.
    released_out_buffer = NULL;
    released_out_count = 0;
    
    // Append the initial output buffer.
    rc = audoutAppendAudioOutBuffer(&audout_buf);
    if (!R_SUCCEEDED(rc)) {
        ma_log_postf(ma_device_get_log(pDevice), MA_LOG_LEVEL_ERROR, "[NX] audoutAppendAudioOutBuffer() returned 0x%x", rc);
        audoutExit();
        free(out_buf_data);
        return MA_ERROR;
    }

    return MA_SUCCESS;
}

ma_result ma_device_uninit__nx(UNUSED ma_device *pDevice) {
    audoutExit();
    
    if (audout_buf.buffer) { free(audout_buf.buffer); }
    memset(&audout_buf, 0, sizeof(audout_buf));
    released_out_buffer = NULL;
    released_out_count = 0;
    return MA_SUCCESS;
}

ma_result ma_device_start__nx(ma_device *pDevice) {
    Result rc = audoutStartAudioOut();
    if (!R_SUCCEEDED(rc)) {
        ma_log_postf(ma_device_get_log(pDevice), MA_LOG_LEVEL_ERROR, "[NX] audoutStartAudioOut() returned 0x%x", rc);
        return MA_ERROR;
    }
    
    return MA_SUCCESS;
}

ma_result ma_device_stop__nx(ma_device *pDevice) {
    Result rc = audoutStopAudioOut();
    if (!R_SUCCEEDED(rc)) {
        ma_log_postf(ma_device_get_log(pDevice), MA_LOG_LEVEL_ERROR, "[NX] audoutStopAudioOut() returned 0x%x", rc);
        return MA_ERROR;
    }
    
    return MA_SUCCESS;
}

ma_result ma_context_uninit__nx(UNUSED ma_context *pContext) {
    return MA_SUCCESS;
}

ma_result ma_context_init__nx(UNUSED ma_context *pContext, UNUSED const ma_context_config *pConfig, ma_backend_callbacks *pCallbacks) {
    /*
    The last step is to make sure the callbacks are set properly in pCallbacks. Internally, miniaudio will copy these callbacks into the
    context object and then use them for then on for calling into our custom backend.
    */
    pCallbacks->onContextInit             = ma_context_init__nx;
    pCallbacks->onContextUninit           = ma_context_uninit__nx;
    pCallbacks->onContextEnumerateDevices = ma_context_enumerate_devices__nx;
    pCallbacks->onContextGetDeviceInfo    = ma_context_get_device_info__nx;
    pCallbacks->onDeviceInit              = ma_device_init__nx;
    pCallbacks->onDeviceUninit            = ma_device_uninit__nx;
    pCallbacks->onDeviceStart             = ma_device_start__nx;
    pCallbacks->onDeviceStop              = ma_device_stop__nx;

    return MA_SUCCESS;
}

#endif // MA_HAS_NX

#endif // miniaudio_nx_inl