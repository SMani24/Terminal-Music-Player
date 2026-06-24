/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */

#pragma once
#include "Song.hpp"
#include <string>
#include <vector>

class Playlist {
private:
    std::string name;
    std::vector<Song*> songs;

public:
    Playlist(const std::string& name);
    
    void addSong(Song* song);
    std::string getName() const;
    std::vector<Song*> getSongs() const;
};