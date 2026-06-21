/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#pragma once
#include "Playlist.hpp"
#include "MusicLibrary.hpp"
#include <string>

class M3uLoader {
public:
    static Playlist load(const std::string& filePath, const std::string& playlistName, const MusicLibrary& library);
};