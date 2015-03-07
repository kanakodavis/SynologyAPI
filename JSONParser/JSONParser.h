//
//  Created on 26/09/14.
//  2014 palladion.it.
//

#ifndef __SynologyAPI__JSONParser__
#define __SynologyAPI__JSONParser__

#include <stdio.h>
#include <string>
#include <vector>

#include "jansson.h"

namespace parser {
    
    class JSONParser {
    private:
        json_error_t error;
        
    protected:
        std::string json_data;
        json_t* rootNode;
        
        //Returns first occurence of key
        json_t* NodeForKey(json_t *node, const char *key);
        
        //Returns all occurences of key
        std::vector<json_t *> NodesForKey(json_t *node, const char *key);
        
        //Param node must contain an array
        //Returns all childnodes in array
        std::vector<json_t *> NodesInArray(json_t *node);
        
        std::string StringInNodeForKey(json_t *node, std::string key);
        int IntInNodeForKey(json_t *node, std::string key);
        bool BoolInNodeForKey(json_t *node, std::string key);
        
    public:
        JSONParser();
        JSONParser(std::string json);
        ~JSONParser( void );
        
        void SetJSON(std::string json);
        void SetRootNode(json_t *root);
        std::string StringForKey(std::string key);
        std::vector<std::string> StringsForKey(std::string key);
        int IntForKey(std::string key);
        bool BoolForKey(std::string key);
        
    };
}

#endif /* defined(__SynologyAPI__JSONParser__) */
