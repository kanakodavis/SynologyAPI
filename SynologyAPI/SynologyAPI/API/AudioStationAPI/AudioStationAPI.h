//
//  AudioStationAPI.h
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 27/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#ifndef __SynologyAPI__AudioStationAPI__
#define __SynologyAPI__AudioStationAPI__

#include <stdio.h>
#include <vector>

#include "AuthAPI.h"
#include "ASParser.h"

namespace api {
    class AudioStationAPI : public AuthAPI {
    private:
        parser::ASParser asParser;
    protected:
    public:
        AudioStationAPI(std::string proto, std::string adress, int prt);
        ~AudioStationAPI();
        
        //Unencrypted Login
        bool LogIn(std::string user, std::string pwd);
        bool LogOut();
        bool IsLoggedIn();
        std::string SearchSong();
        std::vector<std::string> GetSongs();
        std::vector<std::string> GetArtists();
        std::vector<std::string> GetSongListFor(std::string artist, std::string album);
        std::vector<Song> GetSongsFor(std::string artist, std::string album);
        std::vector<std::string> GetAlbumListFor(std::string artist);
        std::vector<Album> GetAlbumsFor(std::string artist);
        void GetArtworkFor(std::string artist, std::string album);
        //covers for artist/album??
        //download song
    };
}

#endif /* defined(__SynologyAPI__AudioStationAPI__) */
