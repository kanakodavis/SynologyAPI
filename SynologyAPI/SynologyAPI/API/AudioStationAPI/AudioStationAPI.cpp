//
//  Created on 26/09/14.
//  2014 palladion.it.
//

#include "AudioStationAPI.h"

namespace api {
    
    using namespace std;
    
    AudioStationAPI::AudioStationAPI(string proto, string adress, int port) : asParser(parser::ASParser()), api::AuthAPI(proto, adress, port, "SYNO", "")
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
    
    string AudioStationAPI::GetInfo()
    {
        string info = "AudioStation\n";
        map<string, string> params{};
        asParser.SetJSON(AuthAPI::RequestJSON("Info", "AudioStation/info.cgi", "getinfo", params, 1));
        
        return info.append(asParser.ParseInfo());
    }
    
    Song AudioStationAPI::SearchSong()
    {
        return Song();
    }
    
    vector<string> AudioStationAPI::GetSongList()
    {
        map<string, string> params{};
        params.insert(pair<string, string>("sort_direction", "asc"));
        params.insert(pair<string, string>("library", "all"));
        params.insert(pair<string, string>("limit", "100000")); //very high limit
        params.insert(pair<string, string>("offset", "0"));
        AuthAPI::RequestJSON("Song", "AudioStation/song.cgi", "list", params, 1);
        
        return parser.StringsForKey("title");
    }
    
    vector<Song> AudioStationAPI::GetSongs()
    {
        map<string, string> params{};
        params.insert(pair<string, string>("sort_direction", "asc"));
        params.insert(pair<string, string>("library", "all"));
        params.insert(pair<string, string>("limit", "100000")); //very high limit
        params.insert(pair<string, string>("offset", "0"));
        AuthAPI::RequestJSON("Song", "AudioStation/song.cgi", "list", params, 1);
        asParser.SetJSON(AuthAPI::RequestJSON("Song", "AudioStation/song.cgi", "list", params, 1));
        
        return asParser.GetSongs();
    }
    
    vector<string> AudioStationAPI::GetArtists()
    {
        map<string, string> params{};
        params.insert(pair<string, string>("sort_direction", "asc"));
        params.insert(pair<string, string>("library", "all"));
        params.insert(pair<string, string>("limit", "5000"));
        params.insert(pair<string, string>("offset", "0"));
        AuthAPI::RequestJSON("Artist", "AudioStation/artist.cgi", "list", params, 1);
        
        return parser.StringsForKey("name");
    }
    
    vector<string> AudioStationAPI::GetSongListFor(std::string artist, string album)
    {
        map<string, string> params{};
        params.insert(pair<string, string>("album", album));
        params.insert(pair<string, string>("library", "all"));
        params.insert(pair<string, string>("artist", artist));
        params.insert(pair<string, string>("limit", "5000"));
        params.insert(pair<string, string>("offset", "0"));
        params.insert(pair<string, string>("additional", "song_tag,song_audio"));
        AuthAPI::RequestJSON("Song", "AudioStation/song.cgi", "list", params, 1);
        
        return parser.StringsForKey("title");
    }
    
    std::vector<Song> AudioStationAPI::GetSongsFor(std::string artist, std::string album)
    {
        map<string, string> params{};
        params.insert(pair<string, string>("album", album));
        params.insert(pair<string, string>("library", "all"));
        params.insert(pair<string, string>("artist", artist));
        params.insert(pair<string, string>("limit", "5000"));
        params.insert(pair<string, string>("offset", "0"));
        params.insert(pair<string, string>("additional", "song_tag,song_audio"));
        asParser.SetJSON(AuthAPI::RequestJSON("Song", "AudioStation/song.cgi", "list", params, 1));
        return asParser.GetSongsFor(album, artist);
    }
    
    vector<string> AudioStationAPI::GetAlbumListFor(std::string artist)
    {
        map<string, string> params{};
        params.insert(pair<string, string>("sort_direction", "asc"));
        params.insert(pair<string, string>("sorty_by", "name"));
        params.insert(pair<string, string>("library", "all"));
        params.insert(pair<string, string>("limit", "5000"));
        params.insert(pair<string, string>("offset", "0"));
        params.insert(pair<string, string>("artist", artist));
        AuthAPI::RequestJSON("Album", "AudioStation/album.cgi", "list", params, 1);
        
        return parser.StringsForKey("name");
    }
    
    vector<Album> AudioStationAPI::GetAlbumsFor(std::string artist)
    {
        map<string, string> params{};
        params.insert(pair<string, string>("sort_direction", "asc"));
        params.insert(pair<string, string>("sorty_by", "name"));
        params.insert(pair<string, string>("library", "all"));
        params.insert(pair<string, string>("limit", "5000"));
        params.insert(pair<string, string>("offset", "0"));
        params.insert(pair<string, string>("artist", artist));
        asParser.SetJSON(AuthAPI::RequestJSON("Album", "AudioStation/album.cgi", "list", params, 1));
        
        return asParser.GetAlbumsFor(artist);
    }
    
    void AudioStationAPI::GetArtworkFor(std::string artist, std::string album)
    {
        
        //PACKAGE 411
        map<string, string> params{};
        params.insert(pair<string, string>("album_name", album));
        //params.insert(pair<string, string>("album_artist_name", ""));
        params.insert(pair<string, string>("library", "all"));
        params.insert(pair<string, string>("artist_name", artist));
        //May need to set another callback
        asParser.SetJSON(AuthAPI::RequestJSON("Cover", "AudioStation/cover.cgi", "getcover", params, 1));
        //asParser.SetJSON(AuthAPI::RequestJSON("Cover", "AudioStation/cover.cgi", "getcover", params, 1));
        
        ///webapi/AudioStation/cover.cgi?api=SYNO.AudioStation.Cover&method=getsongcover&version=1&library=all&id=music_152&_sid=VfQR0vzQuqxt6A6GAN01157
        
        ///webapi/AudioStation/cover.cgi?api=SYNO.AudioStation.Cover&method=getcover&version=1&library=all&album_name=Boots%20Met%20My%20Face&album_artist_name=&artist_name=Admiral%20Fallow
        
        //RESPONSE: $ñGET /webapi/AudioStation/cover.cgi?api=SYNO.AudioStation.Cover&method=getcover&version=1&library=all&album_name=Boots%20Met%20My%20Face&album_artist_name=&artist_name=Admiral%20Fallow HTTP/1.1
        //Host: redacted.url.com:5000
        //    Accept-Encoding: gzip, deflate
        //Accept: image/*
        //    Cookie: id=VfQR0vzQuqxt6A6GAN01157

    }
    
    Audio AudioStationAPI::GetSongFor(std::string sId, AudioType type)
    {
        map<string, string> params{};
        params.insert(pair<string, string>("id", sId));
        params.insert(pair<string, string>("position", "0"));
        if (type == MP3) {
            params.insert(pair<string, string>("format", "mp3"));
            params.insert(pair<string, string>("bitrate", "320000"));
        } else {
            params.insert(pair<string, string>("format", "wav"));
        }
        
        Audio song = asParser.GetSongFromData(AuthAPI::RequestJSON("Stream", "AudioStation/stream.cgi", "transcode", params, 1), type);
        
        return song;
    }
    
    //BROKEN
    void AudioStationAPI::GetStreamFor(std::string sId, AudioType type, char **buffer)
    {
        map<string, string> params{};
        params.insert(pair<string, string>("id", sId));
        params.insert(pair<string, string>("position", "0"));
        if (type == MP3) {
            params.insert(pair<string, string>("format", "mp3"));
            params.insert(pair<string, string>("bitrate", "320000"));
        } else {
            params.insert(pair<string, string>("format", "wav"));
        }
        
        string url = AuthAPI::GetRequestURL("Stream", "AudioStation/stream.cgi", "transcode", params, 1);
        
        thread asyncR(API::RequestAsync, url, buffer);
        
        //Detach to load in background
        asyncR.detach();
    }
}