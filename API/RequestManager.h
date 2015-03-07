//
//  Created on 06/10/14.
//  2014 palladion.it.
//

#ifndef __SynologyAPI__RequestManager__
#define __SynologyAPI__RequestManager__

#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <fstream>
#include <iostream>

namespace api {
    
    class RequestManager {
    private:
        static std::string path;
        
        static CURL *handle;
        static CURLcode response;
        
        //Callback function for CURL - write to buffer
        static size_t WriteToBuffer(void *buffer, size_t size, size_t nmemb, void *userp);
        
        //Callback function for CURL - write to file
        static size_t WriteToFile(void *buffer, size_t size, size_t nmemb, std::ofstream *fileP);
    protected:
    public:
        RequestManager();
        ~RequestManager();
        
        static std::string RequestData(std::string url);
        
        static void RequestDataAsync(std::string url);
        
        static void DownloadData(std::string url, std::string path);
        
        static void DownloadDataAsync(std::string url);
        
        static void SetPath(std::string nPath);
        
        static std::string GetPath();
    };
}

#endif /* defined(__SynologyAPI__RequestManager__) */
