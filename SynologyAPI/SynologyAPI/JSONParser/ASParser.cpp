//
//  ASParser.cpp
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 28/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#include "ASParser.h"

namespace parser {
    
    using namespace std;
    
    ASParser::ASParser(string url) : parser::JSONParser(url)
    {
        
    }
    
    ASParser::~ASParser()
    {
        
    }
    
    //Private methods
    
    AudioInfo ASParser::ParseAudioInfo(json_t *node)
    {
        return AudioInfo();
    }
    
    Song ASParser::ParseSong(json_t *node)
    {
        return Song();
    }
    
    //Protected methods
    
    //Public methods
    
    vector<Song> ASParser::GetSongsFor(std::string album, std::string artist)
    {
        //write parser for song and audioInfo
        vector<Song> songs = vector<Song>();
        json_t *songRoot = NodeForKey(rootNode, "songs");
        vector<json_t *> jSongs = NodesInArray(songRoot);
        
        for (auto &song : jSongs) {
            songs.push_back(ParseSong(song));
        }
        
        return vector<Song>();
    }
}