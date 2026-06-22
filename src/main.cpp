#include "MusicLibrary.hpp"
#include "CsvLoader.hpp"
#include "M3uLoader.hpp"
#include "Player.hpp"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    MusicLibrary myLibrary;
    CsvLoader::load("./Data/library.csv", myLibrary);
    Playlist discoDance = M3uLoader::load("./Data/Playlists/Disco_Dance.m3u", "Disco Dance", myLibrary);

    Player player;
    player.setPlaylist(&discoDance);

    cout << "Mini Terminal Player \n";
    cout << "Commands: [p]lay, [a]use, [r]esume, [s]top, [n]ext, [q]uit\n";
    
    player.play(0); 

    string input;
    bool running = true;

    while (running) {
        cout << "> ";
        cin >> input;

        if (input == "p") player.play();
        else if (input == "a") player.pause();
        else if (input == "r") player.resume();
        else if (input == "s") player.stop();
        else if (input == "n") player.next();
        else if (input == "q") {
            player.stop();
            running = false;
        }

        player.tick(); 
    }

    cout << "Exiting test environment.\n";
    return 0;
}