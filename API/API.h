//
//  Created on 26/09/14.
//  2014 palladion.it.
//

#ifndef __SynologyAPI__API__
#define __SynologyAPI__API__

#include <stdio.h>
#include <string>
#include <map>
#include <curl/curl.h>
#include <cctype>
#include <iomanip>
#include <sstream>

#include "JSONParser.h"
#include "RequestManager.h"

#define LOGGING true

namespace api {
    
    class API {
        
    private:
        std::string protocol;
        std::string url;
        std::string apiNamespace;
        int port;
        
        RequestManager dlManager;
        
        //Single blocking handle
        CURL *curlHandle;
        CURLcode response;
        
        //Callback function for CURL - JSON
        static size_t write_data(void * buffer, size_t size, size_t nmemb, void *userp);
        
        //Append params in the form of "&key=value"
        std::string CreateRequestUrl(std::map<std::string, std::string> params);
        
        //Log API calls
        void LogURL(std::string url);
        
        //Url encoding
        std::string EncodeURL(const std::string &url);
        
    protected:
        std::string serviceName;
        parser::JSONParser parser;
        
        //Creates the request with the parameters and returns the JSON requested from the server
        std::string RequestJSON(std::string api, std::string path, std::string method, std::map<std::string, std::string> params , int version);
        
        //Check for request success
        bool RequestStatus();
        
        //Get API name
        std::string GetAPIName(std::string api);
        
        //Set new parser
        void SetParser(parser::JSONParser cParser);
        
        //Get URL for request
        std::string GetRequestURL(std::string api, std::string path, std::string method, std::map<std::string, std::string> params , int version);
        
        //Static method to fetch data via CURL in new thread
        //BROKEN
        static void RequestAsync(std::string url, char **buffer);
        
    public:
        API(std::string proto, std::string adress, int prt, std::string aNamespace, std::string service);
        ~API();
        
        //Returns the base url of the API
        std::string GetBaseUrl();
    };
}

#endif /* defined(__SynologyAPI__API__) */
