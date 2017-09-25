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
// #include <iconv.h>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"

#define FRAME_LEN	640 
#define	BUFFER_SIZE	4096
#define ASRCMD		1

using namespace std;

bool recflag = true;

int flag    = 0 ;
int flag_ok = 0 ;
int flag_no = 0 ;

static void show_result(char *string, char is_over)
{
    flag_ok=1;	
    printf("\rResult:[ %s ]",  string);
    if(is_over)
		putchar('\n');

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
        flag_no=1;
		printf("speech recognizer init failed\n");
		return;
	}
	errcode = sr_start_listening(&iat);
	if (errcode) {
		printf("start listen failed %d\n", errcode);
	}
	/* demo 15 seconds recording */
	while(i ++ <15)
		sleep(1);
	errcode = sr_stop_listening(&iat);
	if (errcode) {
        flag_no=1;
		printf("stop listening failed %d\n", errcode);
	}

	sr_uninit(&iat);
}


/* main thread: start/stop record ; query the result of recgonization.
 * record thread: record callback(data write)
 * helper thread: ui(keystroke detection)
 */

void WakeUp(const std_msgs::String::ConstPtr& msg)
{
    printf("waking up\r\n");
   // printf("%s", *msg->data.c_str());
    usleep(700*1000);
    flag=1;
}


int main(int argc, char* argv[])
{

    ros::init(argc, argv, "xf_asr_debug_node");
    ros::NodeHandle n;
    ros::Rate loop_rate(10);

    ros::Subscriber sbu = n.subscribe("/voice/xf_asr_topic", 1000, WakeUp);
    ros::Publisher pub1 = n.advertise<std_msgs::String>("/voice/tuling_arv_debug_topic", 1000);
    ros::Publisher pub2 = n.advertise<std_msgs::String>("/voice/xf_tts_topic", 1000);
    while(ros::ok())
    {

        if (flag){

	        int ret = MSP_SUCCESS;
    	    const char* login_params = "appid = 599d4348, work_dir = .";

	        const char* session_begin_params =
		        "sub = iat, domain = iat, language = zh_cn, "
		        "accent = mandarin, sample_rate = 16000, "
		        "result_type = plain, result_encoding = utf8";

	        ret = MSPLogin(NULL, NULL, login_params);
		    if(MSP_SUCCESS != ret){
                MSPLogout();
                printf("MSPLogin failed , Error code %d.\n",ret);
            }

            printf("Demo recognizing the speech from microphone\n");
		    printf("Speak in 15 seconds\n");

		    demo_mic(session_begin_params);

            printf("15 sec passed\n");
        
            flag=0;
            MSPLogout();
        }

        if(flag_ok){
			recflag = true;
            flag_ok=0;
            std_msgs::String msg;
            msg.data = g_result;
            pub1.publish(msg);
        }

        if(flag_no){
			recflag = true;
            flag_no=0;
            std_msgs::String msg;
            msg.data = "Sorry Please do it again";
            pub2.publish(msg);
        }

        ros::spinOnce();
        loop_rate.sleep();
    }

exit:
	MSPLogout(); // Logout...

	return 0;
}
