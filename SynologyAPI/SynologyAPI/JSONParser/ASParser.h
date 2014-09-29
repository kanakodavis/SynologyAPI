//
//  ASParser.h
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 28/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#ifndef __SynologyAPI__ASParser__
#define __SynologyAPI__ASParser__

#include <stdio.h>
#include <string>
#include <vector>

#include "JSONParser.h"
#include "Song.h"

namespace parser {
    class ASParser : public JSONParser {
    private:
        AudioInfo ParseAudioInfo(json_t *node);
        Song ParseSong(json_t *node);
        Album ParseAlbum(json_t *node);
    protected:
    public:
        ASParser();
        ASParser(std::string url);
        ~ASParser( void );
        
        std::string ParseInfo();
        std::vector<Song> GetSongsFor(std::string album, std::string artist);
        std::vector<Album> GetAlbumsFor(std::string artist);
    };
}

#endif /* defined(__SynologyAPI__ASParser__) */
