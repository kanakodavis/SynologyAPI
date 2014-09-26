//
//  JSONParser.h
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 26/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#ifndef __SynologyAPI__JSONParser__
#define __SynologyAPI__JSONParser__

#include <stdio.h>
#include <string>

#include "jansson.h"

namespace parser {
    
    class JSONParser {
    private:
        std::string json_data;
        json_t* rootNode;
        json_error_t error;
        
        //Returns first occurence of key
        json_t* NodeForKey(json_t *node, const char *key);
        
        //Returns all occurences of key
        //json_t[] NodesForKey(const char *key);
        
    protected:
    public:
        JSONParser();
        JSONParser(std::string json);
        ~JSONParser( void );
        
        std::string StringForKey(std::string key);
        int IntForKey(std::string key);
        bool BoolForKey(std::string key);
    };
}

#endif /* defined(__SynologyAPI__JSONParser__) */
