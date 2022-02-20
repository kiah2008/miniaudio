#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#ifdef ANDROID
#include <android/log.h>

#ifndef LOG_TAG
#define LOG_TAG "mini_audio"
#endif

#define LOGD(format...) __android_log_buf_print(LOG_ID_MAIN, ANDROID_LOG_DEBUG, LOG_TAG, format, ##__VA_ARGS__)
#else
#define LOGD(format...) printf(format, ##__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif