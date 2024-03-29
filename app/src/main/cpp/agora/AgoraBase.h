//
//  Agora Engine SDK
//
//  Created by Sting Feng in 2017-11.
//  Copyright (c) 2017 Agora.io. All rights reserved.
//

#ifndef AGORA_BASE_H
#define AGORA_BASE_H

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define AGORA_CALL __cdecl
#if defined(AGORARTC_EXPORT)
#define AGORA_API extern "C" __declspec(dllexport)
#else
#define AGORA_API extern "C" __declspec(dllimport)
#endif
#elif defined(__APPLE__)
#define AGORA_API __attribute__((visibility("default"))) extern "C"
#define AGORA_CALL
#elif defined(__ANDROID__) || defined(__linux__)
#define AGORA_API extern "C" __attribute__((visibility("default")))
#define AGORA_CALL
#else
#define AGORA_API extern "C"
#define AGORA_CALL
#endif

namespace agora {
    namespace util {

        template<class T>
        class AutoPtr {
            typedef T value_type;
            typedef T *pointer_type;
        public:
            AutoPtr(pointer_type p = 0)
                    : ptr_(p) {}

            ~AutoPtr() {
                if (ptr_)
                    ptr_->release();
            }

            operator bool() const { return ptr_ != (pointer_type) 0; }

            value_type &operator*() const {
                return *get();
            }

            pointer_type operator->() const {
                return get();
            }

            pointer_type get() const {
                return ptr_;
            }

            pointer_type release() {
                pointer_type tmp = ptr_;
                ptr_ = 0;
                return tmp;
            }

            void reset(pointer_type ptr = 0) {
                if (ptr != ptr_ && ptr_)
                    ptr_->release();
                ptr_ = ptr;
            }

            template<class C1, class C2>
            bool queryInterface(C1 *c, C2 iid) {
                pointer_type p = NULL;
                if (c && !c->queryInterface(iid, (void **) &p)) {
                    reset(p);
                }
                return p != NULL;;
            }

        private:
            AutoPtr(const AutoPtr &);

            AutoPtr &operator=(const AutoPtr &);

        private:
            pointer_type ptr_;
        };

        class IString {
        public:
            virtual bool empty() const = 0;

            virtual const char *c_str() = 0;

            virtual const char *data() = 0;

            virtual size_t length() = 0;

            virtual void release() = 0;
        };

        typedef AutoPtr<IString> AString;

    }//namespace util

    enum INTERFACE_ID_TYPE {
        AGORA_IID_AUDIO_DEVICE_MANAGER = 1,
        AGORA_IID_VIDEO_DEVICE_MANAGER = 2,
        AGORA_IID_RTC_ENGINE_PARAMETER = 3,
        AGORA_IID_MEDIA_ENGINE = 4,
        AGORA_IID_SIGNALING_ENGINE = 8,
    };

    enum WARN_CODE_TYPE {
        WARN_INVALID_VIEW = 8,
        WARN_INIT_VIDEO = 16,
        WARN_PENDING = 20,
        WARN_NO_AVAILABLE_CHANNEL = 103,
        WARN_LOOKUP_CHANNEL_TIMEOUT = 104,
        WARN_LOOKUP_CHANNEL_REJECTED = 105,
        WARN_OPEN_CHANNEL_TIMEOUT = 106,
        WARN_OPEN_CHANNEL_REJECTED = 107,

        // sdk: 100~1000
                WARN_SWITCH_LIVE_VIDEO_TIMEOUT = 111,
        WARN_SET_CLIENT_ROLE_TIMEOUT = 118,
        WARN_OPEN_CHANNEL_INVALID_TICKET = 121,
        WARN_OPEN_CHANNEL_TRY_NEXT_VOS = 122,
        WARN_AUDIO_MIXING_OPEN_ERROR = 701,

        WARN_ADM_RUNTIME_PLAYOUT_WARNING = 1014,
        WARN_ADM_RUNTIME_RECORDING_WARNING = 1016,
        WARN_ADM_RECORD_AUDIO_SILENCE = 1019,
        WARN_ADM_PLAYOUT_MALFUNCTION = 1020,
        WARN_ADM_RECORD_MALFUNCTION = 1021,
        WARN_ADM_IOS_CATEGORY_NOT_PLAYANDRECORD = 1029,
        WARN_ADM_IOS_SAMPLERATE_CHANGE = 1030,
        WARN_ADM_RECORD_AUDIO_LOWLEVEL = 1031,
        WARN_ADM_PLAYOUT_AUDIO_LOWLEVEL = 1032,
        WARN_ADM_WINDOWS_NO_DATA_READY_EVENT = 1040,
        WARN_APM_HOWLING = 1051,
        WARN_ADM_GLITCH_STATE = 1052,
        WARN_ADM_IMPROPER_SETTINGS = 1053,
        WARN_ADM_WIN_CORE_NO_RECORDING_DEVICE = 1322,
        WARN_ADM_WIN_CORE_NO_PLAYOUT_DEVICE = 1323,
        WARN_ADM_WIN_CORE_IMPROPER_CAPTURE_RELEASE = 1324,
    };

    enum ERROR_CODE_TYPE {
        ERR_OK = 0,
        //1~1000
                ERR_FAILED = 1,
        ERR_INVALID_ARGUMENT = 2,
        ERR_NOT_READY = 3,
        ERR_NOT_SUPPORTED = 4,
        ERR_REFUSED = 5,
        ERR_BUFFER_TOO_SMALL = 6,
        ERR_NOT_INITIALIZED = 7,
        ERR_NO_PERMISSION = 9,
        ERR_TIMEDOUT = 10,
        ERR_CANCELED = 11,
        ERR_TOO_OFTEN = 12,
        ERR_BIND_SOCKET = 13,
        ERR_NET_DOWN = 14,
        ERR_NET_NOBUFS = 15,
        ERR_JOIN_CHANNEL_REJECTED = 17,
        ERR_LEAVE_CHANNEL_REJECTED = 18,
        ERR_ALREADY_IN_USE = 19,
        ERR_ABORTED = 20,
        ERR_INIT_NET_ENGINE = 21,
        ERR_RESOURCE_LIMITED = 22,
        ERR_INVALID_APP_ID = 101,
        ERR_INVALID_CHANNEL_NAME = 102,
        ERR_TOKEN_EXPIRED = 109,
        ERR_INVALID_TOKEN = 110,
        ERR_CONNECTION_INTERRUPTED = 111, // only used in web sdk
        ERR_CONNECTION_LOST = 112, // only used in web sdk
        ERR_DECRYPTION_FAILED = 120,

        ERR_NOT_IN_CHANNEL = 113,
        ERR_SIZE_TOO_LARGE = 114,
        ERR_BITRATE_LIMIT = 115,
        ERR_TOO_MANY_DATA_STREAMS = 116,
        ERR_STREAM_MESSAGE_TIMEOUT = 117,
        ERR_SET_CLIENT_ROLE_NOT_AUTHORIZED = 119,
        ERR_CLIENT_IS_BANNED_BY_SERVER = 123,

        //signaling: 400~600
                ERR_LOGOUT_OTHER = 400,  //
        ERR_LOGOUT_USER = 401,  // logout by user
        ERR_LOGOUT_NET = 402,  // network failure
        ERR_LOGOUT_KICKED = 403,  // login in other device
        ERR_LOGOUT_PACKET = 404,  //
        ERR_LOGOUT_TOKEN_EXPIRED = 405,  // token expired
        ERR_LOGOUT_OLDVERSION = 406,  //
        ERR_LOGOUT_TOKEN_WRONG = 407,
        ERR_LOGOUT_ALREADY_LOGOUT = 408,

        ERR_LOGIN_OTHER = 420,
        ERR_LOGIN_NET = 421,
        ERR_LOGIN_FAILED = 422,
        ERR_LOGIN_CANCELED = 423,
        ERR_LOGIN_TOKEN_EXPIRED = 424,
        ERR_LOGIN_OLD_VERSION = 425,
        ERR_LOGIN_TOKEN_WRONG = 426,
        ERR_LOGIN_TOKEN_KICKED = 427,
        ERR_LOGIN_ALREADY_LOGIN = 428,

        ERR_JOIN_CHANNEL_OTHER = 440,

        ERR_SEND_MESSAGE_OTHER = 440,
        ERR_SEND_MESSAGE_TIMEOUT = 441,

        ERR_QUERY_USERNUM_OTHER = 450,
        ERR_QUERY_USERNUM_TIMEOUT = 451,
        ERR_QUERY_USERNUM_BYUSER = 452,

        ERR_LEAVE_CHANNEL_OTHER = 460,
        ERR_LEAVE_CHANNEL_KICKED = 461,
        ERR_LEAVE_CHANNEL_BYUSER = 462,
        ERR_LEAVE_CHANNEL_LOGOUT = 463,
        ERR_LEAVE_CHANNEL_DISCONNECTED = 464,

        ERR_INVITE_OTHER = 470,
        ERR_INVITE_REINVITE = 471,
        ERR_INVITE_NET = 472,
        ERR_INVITE_PEER_OFFLINE = 473,
        ERR_INVITE_TIMEOUT = 474,
        ERR_INVITE_CANT_RECV = 475,


        //1001~2000
                ERR_LOAD_MEDIA_ENGINE = 1001,
        ERR_START_CALL = 1002,
        ERR_START_CAMERA = 1003,
        ERR_START_VIDEO_RENDER = 1004,
        ERR_ADM_GENERAL_ERROR = 1005,
        ERR_ADM_JAVA_RESOURCE = 1006,
        ERR_ADM_SAMPLE_RATE = 1007,
        ERR_ADM_INIT_PLAYOUT = 1008,
        ERR_ADM_START_PLAYOUT = 1009,
        ERR_ADM_STOP_PLAYOUT = 1010,
        ERR_ADM_INIT_RECORDING = 1011,
        ERR_ADM_START_RECORDING = 1012,
        ERR_ADM_STOP_RECORDING = 1013,
        ERR_ADM_RUNTIME_PLAYOUT_ERROR = 1015,
        ERR_ADM_RUNTIME_RECORDING_ERROR = 1017,
        ERR_ADM_RECORD_AUDIO_FAILED = 1018,
        ERR_ADM_INIT_LOOPBACK = 1022,
        ERR_ADM_START_LOOPBACK = 1023,
        ERR_ADM_NO_PERMISSION = 1027,
        ERR_ADM_RECORD_AUDIO_IS_ACTIVE = 1033,
        ERR_ADM_ANDROID_JNI_JAVA_RESOURCE = 1101,
        ERR_ADM_ANDROID_JNI_NO_RECORD_FREQUENCY = 1108,
        ERR_ADM_ANDROID_JNI_NO_PLAYBACK_FREQUENCY = 1109,
        ERR_ADM_ANDROID_JNI_JAVA_START_RECORD = 1111,
        ERR_ADM_ANDROID_JNI_JAVA_START_PLAYBACK = 1112,
        ERR_ADM_ANDROID_JNI_JAVA_RECORD_ERROR = 1115,
        ERR_ADM_ANDROID_OPENSL_CREATE_ENGINE = 1151,
        ERR_ADM_ANDROID_OPENSL_CREATE_AUDIO_RECORDER = 1153,
        ERR_ADM_ANDROID_OPENSL_START_RECORDER_THREAD = 1156,
        ERR_ADM_ANDROID_OPENSL_CREATE_AUDIO_PLAYER = 1157,
        ERR_ADM_ANDROID_OPENSL_START_PLAYER_THREAD = 1160,
        ERR_ADM_IOS_INPUT_NOT_AVAILABLE = 1201,
        ERR_ADM_IOS_ACTIVATE_SESSION_FAIL = 1206,
        ERR_ADM_IOS_VPIO_INIT_FAIL = 1210,
        ERR_ADM_IOS_VPIO_REINIT_FAIL = 1213,
        ERR_ADM_IOS_VPIO_RESTART_FAIL = 1214,
        ERR_ADM_IOS_SET_RENDER_CALLBACK_FAIL = 1219,
        ERR_ADM_IOS_SESSION_SAMPLERATR_ZERO = 1221,
        ERR_ADM_WIN_CORE_INIT = 1301,
        ERR_ADM_WIN_CORE_INIT_RECORDING = 1303,
        ERR_ADM_WIN_CORE_INIT_PLAYOUT = 1306,
        ERR_ADM_WIN_CORE_INIT_PLAYOUT_NULL = 1307,
        ERR_ADM_WIN_CORE_START_RECORDING = 1309,
        ERR_ADM_WIN_CORE_CREATE_REC_THREAD = 1311,
        ERR_ADM_WIN_CORE_CAPTURE_NOT_STARTUP = 1314,
        ERR_ADM_WIN_CORE_CREATE_RENDER_THREAD = 1319,
        ERR_ADM_WIN_CORE_RENDER_NOT_STARTUP = 1320,
        ERR_ADM_WIN_CORE_NO_RECORDING_DEVICE = 1322,
        ERR_ADM_WIN_CORE_NO_PLAYOUT_DEVICE = 1323,
        ERR_ADM_WIN_WAVE_INIT = 1351,
        ERR_ADM_WIN_WAVE_INIT_RECORDING = 1353,
        ERR_ADM_WIN_WAVE_INIT_MICROPHONE = 1354,
        ERR_ADM_WIN_WAVE_INIT_PLAYOUT = 1355,
        ERR_ADM_WIN_WAVE_INIT_SPEAKER = 1356,
        ERR_ADM_WIN_WAVE_START_RECORDING = 1357,
        ERR_ADM_WIN_WAVE_START_PLAYOUT = 1358,
        ERR_ADM_NO_RECORDING_DEVICE = 1359,
        ERR_ADM_NO_PLAYOUT_DEVICE = 1360,

        // VDM error code starts from 1500
                ERR_VDM_CAMERA_NOT_AUTHORIZED = 1501,

        // VCM error code starts from 1600
                ERR_VCM_UNKNOWN_ERROR = 1600,
        ERR_VCM_ENCODER_INIT_ERROR = 1601,
        ERR_VCM_ENCODER_ENCODE_ERROR = 1602,
        ERR_VCM_ENCODER_SET_ERROR = 1603,
    };

    enum LOG_FILTER_TYPE {
        LOG_FILTER_OFF = 0,
        LOG_FILTER_DEBUG = 0x080f,
        LOG_FILTER_INFO = 0x000f,
        LOG_FILTER_WARN = 0x000e,
        LOG_FILTER_ERROR = 0x000c,
        LOG_FILTER_CRITICAL = 0x0008,
        LOG_FILTER_MASK = 0x80f,
    };
} // namespace agora

#endif
