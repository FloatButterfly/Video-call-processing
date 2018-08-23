package cjh.cvcall.Activity;

import android.content.Context;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.OrientationHelper;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.List;

import cjh.cvcall.AGApplication;
import cjh.cvcall.ChannelVideo.ui.ChannelChooseActivity;
import cjh.cvcall.R;
import cjh.cvcall.adapter.MessageAdapter;
import cjh.cvcall.model.MessageBean;
import cjh.cvcall.model.MessageListBean;
import cjh.cvcall.utils.Constant;
import cjh.cvcall.utils.ToastUtils;
import io.agora.AgoraAPI;
import io.agora.AgoraAPIOnlySignal;
import io.agora.IAgoraAPI;

public class VideoActivity extends AppCompatActivity {
    private String account;
    private int uid;
    private final String TAG = VideoActivity.class.getSimpleName();
    private Button buttonSingle;
    private Button buttonChannel;
    Boolean stateSingleMode=true;
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_video);
        initUI();
    }
    private void initUI(){
        Intent intent = getIntent();
        account=intent.getStringExtra("account");
        uid=intent.getIntExtra("uid",0);
        buttonSingle=findViewById(R.id.SingleVideoCall);
        buttonChannel=findViewById(R.id.ChannelVideoCall);
    }
    public void Join_single_chat(View view){
        stateSingleMode=true;
        onSelectMode();
    }
    public void Join_channel_chat(View view){
        stateSingleMode=false;
        onSelectMode();
    }
    public void onSelectMode(){

        if(stateSingleMode){
            Intent intent= new Intent(VideoActivity.this, NumberCallActivity.class);
            intent.putExtra("account",account);
            intent.putExtra("uid",uid);
            startActivity(intent);
        }
        else{
            Intent intent= new Intent(VideoActivity.this,ChannelChooseActivity.class);
            intent.putExtra("account",account);
            intent.putExtra("uid",uid);
            startActivity(intent);
        }
    }
    private void addCallback(){
        AGApplication.the().getmAgoraAPI().callbackSet(new AgoraAPI.CallBack(){
            public void onLogout(final int i) {

                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        if (i == IAgoraAPI.ECODE_LOGOUT_E_KICKED) { //other login the account
                            ToastUtils.show(new WeakReference<Context>(VideoActivity.this), "Other login account ,you are logout.");

                        } else if (i == IAgoraAPI.ECODE_LOGOUT_E_NET) { //net
                            ToastUtils.show(new WeakReference<Context>(VideoActivity.this), "Logout for Network can not be.");

                        }
                        finish();

                    }
                });

            }
            public void onError(String s, int i, String s1) {
                Log.i(TAG, "onError s:" + s + " s1:" + s1);
            }

        });
    }


    @Override
    protected void onResume() {
        super.onResume();
        addCallback();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.i(TAG ,"onDestroy");
    }

}


