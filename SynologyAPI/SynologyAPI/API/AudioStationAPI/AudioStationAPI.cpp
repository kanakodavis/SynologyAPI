//
//  AudioStationAPI.cpp
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 27/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#include "AudioStationAPI.h"

namespace api {
    
    using namespace std;
    
    AudioStationAPI::AudioStationAPI(string proto, string adress, int port) : api::AuthAPI(proto, adress, port, "SYNO", "")
    {
        
    }
    
    AudioStationAPI::~AudioStationAPI()
    {
        
    }
    
    //Private methods
    
    //Protected methods
    
    //Public methods
    bool AudioStationAPI::LogIn(std::string user, std::string pwd)
    {
        return AuthAPI::LogIn(user, pwd, "AudioStation");
    }
    
    bool AudioStationAPI::LogOut()
    {
        return AuthAPI::LogOut();
    }
    
    bool AudioStationAPI::IsLoggedIn()
    {
        return AuthAPI::IsLoggedIn();
    }
    
    string AudioStationAPI::SearchSong()
    {
        return string();
    }
    
    vector<string> AudioStationAPI::GetArtists()
    {
        map<string, string> params{};
        params.insert(pair<string, string>("sort_direction", "asc"));
        params.insert(pair<string, string>("library", "all"));
        params.insert(pair<string, string>("limit", "5000"));
        params.insert(pair<string, string>("offset", "0"));
        AuthAPI::RequestJSON("Artist", "AudioStation/artist.cgi", "list", params, 1); //response is automatically set in parser
        
        return parser.StringsForKey("name");
    }
    
    vector<string> AudioStationAPI::GetSongsForArtist(std::string artist)
    {
        return vector<string>();
    }
}