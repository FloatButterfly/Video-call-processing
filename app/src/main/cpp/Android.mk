LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)


LOCAL_LDLIBS := -ldl -llog

LOCAL_MODULE := apm-plugin-video-preprocessing

include $(BUILD_SHARED_LIBRARY)
