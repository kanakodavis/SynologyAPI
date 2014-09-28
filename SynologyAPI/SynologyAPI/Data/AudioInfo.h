//
//  AudioInfo.h
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 28/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#ifndef SynologyAPI_AudioInfo_h
#define SynologyAPI_AudioInfo_h

#include <string>

struct AudioInfo {
    int duration;
    int bitrate;
    int frequency;
    int channel;
    int filesize;
    
    std::string toString() {
        return std::string("Duration: ") + std::to_string(duration / 60)
        + std::string("\nBitrate: ") + std::to_string(bitrate)
        + std::string("\nFrequency: ") + std::to_string(frequency)
        + std::string("\nChannels: ") + std::to_string(channel)
        + std::string("\nFilesize: ") + std::to_string(filesize / 1000000);
    }
};

/*
 "song_audio":{
 "bitrate":1627000,
 "channel":2,
 "duration":346,
 "filesize":73664102,
 "frequency":44100
 },

 */

#endif
