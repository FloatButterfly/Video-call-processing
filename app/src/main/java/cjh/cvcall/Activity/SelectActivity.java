package cjh.cvcall.Activity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import java.lang.ref.WeakReference;

import cjh.cvcall.AGApplication;
import cjh.cvcall.R;
import cjh.cvcall.utils.ToastUtils;
import io.agora.AgoraAPI;
import io.agora.IAgoraAPI;

public class SelectActivity extends AppCompatActivity {

    private String account;
    private int uid;
    private final String TAG=SelectActivity.class.getSimpleName();
    private Button buttonVideo;
    private Button buttonText;
    Boolean stateVideoMode=true;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_select);
        initUI();
    }
    private void initUI(){
        Intent intent = getIntent();
        account=intent.getStringExtra("account");
        uid=intent.getIntExtra("uid",0);
        buttonVideo=findViewById(R.id.join_VideoChat);
        buttonText=findViewById(R.id.join_TextChat);
    }
    public void Join_video_chat(View view){
        stateVideoMode=true;
        onSelectMode();
    }
    public void Join_text_chat(View view){
        stateVideoMode=false;
        onSelectMode();
    }
    public void onSelectMode(){

        if(stateVideoMode){
            Intent intent= new Intent(SelectActivity.this,VideoActivity.class);
            intent.putExtra("account",account);
            intent.putExtra("uid",uid);
            startActivity(intent);
        }
        else{
            Intent intent= new Intent(SelectActivity.this,TextActivity.class);
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
                            ToastUtils.show(new WeakReference<Context>(SelectActivity.this), "Other login account ,you are logout.");

                        } else if (i == IAgoraAPI.ECODE_LOGOUT_E_NET) { //net
                            ToastUtils.show(new WeakReference<Context>(SelectActivity.this), "Logout for Network can not be.");

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
