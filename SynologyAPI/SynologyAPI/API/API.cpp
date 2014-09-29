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
        
        return EncodeURL(requestString);
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
        printf("Call to URL: %s \n", url.c_str());
    }
    
    string API::EncodeURL(const std::string &url)
    {
        ostringstream escaped;
        escaped.fill('0');
        escaped << hex;
        
        for (string::const_iterator i = url.begin(), n = url.end(); i != n; ++i) {
            string::value_type c = (*i);
            
            // Keep alphanumeric and other accepted characters intact
            if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~' || c == '=' || c == '&') {
                escaped << c;
                continue;
            }
            
            // Any other characters are percent-encoded
            escaped << '%' << setw(2) << int((unsigned char) c);
        }
        
        return escaped.str();
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
    
    void API::SetParser(parser::JSONParser cParser)
    {
        this->parser = cParser;
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