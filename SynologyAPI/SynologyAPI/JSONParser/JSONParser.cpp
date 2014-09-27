//
//  JSONParser.cpp
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 26/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#include "JSONParser.h"

namespace parser {
    
    using namespace std;
    
    JSONParser::JSONParser() : JSONParser(string())
    {
        
    }
    
    JSONParser::JSONParser(string json) : json_data(json)
    {
        rootNode = json_loads(json.c_str(), 0, &error);
    }
    
    JSONParser::~JSONParser( void )
    {
        
    }
    
    json_t* JSONParser::NodeForKey(json_t *node, const char *field_key)
    {
        const char *key;
        json_t *json_field;
        json_t *data = NULL;
        
        json_field = json_object_get(node, field_key);
        
        if (json_field == NULL) {
            void *iter = json_object_iter(node);
            
            while (iter) {
                key = json_object_iter_key(iter);
                
                data = NodeForKey(json_object_get(node, key), field_key);
                
                if (data != NULL) {
                    return data;
                }
                
                iter = json_object_iter_next(node, iter);
            }
        } else {
            return json_field;
        }
        
        return data;
    }
    
    string JSONParser::StringForKey(std::string key)
    {
        json_t *node = NodeForKey(rootNode, key.c_str());
        if (json_is_string(node)) {
            return json_string_value(node);
        }
        
        printf("LOG – Error parsing string from JSON");
        return string();
    }
    
    int JSONParser::IntForKey(std::string key)
    {
        json_t *node = NodeForKey(rootNode, key.c_str());
        if (json_is_integer(node)) {
            return json_integer_value(node);
        }
        
        printf("LOG – Error parsing int from JSON");
        return -1;
    }
    
    bool JSONParser::BoolForKey(std::string key)
    {
        json_t *node = NodeForKey(rootNode, key.c_str());
        if (json_is_boolean(node)) {
            return node->type == JSON_TRUE ? true : false;
        }
        
        printf("LOG – Error parsing boolean from JSON");
        return false;
    }
    
    void JSONParser::SetJSON(std::string json)
    {
        json_data = json;
        rootNode = json_loads(json.c_str(), 0, &error);
    }
}
