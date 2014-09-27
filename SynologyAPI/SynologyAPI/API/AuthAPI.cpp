//
//  AuthAPI.cpp
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 27/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#include "AuthAPI.h"

namespace api {
    
    using namespace std;
    
    AuthAPI::AuthAPI(std::string proto, std::string adress, int prt) : api::API(proto, adress, prt, "SYNO", "API")
    {
        //Make serviceName and aNamespace static
        serviceName = "API";
        aNamespace = "SYNO";
    }
    
    AuthAPI::~AuthAPI()
    {
        
    }
    
    //Private methods
    
    //Protected methods
    
    //Public methods
    bool AuthAPI::LogIn(std::string user, std::string pwd, std::string station)
    {
        stationName = station;
        map<string, string> map{};
        map.insert(pair<string, string>("account", user));
        map.insert(pair<string, string>("passwd", pwd));
        map.insert(pair<string, string>("session", station));
        map.insert(pair<string, string>("format", "sid"));
        string response = API::RequestJSON("Auth", "auth.cgi", "login", map, 2);
        
        if (RequestStatus()) {
            sid = parser.StringForKey("sid");
            return true;
        }
        
        return false;
    }
    
    bool AuthAPI::LogOut()
    {
        map<string, string> map{};
        map.insert(pair<string, string>("session", stationName));
        map.insert(pair<string, string>("sid", sid));
        string response = API::RequestJSON("Auth", "auth.cgi", "logout", map, 1);
        
        if (RequestStatus()) {
            sid.empty();
            return true;
        }
        
        return false;
    }
    
    bool AuthAPI::IsLoggedIn()
    {
        return !sid.empty();
    }
}