/*
 * tuling_arv.cpp
 * tuling_arv_node
*/ 

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <jsoncpp/json/json.h>
#include <curl/curl.h>
#include <string>
#include <exception>
#include "geturl.h"
 
using namespace std;
 
int flag = 0;
int server = 0;
string result; //声明全局变量
string question;
 
 int writer(char *data, size_t size, size_t nmemb, string *writerData)
{
    unsigned long sizes = size * nmemb;
    if (writerData == NULL)
        return -1;
 
    writerData->append(data, sizes);
 
    return sizes;
}
 
/*
*   解析服务器返回的Json string
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

   if(!server){
     const Json::Value answer = root["answer"];
     result = answer.asString(); //将返回的文本内容放到全局变量result中，在main中应用
    //  std::cout<<"(4)result: "<< result << std::endl;
     if(result =="no"){
          
        //   std::cout<<"(4.2.1)TO tuling "<< std::endl;
          server = 1;
        //   std::cout<<"(4.2.2)server: "<<server<< std::endl;
          HttpPostRequest(question);
     }
     else{
        flag = 1; //可以让main函数中的while函数实现if处理
        std::cout<< "response answer:" << result << std::endl;
     }
   }
   else{
     const Json::Value code = root["code"];
     const Json::Value text = root["text"];
     result = text.asString();
     flag = 1; //可以让main函数中的while函数实现if处理
     server = 0;
     std::cout<< "response text:" << result << std::endl;

   }
   return 0;
}
/*
* 访问公司的服务器
*/ 
int HttpGetRequest(string input)
{
    string buffer;

    // std::cout<<"(2)get input: " << input << std::endl;
    
    UrlEncode(input);

    question = input;
    
    std::string url = "http://192.168.1.200:5000/chat/";
    url += strTemp;

    // std::cout << "(3)URL: "<< url << std::endl;   
 
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
              result = "对不起，服务器访问错误，请检查后再使用";
              flag = 1; //可以让main函数中的while函数实现if处理
      
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
      std::cout<< "ERROR The sever response NULL" << std::endl;
    }
    else
    {
        parseJsonResonse(buffer); //返回的数据不为空，解析字符串
    }
    return 0;
}

/*
* 访问图灵服务器
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
 
    // std::cout<<"post json string: " << strJson << std::endl;
 

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
*   当voice/tuling_arv_topic话题有消息时，调用HttpGetRequest向服务器发送内容，返回结果。
*/
void arvCallBack(const std_msgs::String::ConstPtr &msg)
{
    std::cout<<"your question is: " << msg->data << std::endl;
    HttpGetRequest(msg->data); //发送问题以get方式
}
 
int main(int argc, char **argv)
{
    ros::init(argc, argv,"xf_record_node");
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
