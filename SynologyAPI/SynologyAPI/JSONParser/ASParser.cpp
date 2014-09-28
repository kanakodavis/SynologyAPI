//
//  ASParser.cpp
//  SynologyAPI
//
//  Created by Matthias Gusenbauer on 28/09/14.
//  Copyright (c) 2014 palladion.it. All rights reserved.
//

#include "ASParser.h"

namespace parser {
    
    using namespace std;
    
    ASParser::ASParser() : ASParser(string())
    {
        
    }
    
    ASParser::ASParser(string url) : parser::JSONParser(url)
    {
        
    }
    
    ASParser::~ASParser()
    {
        
    }
    
    //Private methods
    
    AudioInfo ASParser::ParseAudioInfo(json_t *node)
    {
        AudioInfo info;
        info.duration = IntInNodeForKey(node, "duration");
        info.bitrate = IntInNodeForKey(node, "bitrate");
        info.frequency = IntInNodeForKey(node, "frequency");
        info.channel = IntInNodeForKey(node, "channel");
        info.filesize = IntInNodeForKey(node, "filesize");
        return AudioInfo();
    }
    
    Song ASParser::ParseSong(json_t *node)
    {
        json_t *tagNode = NodeForKey(node, "song_tag");
        
        Song song;
        song.albumID = IntInNodeForKey(tagNode, "track");
        song.year = IntInNodeForKey(tagNode, "year");
        song.disc = IntInNodeForKey(tagNode, "disc");
        song.trackID = StringInNodeForKey(node, "id");
        song.title = StringInNodeForKey(node, "title");
        song.artist = StringInNodeForKey(tagNode, "artist");
        song.album = StringInNodeForKey(tagNode, "album");
        song.albumArtist = StringInNodeForKey(tagNode, "album_artist");
        song.genre = StringInNodeForKey(tagNode, "genre");
        song.info = ParseAudioInfo(NodeForKey(node, "song_audio"));
        
        return Song();
    }
    
    //Protected methods
    
    //Public methods
    
    vector<Song> ASParser::GetSongsFor(std::string album, std::string artist)
    {
        //write parser for song and audioInfo
        vector<Song> songs = vector<Song>();
        json_t *songRoot = NodeForKey(rootNode, "songs");
        vector<json_t *> jSongs = NodesInArray(songRoot);
        
        for (auto &song : jSongs) {
            songs.push_back(ParseSong(song)); //open song_tag first
        }
        
        return vector<Song>();
    }
}