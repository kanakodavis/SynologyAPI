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
    
    AudioStationAPI::AudioStationAPI(string proto, string adress, int port) : api::AuthAPI(proto, adress, port)
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
        return vector<string>();
    }
    
    vector<string> AudioStationAPI::GetSongsForArtist(std::string artist)
    {
        return vector<string>();
    }
}