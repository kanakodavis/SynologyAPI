//
//  Created on 26/09/14.
//  2014 palladion.it.
//

#ifndef __SynologyAPI__AudioStationAPI__
#define __SynologyAPI__AudioStationAPI__

#include <stdio.h>
#include <vector>
#include <thread>

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
        std::string GetInfo();
        Song SearchSong();
        std::vector<std::string> GetSongList();
        std::vector<Song> GetSongs();
        std::vector<std::string> GetArtists();
        std::vector<std::string> GetSongListFor(std::string artist, std::string album);
        std::vector<Song> GetSongsFor(std::string artist, std::string album);
        std::vector<std::string> GetAlbumListFor(std::string artist);
        std::vector<Album> GetAlbumsFor(std::string artist);
        std::vector<Song> GetID3sFor(std::string sId);
        Song GetID3For(std::string sId);
        void GetArtworkFor(std::string artist, std::string album);
        //covers for artist/album??
        Audio GetSongFor(std::string sId, AudioType type);
        void DownloadSongFor(std::string sId, std::string path, AudioType type);
        //BROKEN
        void GetStreamFor(std::string sId, AudioType type, char **buffer);
    };
}

#endif /* defined(__SynologyAPI__AudioStationAPI__) */
