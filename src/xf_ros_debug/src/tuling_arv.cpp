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
string result, number; //声明全局变量

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
       std::cout<<"Failed to parse the response data"<< std::endl;
        return -1;
   }
   const Json::Value code = root["code"];
   const Json::Value text = root["text"];
  // const Json::Value answer = root["answer"];
   result = text.asString(); //将返回的文本内容放到全局变量result中，在main中应用
   number = code.asString();
   flag = 1; //可以让main函数中的while函数实现if处理
 
   std::cout<< "response code:" << number << std::endl;
   std::cout<< "response text:" << result << std::endl;
 
   return 0;
}
 
/*
*   将input字符发送到图灵服务器接受json string
*/
int HttpPostRequest(string input)
{
    string buffer;
    //组装字符串的格式为json
    std::string strJson = "{";
    // strJson += "\"key\" : \"1bf4cfd53fea4ee09f327822c53ad20c\","; //双引号前加 \ 防转义
    strJson += "\"key\" : \"7368a378db554415b2ff1afa18e3515e\",";
    strJson += "\"info\" : ";
    strJson += "\"";
    strJson += input;
    strJson += "\"";
    strJson += "}";
 
    std::cout<<"post json string: " << strJson << std::endl;
 

     try
    {
        CURL *pCurl = NULL;
        CURLcode res;
        // In windows, this will init the winsock stuff
        curl_global_init(CURL_GLOBAL_ALL); //初始化
 
        // get a curl handle
        pCurl = curl_easy_init();
        if (NULL != pCurl)
        {
            // 设置超时时间为10秒
            curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 10);
 
            // First set the URL that is about to receive our POST.
            // This URL can just as well be a
            // https:// URL if that is what should receive the data.发送的api地址
            curl_easy_setopt(pCurl, CURLOPT_URL, "http://www.tuling123.com/openapi/api");
            
            // curl_easy_setopt(pCurl, CURLOPT_VERBOSE, 1L);
 
            // 设置http发送的内容类型为JSON 编码方式为UTF-8 (get)
            curl_slist *plist = curl_slist_append(NULL,
                "Content-Type:application/json;charset=UTF-8");
            curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, plist); 
  
            // 设置要POST的JSON数据
            curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, strJson.c_str());   //指定post内容（post）
 
            curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, writer); //缓冲区保存数据
 
            curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &buffer); //将数据保存到buffer中(all)
 
            // Perform the request, res will get the return code
            res = curl_easy_perform(pCurl); //执行请求

            // Check for errors
            if (res != CURLE_OK)
            {
                printf("curl_easy_perform() failed:%s\n", curl_easy_strerror(res));
            }
            // always cleanup
            curl_easy_cleanup(pCurl); //成功后清空
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
*   当voice/tuling_arv_topic话题有消息时，调用HttpPostRequest向图灵服务器发送内容，返回结果。
*/
void arvCallBack(const std_msgs::String::ConstPtr &msg)
{
    std::cout<<"your quesion is: " << msg->data << std::endl;
    HttpPostRequest(msg->data); //发送问题以post方式
}
 
int main(int argc, char **argv)
{
    ros::init(argc, argv,"tuling_arv_debug_node");
    ros::NodeHandle nd;
 
    ros::Subscriber sub = nd.subscribe("/voice/tuling_arv_debug_topic", 10, arvCallBack); //创建订阅图灵话题
    ros::Publisher pub = nd.advertise<std_msgs::String>("/voice/xf_tts_topic", 10); //发布消息的话题 xf_tts_topic
    // ros::Publisher pub1 = nd.advertise<std_msgs::String>("/voice/android_topic",10);
    ros::Rate loop_rate(10); //一秒10次处理的频率
 
    while(ros::ok())
    {
        if(flag)
        {
            std_msgs::String msg;
            // std_msgs::String num;
            // num.data = number;
            msg.data = result;
            pub.publish(msg);
            // pub1.publish(num);
            flag = 0;
        } //当收到的消息有内容时 即flag=1
        ros::spinOnce();
        loop_rate.sleep();
    }
 
 
}
