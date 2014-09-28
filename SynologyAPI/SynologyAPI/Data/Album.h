//
//  Album.h
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 28/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#ifndef SynologyAPI_Album_h
#define SynologyAPI_Album_h

#include <string>

struct Album {
    int year;
    std::string name;
    std::string artist;
    std::string displayArtist;
    std::string albumArtist;
    
    std::string toString()
    {
        return std::string("Album: ") + name
        + std::string("\nArtist: ") + artist
        + std::string("\nDiplay Artist: ") + displayArtist
        + std::string("\nAlbum Artist: ") + albumArtist
        + std::string("\nYear: ") + std::to_string(year);
    }
};
#endif

/*
 {
 "data":{
 "albums":[
 {
 "album_artist":"",
 "artist":"Admiral Fallow",
 "display_artist":"Admiral Fallow",
 "name":"Boots Met My Face",
 "year":2010
 }
 ],
 "offset":0,
 "total":1
 },
 "success":true
 }
 */
