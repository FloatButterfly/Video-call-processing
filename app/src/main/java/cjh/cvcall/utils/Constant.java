package cjh.cvcall.utils;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import cjh.cvcall.R;
import cjh.cvcall.model.MessageBean;
import cjh.cvcall.model.MessageListBean;
import io.agora.rtc.RtcEngine;

public class Constant {
    public static int  CALL_IN = 0x01;
    public static int  CALL_OUT = 0x02;
    private static long timeLast;
    public static boolean isFastlyClick(){
        if (System.currentTimeMillis() - timeLast < 1500){
            timeLast = System.currentTimeMillis();
            return true;
        }else {
            timeLast = System.currentTimeMillis();
            return false;
        }
    }

    public static int MAX_INPUT_NAME_LENGTH = 128;

    public static Random RANDOM = new Random();

    public static final int[] COLOR_ARRAY = new int[]{R.drawable.shape_circle_black, R.drawable.shape_circle_blue, R.drawable.shape_circle_pink,
            R.drawable.shape_circle_pink_dark, R.drawable.shape_circle_yellow, R.drawable.shape_circle_red};

    private static List<MessageListBean> messageListBeanList = new ArrayList<>();


    public static void addMessageListBeanList(MessageListBean messageListBean) {
        messageListBeanList.add(messageListBean);

    }

    //logout clean list
    public static void cleanMessageListBeanList() {
        messageListBeanList.clear();
    }

    public static MessageListBean getExistMesageListBean(String accountOther) {
        int ret = existMessageListBean(accountOther);
        if (ret > -1) {

            return messageListBeanList.remove(ret);
        }
        return null;
    }

    //return exist list position
    private static int existMessageListBean(String accountOther) {
        int size = messageListBeanList.size();

        for (int i = 0; i < size; i++) {
            if (messageListBeanList.get(i).getAccountOther().equals(accountOther)) {

                return i;
            }
        }
        return -1;
    }

    public static void addMessageBean(String account, String msg) {
        MessageBean messageBean = new MessageBean(account, msg, false);

        int ret = existMessageListBean(account);

        if (ret == -1) {

            //account not exist new messagelistbean
            messageBean.setBackground(Constant.COLOR_ARRAY[RANDOM.nextInt(Constant.COLOR_ARRAY.length)]);
            List<MessageBean> messageBeanList = new ArrayList<>();
            messageBeanList.add(messageBean);
            messageListBeanList.add(new MessageListBean(account, messageBeanList));
        } else {

            //account exist get messagelistbean
            MessageListBean bean = messageListBeanList.remove(ret);
            List<MessageBean> messageBeanList = bean.getMessageBeanList();
            if (messageBeanList.size() > 0) {
                messageBean.setBackground(messageBeanList.get(0).getBackground());
            } else {
                messageBean.setBackground(Constant.COLOR_ARRAY[RANDOM.nextInt(Constant.COLOR_ARRAY.length)]);
            }
            messageBeanList.add(messageBean);
            bean.setMessageBeanList(messageBeanList);
            messageListBeanList.add(bean);
        }
    }

    public static final String MEDIA_SDK_VERSION;

    static {
        String sdk = "undefined";
        try {
            sdk = RtcEngine.getSdkVersion();
        } catch (Throwable e) {
        }
        MEDIA_SDK_VERSION = sdk;
    }

    public static boolean PRP_ENABLED = true;
    public static float PRP_DEFAULT_LIGHTNESS = 1.1f;
    public static int PRP_DEFAULT_SMOOTHNESS = 12;
    public static final float PRP_MAX_LIGHTNESS = 1.5f;
    public static final int PRP_MAX_SMOOTHNESS = 15;

    public static boolean SHOW_VIDEO_INFO = true;
}
