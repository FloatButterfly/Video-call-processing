//
// Created by changjianhui on 2018/4/11.
//
#include <jni.h>
#include <android/log.h>
#include <cstring>

#include "../cpp/agora/IAgoraRtcEngine.h"
#include "../cpp/agora/IAgoraMediaEngine.h"
#include "cjh_cvcall_propeller_preprocessing_VideoPreProcessing.h"

class AgoraVideoFrameObserver : public agora::media::IVideoFrameObserver {
public:
    virtual bool onCaptureVideoFrame(VideoFrame &videoFrame) override {
        int width = videoFrame.width;
        int height = videoFrame.height;
        int uStride = videoFrame.uStride;
        int vStride = videoFrame.vStride;
        memset(videoFrame.uBuffer, 256, uStride * height / 2);
        memset(videoFrame.vBuffer, 256, vStride * height / 2);

        return true;
    }

    virtual bool onRenderVideoFrame(unsigned int uid, VideoFrame &videoFrame) override {
        return true;
    }
};

static AgoraVideoFrameObserver s_videoFrameObserver;
static agora::rtc::IRtcEngine *rtcEngine = NULL;

#ifdef __cplusplus
extern "C" {
#endif

int __attribute__((visibility("default")))
loadAgoraRtcEnginePlugin(agora::rtc::IRtcEngine *engine) {
    __android_log_print(ANDROID_LOG_ERROR, "plugin", "plugin loadAgoraRtcEnginePlugin");
    rtcEngine = engine;
    return 0;
}

void __attribute__((visibility("default")))
unloadAgoraRtcEnginePlugin(agora::rtc::IRtcEngine *engine) {
    __android_log_print(ANDROID_LOG_ERROR, "plugin", "plugin unloadAgoraRtcEnginePlugin");
    rtcEngine = NULL;
}
JNIEXPORT void JNICALL
Java_cjh_cvcall_propeller_preprocessing_VideoPreProcessing_enablePreProcessing(JNIEnv *env,
                                                                               jobject obj,
                                                                               jboolean enable) {
    if (!rtcEngine)
        return;
    agora::util::AutoPtr<agora::media::IMediaEngine> mediaEngine;
    mediaEngine.queryInterface(rtcEngine, agora::AGORA_IID_MEDIA_ENGINE);
    if (mediaEngine) {
        if (enable) {
            mediaEngine->registerVideoFrameObserver(&s_videoFrameObserver);
        } else {
            mediaEngine->registerVideoFrameObserver(NULL);
        }
    }
}

#ifdef __cplusplus
}
#endif
