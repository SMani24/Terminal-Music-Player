/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */

#pragma once
#include "Song.hpp"
#include <vector>
#include <string>

class MusicLibrary {
private:
    std::vector<Song*> songs;

public:
    ~MusicLibrary();

    void addSong(Song* newSong);
    std::vector<Song*> getSongs() const;
    
    std::vector<Song*> filterByArtist(const std::string& artistName) const;
    std::vector<Song*> filterByAlbum(const std::string& albumName) const;
};