//
//  AuthAPI.h
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 27/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#ifndef __SynologyAPI__AuthAPI__
#define __SynologyAPI__AuthAPI__

#include <stdio.h>

#include "API.h"

namespace api {
    
    class AuthAPI : public API {
    private:
        std::string serviceName;
        std::string aNamespace;
        std::string stationName;
        
        std::string sid;
    protected:
        //Creates the request with the parameters and returns the JSON requested from the server
        std::string RequestJSON(std::string api, std::string path, std::string method, std::map<std::string, std::string> params , int version);
    public:
        AuthAPI(std::string proto, std::string adress, int prt);
        ~AuthAPI();
        
        //Unencrypted! Login
        bool LogIn(std::string user, std::string pwd, std::string station); //maybe change to get station from subclass eg. call in AudioStationAPI provides this implicitly
        bool LogOut();
        bool IsLoggedIn();
    };
}

#endif /* defined(__SynologyAPI__AuthAPI__) */
