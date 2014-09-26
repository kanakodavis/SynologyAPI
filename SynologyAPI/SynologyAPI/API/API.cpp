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
    
    API::API(std::string proto, std::string adress, int prt) : protocol(proto), url(adress), port(prt)
    {
        
    }
    API::~API()
    {
        
    }
}