package cjh.cvcall.propeller.preprocessing;

import android.util.Log;

public class VideoPreProcessing {
    static
    {
        System.loadLibrary("apm-plugin-video-preprocessing");
        Log.i("JNI","load success");
    }
    public native void enablePreProcessing(boolean enable);
}
