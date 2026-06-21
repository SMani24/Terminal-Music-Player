/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */

#include "M3uLoader.hpp"
#include <fstream>
#include <iostream>

using namespace std;

Playlist M3uLoader::load(const string& filePath, const string& playlistName, const MusicLibrary& library) {
    Playlist playlist(playlistName);
    ifstream file(filePath);
    
    if (!file.is_open()) {
        cerr << "Could not open playlist file " << filePath << "\n";
        return playlist;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        bool found = false;
        for (Song* song : library.getSongs()) {
            if (song->getFilePath() == line) {
                playlist.addSong(song);
                found = true;
                break;
            }
        }

        if (!found) {
            cerr << "Song path '" << line << "' not found in library. Skipping.\n";
        }
    }

    file.close();
    return playlist;
}