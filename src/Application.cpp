/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#include "MainMenuScreen.hpp"
#include "Application.hpp"
#include "CsvLoader.hpp"
#include "M3uLoader.hpp"
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

Application::Application() : config("Data/settings.cfg"), activeScreen(nullptr), running(true) {}

Application::~Application() {
    if (activeScreen != nullptr) {
        delete activeScreen;
    }
}

void Application::init() {
    config.load();
    CsvLoader::load("Data/library.csv", library);
    
    string playlistDir = "Data/Playlists";
    if (fs::exists(playlistDir) && fs::is_directory(playlistDir)) {
        for (const auto& entry : fs::directory_iterator(playlistDir)) {
            if (entry.path().extension() == ".m3u") {
                string filename = entry.path().stem().string();
                playlists.push_back(M3uLoader::load(entry.path().string(), filename, library));
            }
        }
    } else {
        cerr << "Warning: Playlist directory not found at " << playlistDir << "\n";
    }

    string activePlaylistName = config.get("active_playlist", "");
    Playlist* startingPlaylist = nullptr;

    for (auto& pl : playlists) {
        if (pl.getName() == activePlaylistName) {
            startingPlaylist = &pl;
            break;
        }
    }

    if (!startingPlaylist && !playlists.empty()) {
        startingPlaylist = &playlists[0]; 
    }

    if (startingPlaylist) {
        player.setPlaylist(startingPlaylist);
    }

    activeScreen = new MainMenuScreen(this);
}

void Application::run() {
    while (running) {
        if (activeScreen) {
            activeScreen->render();
            activeScreen->handleInput();
        }
        
        player.tick();
        
        Song* currentSong = player.getCurrentSong();
        if (currentSong != nullptr) {
            string songDisplay = currentSong->getTitle() + " - " + currentSong->getArtist();
            config.set("last_song", songDisplay);
        }
    }
}

void Application::shutdown() {
    config.save();
    running = false;
}

void Application::changeScreen(Screen* newScreen) {
    if (activeScreen != nullptr) {
        delete activeScreen; 
    }
    activeScreen = newScreen; 
}