//
//  Created on 26/09/14.
//  2014 palladion.it.
//

#ifndef __SynologyAPI__AuthAPI__
#define __SynologyAPI__AuthAPI__

#include <stdio.h>

#include "API.h"

namespace api {
    
    class AuthAPI : public API {
    private:
        static const std::string authServiceName;
        static const std::string aNamespace;
        std::string stationName;
        std::string sid;
        
    protected:
        //Creates the request with the parameters and returns the JSON requested from the server
        std::string RequestJSON(std::string api, std::string path, std::string method, std::map<std::string, std::string> params , int version);
        
        //Get request URL
        std::string GetRequestURL(std::string api, std::string path, std::string method, std::map<std::string, std::string> params , int version);
        
    public:
        AuthAPI(std::string proto, std::string adress, int prt, std::string namespce, std::string service);
        ~AuthAPI();
        
        //Unencrypted! Login
        bool LogIn(std::string user, std::string pwd, std::string station);
        bool LogOut();
        bool IsLoggedIn();
    };
}

#endif /* defined(__SynologyAPI__AuthAPI__) */
