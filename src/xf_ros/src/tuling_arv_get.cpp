/*
 * tuling_arv.cpp
 * tuling_arv_node
*/ 

#include<ros/ros.h>
#include<std_msgs/String.h>
#include<iostream>
#include<sstream>
#include<jsoncpp/json/json.h>
#include<curl/curl.h>
#include<string>
#include<exception>
 
using namespace std;
 
int flag = 0;
string result; //声明全局变量
string strTemp;
 
 int writer(char *data, size_t size, size_t nmemb, string *writerData)
{
    unsigned long sizes = size * nmemb;
    if (writerData == NULL)
        return -1;
 
    writerData->append(data, sizes);
 
    return sizes;
}
 
/*
*   解析图灵服务器返回的Json string
*/
int parseJsonResonse(string input)
{
   Json::Value root;
   Json::Reader reader;
   bool parsingSuccessful = reader.parse(input, root);
   if(!parsingSuccessful)
   {
       std::cout<<"!!! Failed to parse the response data"<< std::endl;
        return -1;
   }
   const Json::Value answer = root["answer"];
   result = answer.asString(); //将返回的文本内容放到全局变量result中，在main中应用
   flag = 1; //可以让main函数中的while函数实现if处理
 
   std::cout<< "response answer:" << result << std::endl;
 
   return 0;
}
 
/*
*   将input字符发送到服务器接受
*/
unsigned char ToHex(unsigned char x)
{   
        return  x > 9 ? x + 55 : x + 48;   
}  
      
unsigned char FromHex(unsigned char x)
{   
        unsigned char y;  
        if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;  
        else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;  
        else if (x >= '0' && x <= '9') y = x - '0';  
        // else assert(0);  
        return y;  
}  
      
std::string UrlEncode(const std::string& str)
{  
   strTemp = "";  
   size_t length = str.length();  
   for (size_t i = 0; i < length; i++)  {  
        if (isalnum((unsigned char)str[i]) ||   
                (str[i] == '-') ||  
                (str[i] == '_') ||   
                (str[i] == '.') ||   
                (str[i] == '~'))  
                strTemp += str[i];  
            else if (str[i] == ' ')  
                strTemp += "+";  
            else  
            {  
                strTemp += '%';  
                strTemp += ToHex((unsigned char)str[i] >> 4);  
                strTemp += ToHex((unsigned char)str[i] % 16);  
            }  
        }  
        return strTemp;
        std::cout << "strTemp = input : " << strTemp <<std::endl;  
}


int HttpGetRequest(string input)
{
    string buffer;

    std::cout<<"get strJson: " << input << std::endl;
    
    UrlEncode(input);
    
    std::string url = "http://192.168.1.200:5000/chat/";
    url += strTemp;

    std::cout << "URL: "<< url << std::endl;

    
     try
    {
        CURL *curl;
        CURLcode res;
     
        curl_global_init(CURL_GLOBAL_ALL); //初始化

        curl = curl_easy_init();
     
       if(curl) 
       {
          curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

        //    curl_easy_setopt(curl, CURLOPT_HEADER, 0);

          curl_easy_setopt(curl, CURLOPT_URL, url.c_str());     
          curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //   curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);  //TODO：打开调试信息

        //   设置http头部的数据类型以及编码方式为UTF-8
          curl_slist *plist = curl_slist_append(NULL,
                "Content-Type:text/html; charset=utf-8");
          curl_easy_setopt(curl, CURLOPT_HTTPHEADER, plist); 
     
        //   curl_easy_setopt(curl, CURLOPT_POSTFIELDS, input);

          curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer); //缓冲区保存数据
 
          curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer); //将数据保存到buffer中(all)
      
          res = curl_easy_perform(curl); //执行请求
      
          if(res != CURLE_OK)
              fprintf(stderr, "curl_easy_perform() failed:%s\n", curl_easy_strerror(res));
     
      
          curl_easy_cleanup(curl); //成功后清空

        }
        curl_global_cleanup();  
    }
    catch (std::exception &ex)
    {
        printf("curl exception %s.\n", ex.what());
    }
    if(buffer.empty())
    {
      std::cout<< "!!! ERROR The Tuling sever response NULL" << std::endl;
    }
    else
    {
        parseJsonResonse(buffer); //返回的数据不为空，解析字符串
    }
 
    return 0;
 
}
 
/*
*   当voice/tuling_arv_topic话题有消息时，调用HttpGetRequest向服务器发送内容，返回结果。
*/
void arvCallBack(const std_msgs::String::ConstPtr &msg)
{
    std::cout<<"your quesion is: " << msg->data << std::endl;
    HttpGetRequest(msg->data); //发送问题以get方式
}
 
int main(int argc, char **argv)
{
    ros::init(argc, argv,"tuling_get_node");
    ros::NodeHandle nd;
 
    ros::Subscriber sub = nd.subscribe("/voice/tuling_arv_topic", 10, arvCallBack); //创建订阅图灵话题
    ros::Publisher pub = nd.advertise<std_msgs::String>("/voice/xf_tts_topic", 10); //发布消息的话题 xf_tts_topic
    ros::Rate loop_rate(10); //一秒10次处理的频率
 
    while(ros::ok())
    {
        if(flag)
        {
            std_msgs::String msg;
            msg.data = result;
            pub.publish(msg);
            flag = 0;
        } //当收到的消息有内容时 即flag=1
        ros::spinOnce();
        loop_rate.sleep();
    }
 
 
}
