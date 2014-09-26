//
//  API.h
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 26/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#ifndef __SynologyAPI__API__
#define __SynologyAPI__API__

#include <stdio.h>
#include <string>
#include <curl/curl.h>
#include <vector>

#include "JSONParser.h"

namespace api {
    
    class API {
    private:
        std::string protocol;
        std::string url;
        int port;
        
        parser::JSONParser parser;
    protected:
    public:
        API(std::string proto, std::string adress, int prt);
        ~API();
    };
}

#endif /* defined(__SynologyAPI__API__) */
