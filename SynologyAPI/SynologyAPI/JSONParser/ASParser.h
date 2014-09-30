//
//  Created on 26/09/14.
//  2014 palladion.it.
//

#ifndef __SynologyAPI__ASParser__
#define __SynologyAPI__ASParser__

#include <stdio.h>
#include <string>
#include <vector>

#include "JSONParser.h"
#include "Song.h"
#include "Audio.h"

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
        Audio GetSongFromData(std::string data, AudioType type);
    };
}

#endif /* defined(__SynologyAPI__ASParser__) */
