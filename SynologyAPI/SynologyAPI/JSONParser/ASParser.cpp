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
        return info;
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
        
        return song;
    }
    
    Album ASParser::ParseAlbum(json_t *node)
    {
        Album album;
        album.name = StringInNodeForKey(node, "name");
        album.name = StringInNodeForKey(node, "artist");
        album.name = StringInNodeForKey(node, "display_artist");
        album.name = StringInNodeForKey(node, "album_artist");
        album.name = IntInNodeForKey(node, "year");
        
        return album;
    }
    
    //Protected methods
    
    //Public methods
    
    vector<Song> ASParser::GetSongsFor(std::string album, std::string artist)
    {
        vector<Song> songs = vector<Song>();
        json_t *songRoot = NodeForKey(rootNode, "songs");
        vector<json_t *> jSongs = NodesInArray(songRoot);
        
        for (auto &song : jSongs) {
            Song tmpSong = ParseSong(song);
            
            if (tmpSong.artist.compare(artist) == 0 && tmpSong.album.compare(album) == 0) {
                //songs.push_back(ParseSong(song));
                songs.push_back(tmpSong);
            }
        }
        
        return songs;
    }
    
    vector<Album> ASParser::GetAlbumsFor(std::string artist)
    {
        vector<Album> albums = vector<Album>();
        json_t *albumRoot = NodeForKey(rootNode, "albums");//something terribly messed up here
        printf("This is array: %s\n", to_string(json_is_array(albumRoot)).c_str());
        vector<json_t *> jAlbums = NodesInArray(albumRoot); //or here
        
        for (auto &el : jAlbums) {
                printf("string: %s\n", json_string_value(el));
                printf("int val: %s\n", to_string(json_integer_value(el)).c_str());
                printf("is array: %s\n", to_string(json_is_array(el)).c_str());
                printf("is bool: %s\n", to_string(json_is_boolean(el)).c_str());
                printf("is object: %s\n", to_string(json_is_object(el)).c_str());
            printf("HERE! %s",to_string(json_is_object(json_object_get(el, "total"))).c_str());
            
        }
        
        //DELETE
        const char *key;
        void *iter = json_object_iter(albumRoot);
        //NODE FOR KEY DOES NOT FIND ALBUMROOT
        while (iter) {
            key = json_object_iter_key(iter);
            printf(key);
            iter = json_object_iter_next(albumRoot, iter);
        }
        
        printf("\n teeeest %s \n", json_string_value(albumRoot));
        //DELETE
        
        for (auto &album : jAlbums) {
            //Album tmpAlbum = ParseAlbum(album);
            albums.push_back(ParseAlbum(album));
        }
        
        return albums;
    }
}