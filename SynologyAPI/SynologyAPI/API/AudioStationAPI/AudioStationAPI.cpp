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
        parser = parser::ASParser();
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
    
    vector<string> AudioStationAPI::GetSongs()
    {
        map<string, string> params{};
        params.insert(pair<string, string>("sort_direction", "asc"));
        params.insert(pair<string, string>("library", "all"));
        params.insert(pair<string, string>("limit", "5000"));
        params.insert(pair<string, string>("offset", "0"));
        AuthAPI::RequestJSON("Song", "AudioStation/song.cgi", "list", params, 1); //response is automatically set in parser
        
        return parser.StringsForKey("title");
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
    
    vector<string> AudioStationAPI::GetSongListFor(std::string artist, string album)
    {
        //%album=Boots%20Met%20My%20Face&album_artist=&library=all&artist=Admiral%20Fallow&limit=5000&offset=0&api=SYNO.AudioStation.Song&method=list&version=1&additional=song_tag%2Csong_audio %2c == ,
        
        
        map<string, string> params{};
        params.insert(pair<string, string>("album", album));
        //params.insert(pair<string, string>("album_artist", artist));
        params.insert(pair<string, string>("library", "all"));
        params.insert(pair<string, string>("artist", artist));
        params.insert(pair<string, string>("limit", "5000"));
        params.insert(pair<string, string>("offset", "0"));
        params.insert(pair<string, string>("additional", "song_tag,song_audio"));
        AuthAPI::RequestJSON("Song", "AudioStation/song.cgi", "list", params, 1); //response is automatically set in parser
        
        return parser.StringsForKey("title");
    }
    
    vector<string> AudioStationAPI::GetAlbumListFor(std::string artist)
    {
        //album.cgi
        //sort_direction=asc&library=all&artist=Admiral%20Fallow&api=SYNO.AudioStation.Album&limit=5000&offset=0&method=list&sort_by=name&version=1
        map<string, string> params{};
        params.insert(pair<string, string>("sort_direction", "asc"));
        params.insert(pair<string, string>("sorty_by", "name"));
        params.insert(pair<string, string>("library", "all"));
        params.insert(pair<string, string>("limit", "5000"));
        params.insert(pair<string, string>("offset", "0"));
        params.insert(pair<string, string>("artist", artist));
        AuthAPI::RequestJSON("Album", "AudioStation/album.cgi", "list", params, 1); //response is automatically set in parser
        
        return parser.StringsForKey("name");
    }
    
    vector<string> AudioStationAPI::GetAlbumsFor(std::string artist)
    {
        //SET RETURN VALUE TO ALBUM STRUCT
        
        //album.cgi
        //sort_direction=asc&library=all&artist=Admiral%20Fallow&api=SYNO.AudioStation.Album&limit=5000&offset=0&method=list&sort_by=name&version=1
        map<string, string> params{};
        params.insert(pair<string, string>("sort_direction", "asc"));
        params.insert(pair<string, string>("sorty_by", "name"));
        params.insert(pair<string, string>("library", "all"));
        params.insert(pair<string, string>("limit", "5000"));
        params.insert(pair<string, string>("offset", "0"));
        params.insert(pair<string, string>("artist", artist));
        AuthAPI::RequestJSON("Album", "AudioStation/album.cgi", "list", params, 1); //response is automatically set in parser
        
        return parser.StringsForKey("name");
    }
    
    void AudioStationAPI::GetArtworkFor(std::string artist, std::string album)
    {
        ///webapi/AudioStation/cover.cgi?api=SYNO.AudioStation.Cover&method=getcover&version=1&library=all&album_name=Boots%20Met%20My%20Face&album_artist_name=&artist_name=Admiral%20Fallow
        
        //RESPONSE: $ñGET /webapi/AudioStation/cover.cgi?api=SYNO.AudioStation.Cover&method=getcover&version=1&library=all&album_name=Boots%20Met%20My%20Face&album_artist_name=&artist_name=Admiral%20Fallow HTTP/1.1
        //Host: prometheus.palladion.it:5000
        //    Accept-Encoding: gzip, deflate
        //Accept: image/*
        //    Cookie: id=VfQR0vzQuqxt6A6GAN01157

    }
}