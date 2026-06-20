/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */

#include "MusicLibrary.hpp"

using namespace std;

MusicLibrary::~MusicLibrary() {
    for (Song* song : songs) {
        delete song;
    }
    songs.clear();
}

void MusicLibrary::addSong(Song* newSong) {
    songs.push_back(newSong);
}

vector<Song*> MusicLibrary::getSongs() const {
    return songs;
}

vector<Song*> MusicLibrary::filterByArtist(const string& artistName) const {
    vector<Song*> filteredSongs;
    for (Song* song : songs) {
        if (song->getArtist() == artistName) {
            filteredSongs.push_back(song);
        }
    }
    return filteredSongs;
}

vector<Song*> MusicLibrary::filterByAlbum(const string& albumName) const {
    vector<Song*> filteredSongs;
    for (Song* song : songs) {
        if (song->getAlbum() == albumName) {
            filteredSongs.push_back(song);
        }
    }
    return filteredSongs;
}