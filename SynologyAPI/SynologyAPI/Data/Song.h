//
//  Created on 26/09/14.
//  2014 palladion.it.
//

#ifndef SynologyAPI_Song_h
#define SynologyAPI_Song_h

#include <string>
#include "ID3.h"
#include "AudioInfo.h"
#include "Album.h"
#include "Audio.h"

struct Song {
    
    //New
    std::string sId;
    std::string title;
    ID3 id3Tag;
    AudioInfo aInfo;
    Audio audio;
    
    std::string toString() {
        return std::string("Track: ") + title
        + std::string("\nTrack-ID: ") + sId
        + std::string("\nID3: ") + id3Tag.toString()
        + std::string("\nAudio Info: ") + aInfo.toString();
    }
    
    friend
    bool operator==(const Song& s1, const Song& s2)
    {
        return s1.sId.compare(s2.sId)==0 ? true : false;
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