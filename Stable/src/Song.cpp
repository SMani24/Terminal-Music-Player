/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */

#include "Song.hpp"

using namespace std;

Song::Song(const string& title, const string& artist, 
           const string& album, const string& genre, 
           int year, int durationSec, const string& filePath) {
    this->title = title;
    this->artist = artist;
    this->album = album;
    this->genre = genre;
    this->year = year;
    this->durationSec = durationSec;
    this->filePath = filePath;
}

string Song::getTitle() const { return title; }
string Song::getArtist() const { return artist; }
string Song::getAlbum() const { return album; }
string Song::getGenre() const { return genre; }
int Song::getYear() const { return year; }
int Song::getDurationSec() const { return durationSec; }
string Song::getFilePath() const { return filePath; }