//
//  API.cpp
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 26/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#include "API.h"

namespace api {
    
    using namespace std;
    
    API::API(std::string proto, std::string adress, int prt) : protocol(proto), url(adress), port(prt)
    {
        parser = parser::JSONParser();
        curlHandle = curl_easy_init();
        
        if (curlHandle) {
            curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
        }
    }
    API::~API()
    {
        curl_easy_cleanup(curlHandle);
    }
    
    //Private methods
    
    size_t API::write_data(void *buffer, size_t size, size_t nmemb, void *userp)
    {
        ((string*)userp)->append((char*)buffer, size * nmemb);
        return size * nmemb;
    }
    
    //Protected methods
    
    string API::RequestJSON(string api, string path, string method, map<string, string> params, int version)
    {
        //Iterate over params and create appropriate URL
        //send request
        //return json
        return string();
    }
    
    //Public methods
    
    string API::GetBaseUrl()
    {
        string baseUrl = protocol;
        baseUrl.append("://");
        baseUrl.append(url);
        baseUrl.append(":");
        baseUrl.append(to_string(port));
        baseUrl.append("/webapi/");
        return baseUrl;
    }
}