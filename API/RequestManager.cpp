//
//  Created on 06/10/14.
//  2014 palladion.it.
//

#include "RequestManager.h"
#include <fstream>

namespace api {
    
    using namespace std;
    
    //Set default path for file saving
    string RequestManager::path = "./streams/";
    
    CURL *RequestManager::handle = curl_easy_init();
    CURLcode RequestManager::response = CURLE_OK;
    
    //Private methods
    
    size_t RequestManager::WriteToBuffer(void *buffer, size_t size, size_t nmemb, void *userp)
    {
        ((string*)userp)->append((char*)buffer, size * nmemb);
        
        return size * nmemb;
    }
    
    size_t RequestManager::WriteToFile(void *buffer, size_t size, size_t nmemb, ofstream *fileP)
    {
        fileP->write((char*)buffer, size * nmemb);
        return size*nmemb;
    }
    
    //Protected methods
    
    //Public methods
    
    RequestManager::RequestManager()/* : handle(curl_easy_init())*/
    {
        
    }
    
    RequestManager::~RequestManager()
    {
        //curl_easy_cleanup(handle);
    }
    
    string RequestManager::RequestData(std::string url)
    {
        if (RequestManager::handle) {
            string data;
            curl_easy_setopt(RequestManager::handle, CURLOPT_WRITEFUNCTION, WriteToBuffer);
            //curl_easy_setopt(RequestManager::handle, CURLOPT_TIMEOUT, 10l);//may chose better timeout
            curl_easy_setopt(RequestManager::handle, CURLOPT_URL, url.c_str());
            curl_easy_setopt(RequestManager::handle, CURLOPT_WRITEDATA, &data);
            response = curl_easy_perform(RequestManager::handle);
            
            if (RequestManager::response != CURLE_OK) {
                printf("Request Manager - Error while retrieving data from url: %s\n", url.c_str());
            }
            
            return data;
        } else {
            printf("Request Manager - Error while retrieving data. No valid CURL handle.\n");
            return string();
        }
    }
    
    void RequestManager::RequestDataAsync(std::string url)
    {
        //TODO - implement
    }
    
    void RequestManager::DownloadData(std::string url, std::string path)
    {
        if (RequestManager::handle) {
            ofstream fStream;
            fStream.open(path, ios_base::out);
            
            if (fStream.fail()) {
                printf("ERROR - could not open file pointer for path: %s\n", path.c_str());
                return;
            }
            curl_easy_setopt(RequestManager::handle, CURLOPT_WRITEFUNCTION, WriteToFile);
            //curl_easy_setopt(RequestManager::handle, CURLOPT_TIMEOUT, 10l);//may chose better timeout
            curl_easy_setopt(RequestManager::handle, CURLOPT_URL, url.c_str());
            curl_easy_setopt(RequestManager::handle, CURLOPT_WRITEDATA, &fStream);
            response = curl_easy_perform(RequestManager::handle);
            fStream.close();
            
            if (RequestManager::response != CURLE_OK) {
                printf("Request Manager - Error while downloading data from url: %s\n", url.c_str());
            }
        }
    }
    
    void RequestManager::DownloadDataAsync(std::string url)
    {
        //TODO - implement
        //set filewrite in curl and preform async curl
    }
    
    void RequestManager::SetPath(std::string nPath)
    {
        RequestManager::path = nPath;
    }
    
    string RequestManager::GetPath()
    {
        return path;
    }
}