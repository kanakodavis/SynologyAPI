//
//  Created on 26/09/14.
//  2014 palladion.it.
//

#ifndef SynologyAPI_Song_h
#define SynologyAPI_Song_h

#include <string>
#include "AudioInfo.h"
#include "Album.h"
#include "Album.h"

struct Song {
    int albumID;
    int year;
    int disc;
    std::string trackID;
    std::string title;
    std::string artist;
    Album album;
    std::string genre;
    Album salbum;
    AudioInfo info;
    
    std::string toString() {
        return std::string("Track: ") + title
        + std::string("\nID: ") + trackID
        + std::string("\nArtist: ") + artist
        + std::string("\nAlbum Artist: ") + album.albumArtist//May call album.toString();
        + std::string("\n# on Album: ") + std::to_string(albumID)
        + std::string("\nAlbum: ") + album.name
        + std::string("\nGenre: ") + genre
        + std::string("\nYear: ") + std::to_string(year)
        + std::string("\nDisc: ") + std::to_string(disc)
        + std::string("\nAudio Data: ") + info.toString();
    }
};

#endif

/*{

    "song_tag":{
        "album":"Boots Met My Face",
        "album_artist":"",
        "artist":"Admiral Fallow",
        "comment":"",
        "composer":"",
        "disc":1,
        "genre":"Independent",
        "track":1,
        "year":2010
    }
},
"id":"music_152",
"path":"/multimedia/music/iTunes Media/Music/Admiral Fallow/Boots Met My Face/01 Dead Against Smoking.m4a",
"title":"Dead Against Smoking",
"type":"file"
}*/