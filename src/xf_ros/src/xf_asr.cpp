/*
* 语音听写(iFly Auto Transform)技术能够实时地将语音转换成对应的文字。
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "qisr.h"
#include "msp_cmn.h"
#include "msp_errors.h"
#include "speech_recognizer.h"


#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>

#define FRAME_LEN	640 
#define	BUFFER_SIZE	4096
#define ASRCMD 		1

using namespace std;

bool recflag = true;
bool asrflag = false;
string result = "";

//打印信息
static void show_result(char *str, char is_over)
{
	asrflag = true; //set flag can publish msg to tuling topic
	printf("\rResult: [ %s ]", str);
	if(is_over)
		putchar('\n');
    string s(str);
	result = s;
    
}

static char *g_result = NULL;
static unsigned int g_buffersize = BUFFER_SIZE;

void on_result(const char *result, char is_last)
{
	if (result) {
		size_t left = g_buffersize - 1 - strlen(g_result);
		size_t size = strlen(result);
		if (left < size) {
			g_result = (char*)realloc(g_result, g_buffersize + BUFFER_SIZE);
			if (g_result)
				g_buffersize += BUFFER_SIZE;
			else {
				printf("mem alloc failed\n");
				return;
			}
		}
		strncat(g_result, result, size);
		show_result(g_result, is_last);
	}
}
void on_speech_begin()
{
	if (g_result)
	{
		free(g_result);
	}
	g_result = (char*)malloc(BUFFER_SIZE);
	g_buffersize = BUFFER_SIZE;
	memset(g_result, 0, g_buffersize);

	printf("Start Listening...\n");
}
//VAD检测断点
void on_speech_end(int reason)
{
	if (reason == END_REASON_VAD_DETECT)
	{
        printf("\nSpeaking done \n");
		recflag = false; //提前退出
	}
	else
        printf("\nRecognizer error %d\n", reason);
		
}


/* demo recognize the audio from microphone */
static void demo_mic(const char* session_begin_params)
{
	int errcode;
	int i = 0;

	struct speech_rec iat;

	struct speech_rec_notifier recnotifier = {
		on_result,
		on_speech_begin,
		on_speech_end
	};

	errcode = sr_init(&iat, session_begin_params, SR_MIC, &recnotifier);
	if (errcode) {
		printf("speech recognizer init failed\n");
		return;
	}
	errcode = sr_start_listening(&iat);
	if (errcode) {
		printf("start listen failed %d\n", errcode);
	}
	/* demo 15 seconds recording */
	/*这里是强制等待15秒*/
	// while(i++ < 15)
	// 	sleep(1);
	 
	while(recflag){
		sleep(1);
	} /* 这里是不强制等待15秒，若15秒内说完，就提前结束*/
	errcode = sr_stop_listening(&iat);
	if (errcode) {
		printf("stop listening failed %d\n", errcode);
	}

	sr_uninit(&iat);
}

//open mic,record,send voice to server,
//wait text
//打开麦克风进行监听
void asrProcess()
{
    int ret = MSP_SUCCESS;
	/* login params, please do keep the appid correct */
	const char* login_params = "appid = 599d4348, work_dir = .";
	
	/*
	* See "iFlytek MSC Reference Manual"
	*/
	const char* session_begin_params =
		"sub = iat, domain = iat, language = zh_cn, "
		"accent = mandarin, sample_rate = 16000, "
		"result_type = plain, result_encoding = utf8";

	/* Login first. the 1st arg is username, the 2nd arg is password
	 * just set them as NULL. the 3rd arg is login paramertes 
	 * */
	ret = MSPLogin(NULL, NULL, login_params);
	if (MSP_SUCCESS != ret)	{
		printf("MSPLogin failed , Error code %d.\n",ret);
		goto exit; // login fail, exit the program
	}

    demo_mic(session_begin_params);
	
  exit:
	MSPLogout(); // Logout...
	
}

//判断是否收到指定的指令，开启录音监控
void topicCallback(const std_msgs::Int32::ConstPtr &msg )
{
   ROS_INFO_STREAM("Now in topic Callback function...");
   if(msg->data == ASRCMD)
   {
	   asrProcess();
   }
}

/* main thread: start/stop record ; query the result of recgonization.
 * record thread: record callback(data write)
 * helper thread: ui(keystroke detection)
 */
int main(int argc, char* argv[])
{
    ros::init(argc, argv, "xf_asr_node");
	ros::NodeHandle nd;
	ros::Subscriber sub = nd.subscribe("/voice/xf_asr_topic", 1, topicCallback); //只能一次处理一条

    ros::Publisher pub = nd.advertise<std_msgs::String>("/voice/xf_record_topic", 10); //给/voice/tuling_arv_topic话题发布消息发布
    // ros::Publisher pub = nd.advertise<std_msgs::String>("/voice/tuling_arv_topic", 10);

	ros::Rate loop_rate(10); //循环的频率+

    while(ros::ok())
	{
		if(asrflag){
			std_msgs::String msg;
			msg.data = result; //asr response text asr返回的文本结果
			pub.publish(msg);  //发布消息内容
			asrflag = false;
			recflag = true; //重置断点检测true
		} //只有在返回有结果的时候发送消息

		loop_rate.sleep(); //强制等待       
		ros::spinOnce();
	}
   
	

	return 0;
}
