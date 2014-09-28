//
//  Song.h
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 28/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#ifndef SynologyAPI_Song_h
#define SynologyAPI_Song_h

#include <string>
#include "AudioInfo.h"

struct Song {
    int albumID;
    int year;
    int disc;
    std::string trackID;
    std::string title;
    std::string artist;
    std::string album;
    std::string albumArtist;
    std::string genre;
    AudioInfo info;
    
    std::string toString() {
        return std::string("Track: ") + title
        + std::string("\nID: ") + trackID
        + std::string("\nArtist: ") + artist
        + std::string("\nAlbum Artist: ") + albumArtist
        + std::string("\n# on Album: ") + std::to_string(albumID)
        + std::string("\nAlbum: ") + album
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