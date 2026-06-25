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
    
    for (Song* song : library.getSongs()) {
        string key = "playcount_" + song->getFilePath(); 
        string countStr = config.get(key, "0");
        song->setPlayCount(stoi(countStr));

        string favKey = "favorite_" + song->getFilePath();
        string favStr = config.get(favKey, "0");
        song->setIsFavorite(favStr == "1");
    }
    
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

    Playlist mostPlayed("⭐ Most Played");
    vector<Song*> playedSongs;
    
    for (Song* s : library.getSongs()) {
        if (s->getPlayCount() > 0) {
            playedSongs.push_back(s);
        }
    }
    
    sort(playedSongs.begin(), playedSongs.end(), [](Song* a, Song* b) {
        return a->getPlayCount() > b->getPlayCount();
    });
    
    for (size_t i = 0; i < playedSongs.size() && i < 10; ++i) {
        mostPlayed.addSong(playedSongs[i]);
    }
    
    Playlist favorites("♥ Favourites");
    for (Song* s : library.getSongs()) {
        if (s->getIsFavorite()) {
            favorites.addSong(s);
        }
    }

    if (!favorites.getSongs().empty()) {
        playlists.insert(playlists.begin(), favorites);
    }
    if (!mostPlayed.getSongs().empty()) {
        playlists.insert(playlists.begin(), mostPlayed);
    }

    string activePlaylistName = config.get("active_playlist", "");
    string savedMode = config.get("playback_mode", "NO_REPEAT");
    if (savedMode == "REPEAT_ONE") {
        player.setMode(PlaybackMode::REPEAT_ONE);
    } else if (savedMode == "REPEAT_ALL") {
        player.setMode(PlaybackMode::REPEAT_ALL);
    } else if (savedMode == "SHUFFLE") {
        player.setMode(PlaybackMode::SHUFFLE);
    } else {
        player.setMode(PlaybackMode::NO_REPEAT);
    }
    
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
    for (Song* song : library.getSongs()) {
        if (song->getPlayCount() > 0) {
            string key = "playcount_" + song->getFilePath();
            config.set(key, to_string(song->getPlayCount()));
        }
        
        string favKey = "favorite_" + song->getFilePath();
        config.set(favKey, song->getIsFavorite() ? "1" : "0");
    }
    
    config.save();
    running = false;
}

void Application::changeScreen(Screen* newScreen) {
    if (activeScreen != nullptr) {
        delete activeScreen; 
    }
    activeScreen = newScreen; 
}