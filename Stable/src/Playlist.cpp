/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */

#include "Playlist.hpp"

using namespace std;

Playlist::Playlist(const string& name) {
    this->name = name;
}

void Playlist::addSong(Song* song) {
    songs.push_back(song);
}

string Playlist::getName() const {
    return name;
}

vector<Song*> Playlist::getSongs() const {
    return songs;
}