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
    int trackID;
    //int disc
    string title;
    string artist;
    string album;
    string albumArtist;
    string genre;
    AudioInfo info;
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