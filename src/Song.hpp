/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#pragma once
#include <string>

class Song {
private:
    std::string title;
    std::string artist;
    std::string album;
    std::string genre;
    int year;
    int durationSec; 
    std::string filePath;

public:
    Song(const std::string& title, const std::string& artist, 
         const std::string& album, const std::string& genre, 
         int year, int durationSec, const std::string& filePath);

    std::string getTitle() const;
    std::string getArtist() const;
    std::string getAlbum() const;
    std::string getGenre() const;
    int getYear() const;
    int getDurationSec() const;
    std::string getFilePath() const;
};