//
//  ID3.h
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 10/10/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#ifndef SynologyAPI_ID3_h
#define SynologyAPI_ID3_h

#include <string>

#include "Album.h"

struct ID3 {
    int disc;
    int year;
    int albumNr;
    std::string title;
    std::string artist;
    std::string genre;
    Album album;
    
    std::string toString()
    {
        return std::string("ID3 Tag: ")
        + std::string("\nTitle: ") + title
        + std::string("\nArtist: ") + artist
        + std::string("\nAlbum Nr: ") + std::to_string(albumNr)
        + std::string("\nAlbum: ") + album.toString()
        + std::string("\nGenre: ") + genre
        + std::string("\nDisc: ") + std::to_string(year)
        + std::string("\nYear: ") + std::to_string(year);
    }
};


#endif
