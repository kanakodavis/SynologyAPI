//
//  AudioInfo.h
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 28/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#ifndef SynologyAPI_AudioInfo_h
#define SynologyAPI_AudioInfo_h

struct AudioInfo {
    int duration;
    int bitrate;
    int frequency;
    int channel;
    int filesize;
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
