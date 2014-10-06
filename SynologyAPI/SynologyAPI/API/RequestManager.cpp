//
//  Created on 06/10/14.
//  2014 palladion.it.
//

#include "RequestManager.h"

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
    
    size_t RequestManager::WriteToFile(void *buffer, size_t size, size_t nmemb, FILE *fileP)
    {
        //size_t written;
        //written = fwrite(buffer, size, nmemb, fileP);
        /*ofstream outStream;
        char *name = (char*)userp; //need to set userp if filewrite
        outStream.open((path + name).c_str());
        outStream.write(buffer, sizeof(char)*strlen(buffer));*/
        
        //SETUP WITH
        /*
         CURL *curl;
         FILE *fp;
         CURLcode res;
         char *url = "http://localhost/aaa.txt";
         char outfilename[FILENAME_MAX] = "C:\\bbb.txt";
         curl = curl_easy_init();
         if (curl) {
         fp = fopen(outfilename,"wb");
         curl_easy_setopt(curl, CURLOPT_URL, url);
         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
         curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
         res = curl_easy_perform(curl);
         curl_easy_cleanup(curl);
         fclose(fp);
         */
        return fwrite(buffer, size, nmemb, fileP);
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
    
    void RequestManager::DownloadData(std::string url)
    {
        if (RequestManager::handle) {
            FILE *fp;
            curl_easy_setopt(RequestManager::handle, CURLOPT_WRITEFUNCTION, WriteToBuffer);
            curl_easy_setopt(RequestManager::handle, CURLOPT_URL, url.c_str());
            curl_easy_setopt(RequestManager::handle, CURLOPT_WRITEDATA, &fp);
            response = curl_easy_perform(RequestManager::handle);
            fclose(fp);
            
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