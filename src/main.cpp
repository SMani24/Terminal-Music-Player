#include "MusicLibrary.hpp"
#include "CsvLoader.hpp"
#include "M3uLoader.hpp"
#include <iostream>

using namespace std;

int main() {
    MusicLibrary myLibrary;

    cout << "Testing Phase 1: CSV Loader \n";
    CsvLoader::load("../Data/library.csv", myLibrary);
    cout << "Success: Loaded " << myLibrary.getSongs().size() << " songs into the master library.\n\n";

    cout << "Testing Phase 2: M3U Loader \n";
    Playlist discoDance = M3uLoader::load("../Data/Playlists/Disco_Dance.m3u", "Disco Dance", myLibrary);
    
    cout << "Success: Playlist '" << discoDance.getName() << "' initialized with " 
         << discoDance.getSongs().size() << " valid songs:\n";
         
    for (Song* song : discoDance.getSongs()) {
        cout << " -> " << song->getTitle() << " by " << song->getArtist() << "\n";
    }

    cout << "\nMemory clean-up will occur automatically when myLibrary goes out of scope.\n";

    return 0;
}