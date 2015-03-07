//
//  Audio.h
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 30/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#ifndef SynologyAPI_Audio_h
#define SynologyAPI_Audio_h

#include <string>

typedef enum {MP3, WAV} AudioType;

struct Audio {
    std::string name;
    char *data;
    unsigned long length;
    AudioType type;
};

#endif
