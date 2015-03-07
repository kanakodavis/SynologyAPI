//
//  Created on 26/09/14.
//  2014 palladion.it.
//

#include "AuthAPI.h"

namespace api {
    
    using namespace std;
    
    const string AuthAPI::aNamespace = "SYNO";
    const string AuthAPI::authServiceName = "API";
    
    AuthAPI::AuthAPI(std::string proto, std::string adress, int prt, string namespce, string service) : api::API(proto, adress, prt, namespce.empty() ? aNamespace : namespce, service.empty() ? authServiceName : service)
    {
        
    }
    
    AuthAPI::~AuthAPI()
    {
        
    }
    
    //Private methods
    
    //Protected methods
    
    string AuthAPI::RequestJSON(std::string api, std::string path, std::string method, std::map<std::string, std::string> params, int version)
    {
        if (IsLoggedIn()) {
            params.insert(pair<string, string>("_sid", sid));
            return API::RequestJSON(api, path, method, params, version);
        }
        
        printf("Not logged in – could not retrieve data.\n");
        return string();
    }
    
    string AuthAPI::GetRequestURL(std::string api, std::string path, std::string method, std::map<std::string, std::string> params , int version)
    {
        if (IsLoggedIn()) {
            params.insert(pair<string, string>("_sid", sid));
            return API::GetRequestURL(api, path, method, params, version);
        }
        
        printf("Not logged in – could not retrieve data.\n");
        return string();
    }
    
    //Public methods
    bool AuthAPI::LogIn(std::string user, std::string pwd, std::string station)
    {
        stationName = station;
        map<string, string> params{};
        params.insert(pair<string, string>("account", user));
        params.insert(pair<string, string>("passwd", pwd));
        params.insert(pair<string, string>("session", station));
        params.insert(pair<string, string>("format", "sid"));
        string response = API::RequestJSON("Auth", "auth.cgi", "login", params, 2);
        
        if (RequestStatus()) {
            sid = parser.StringForKey("sid");
            API::serviceName = station;
            return true;
        }
        
        return false;
    }
    
    bool AuthAPI::LogOut()
    {
        API::serviceName = authServiceName;
        map<string, string> params{};
        params.insert(pair<string, string>("session", stationName));
        params.insert(pair<string, string>("sid", sid));
        string response = API::RequestJSON("Auth", "auth.cgi", "logout", params, 1);
        
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