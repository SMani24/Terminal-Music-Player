/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#pragma once
#include "MusicLibrary.hpp"
#include "Player.hpp"
#include "ConfigManager.hpp"
#include "Screen.hpp"
#include <algorithm>
#include <vector>

class Application {
private:
    MusicLibrary library;
    Player player;
    ConfigManager config;
    std::vector<Playlist> playlists;
    
    Screen* activeScreen;
    bool running;

public:
    Application();
    ~Application();

    void init();
    void run();
    void shutdown();
    void changeScreen(Screen* newScreen);

    Player* getPlayer() { return &player; }
    ConfigManager* getConfig() { return &config; }    
    std::vector<Playlist>& getPlaylists() { return playlists; } 
};