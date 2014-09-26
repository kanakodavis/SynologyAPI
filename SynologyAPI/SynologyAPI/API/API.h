//
//  API.h
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 26/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#ifndef __SynologyAPI__API__
#define __SynologyAPI__API__

#include <stdio.h>
#include <string>
#include <map>
#include <curl/curl.h>

#include "JSONParser.h"

namespace api {
    
    class API {
        
    private:
        std::string protocol;
        std::string url;
        int port;
        CURL *curlHandle;
        CURLcode response;
        parser::JSONParser parser;
        
        //Callback function for CURL
        static size_t write_data(void * buffer, size_t size, size_t nmemb, void *userp);
        
    protected:
        std::string RequestJSON(std::string api, std::string path, std::string method, std::map<std::string, std::string> params , int version);
        
    public:
        API(std::string proto, std::string adress, int prt);
        ~API();
        
        std::string GetBaseUrl();
        
    };
}

#endif /* defined(__SynologyAPI__API__) */
