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
    
    API::API(std::string proto, std::string adress, int prt, string aNamespace, string service) : protocol(proto), url(adress), port(prt), apiNamespace(aNamespace), serviceName(service)
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
    
    string API::CreateRequestUrl(std::map<std::string, std::string> params)
    {
        string requestString;
        for (auto& iter : params) {
            requestString.append(iter.first);
            requestString.append("=");
            requestString.append(iter.second);
            requestString.append("&");
        }
        
        if (!requestString.empty()) {
            requestString.pop_back(); //Delete last char "&"
        }
        
        return requestString;
    }
    
    string API::GetAPIName(std::string api)
    {
        string apiName = apiNamespace;
        apiName.append(".");
        apiName.append(serviceName);
        apiName.append(".");
        apiName.append(api);
        return apiName;
    }
    
    void API::LogURL(std::string url)
    {
        printf("Call to URL: %s", url.c_str());
    }
    
    //Protected methods
    
    string API::RequestJSON(string api, string path, string method, map<string, string> params, int version)
    {
        string data;
        string requestUrl = GetBaseUrl();
        requestUrl.append(path);
        requestUrl.append("?");
        
        params.insert(pair<string, string>("api", GetAPIName(api)));
        params.insert(pair<string, string>("method", method));
        params.insert(pair<string, string>("version", to_string(version)));
        
        requestUrl.append(CreateRequestUrl(params));
        
        if (LOGGING) {
            LogURL(requestUrl);
        }
        
        curl_easy_setopt(curlHandle, CURLOPT_URL, requestUrl.c_str());
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &data);
        response = curl_easy_perform(curlHandle);
        
        if (LOGGING) {
            //LogURL(data);
        }
        
        parser.SetJSON(data);
        
        return data;
    }
    
    bool API::RequestStatus()
    {
        return parser.BoolForKey("success");;
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