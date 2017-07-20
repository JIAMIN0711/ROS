//  url.cpp
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include "geturl.h"

using namespace std;
string strTemp;

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
//    std::cout <<"urlencode"<< std::endl;
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
 }