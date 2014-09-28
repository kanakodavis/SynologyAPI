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
    
    //Private methods
    
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
    
    //Iterates over every node and if there is an array over all the nodes in the array
    //if node key matches the search string field_key then it will be added to the vector that will be returned
    vector<json_t *> JSONParser::NodesForKey(json_t *node, const char *field_key)
    {
        const char *key;
        json_t *json_field;
        json_t *data = NULL;
        vector<json_t *> nodes = vector<json_t *>();
        
        void *iter = json_object_iter(node);
        
        while (iter) {
            key = json_object_iter_key(iter);
            json_t *currentNode = json_object_get(node, key);
            
            if (json_is_array(currentNode)) {
                for (int i = 0; i < json_array_size(currentNode); i++) {
                    vector<json_t *> newNodes = NodesForKey(json_array_get(currentNode, i), field_key);
                    
                    nodes.insert(nodes.end(), newNodes.begin(), newNodes.end());
                }
            }
            
            if (strcmp(field_key, key) == 0) {
                nodes.push_back(currentNode);
            }
            
            vector<json_t *> newNodes = NodesForKey(currentNode, field_key);
            
            nodes.insert(nodes.end(), newNodes.begin(), newNodes.end());
            
            iter = json_object_iter_next(node, iter);
        }
        
        return nodes;
    }
    
    //Protected methods
    
    vector<json_t *> JSONParser::NodesInArray(json_t *node)
    {
        vector<json_t *> aElems = vector<json_t *>();
        if (json_is_array(node)) {
            size_t index;
            json_t *value;
            
            json_array_foreach(node, index, value)
            {
                aElems.push_back(value);
            }
            return aElems;
        }
        
        return aElems;
    }
    
    //Public methods
    
    string JSONParser::StringForKey(std::string key)
    {
        json_t *node = NodeForKey(rootNode, key.c_str());
        if (json_is_string(node)) {
            return json_string_value(node);
        }
        
        printf("LOG – Error parsing string from JSON");
        return string();
    }
    
    vector<string> JSONParser::StringsForKey(std::string key)
    {
        vector<string> strings = vector<string>();
        vector<json_t *>nodes = NodesForKey(rootNode, key.c_str());
        
        for (auto &node : nodes) {
            if (json_is_string(node)) {
                strings.push_back(json_string_value(node));
            }
        }
        
        return strings;
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
