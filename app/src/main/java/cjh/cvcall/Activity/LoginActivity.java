package cjh.cvcall.Activity;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import cjh.cvcall.AGApplication;
import cjh.cvcall.R;
import io.agora.AgoraAPI;
import io.agora.IAgoraAPI;
import io.agora.rtc.RtcEngine;

public class LoginActivity extends AppCompatActivity {

    private final String TAG=LoginActivity.class.getSimpleName();
    private EditText textAccountName;
    private int uid;
    private String account;
    private String appId;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        Log.i("dd","oncreat");
        appId=getString(R.string.agora_app_id);
        textAccountName = (EditText) findViewById(R.id.account_name);
        textAccountName.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                boolean isEmpty = s.toString().isEmpty();
                findViewById(R.id.button_login).setEnabled(!isEmpty);
            }
        });
    }
    public void onClickLogin(View v){
        Log.i(TAG ,"onClickLogin");
        account = textAccountName.getText().toString().trim();

        AGApplication.the().getmAgoraAPI().login2(appId, account, "_no_need_token", 0, "" ,5,1);
    }

    private void addCallback() {
        Log.i(TAG, "addCallback enter." );
   //     if(new AGApplication().the()==null) {
    //        new AGApplication();
     //       Log.i(TAG, "aga initial success");
      //  }
        AGApplication.the().getmAgoraAPI().callbackSet(new AgoraAPI.CallBack() {
            public void onLoginSuccess(int i, int i1) {
                Log.i(TAG ,"onLoginSuccess " + i + "  " + i1 );
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Intent intent = new Intent(LoginActivity.this ,SelectActivity.class);
                        intent.putExtra("uid" ,uid);
                        intent.putExtra("account" ,account);
                        startActivity(intent);
                    }
                });
            }

            @Override
            public void onLogout(int i) {
                Log.i(TAG ,"onLogout  i = " + i);
            }

            @Override
            public void onLoginFailed(final int i) {
                Log.i(TAG ,"onLoginFailed " + i);
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        if (i == IAgoraAPI.ECODE_LOGIN_E_NET){
                            Toast.makeText(LoginActivity.this ,"Login Failed for the network is not available",Toast.LENGTH_SHORT ).show();
                        }
                    }
                });
            }


            @Override
            public void onError(String s, int i, String s1) {
                Log.i(TAG ,"onError s:"+ s + " s1:" + s1);
            }

        });
    }

    @Override
    protected void onResume() {
        Log.i(TAG,"resume");
        super.onResume();
        Log.i(TAG,"callback begin");
        addCallback();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.i(TAG ,"onDestroy");
        RtcEngine.destroy();
    }
}