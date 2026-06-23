/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#include "NowPlayingScreen.hpp"
#include "MainMenuScreen.hpp"
#include "InputHandler.hpp"
#include "Application.hpp"
#include "UIRenderer.hpp"
#include <iostream>
#include <string>

using namespace std;

void MainMenuScreen::render() {
    UIRenderer::clearScreen();
    
    cout << COLOR_BLUE << "╔══════════════════════════════════════════════════════╗\n";
    
    cout << "║ " << COLOR_YELLOW << "♫ Terminal Music Player ♫                            " << COLOR_BLUE << "║\n";
    
    string lastSong = app->getConfig()->get("last_song", ""); 
    
    if (!lastSong.empty()) {
        cout << COLOR_BLUE << "╠══════════════════════════════════════════════════════╣\n";
        
        string content = "Last played: " + lastSong;
        int spacesNeeded = 52 - content.length();
        
        if (spacesNeeded < 0) {
            content = content.substr(0, 48) + "...";
            spacesNeeded = 0;
        }
        
        string padding(spacesNeeded, ' ');
        
        cout << "║ " << COLOR_GREEN << content << padding << COLOR_BLUE << " ║\n";
    }
    
    cout << COLOR_BLUE << "╠══════════════════════════════════════════════════════╣\n";
    
    cout << "║ " << COLOR_CYAN << "1. " << COLOR_WHITE << "Now Playing                                       " << COLOR_BLUE << "║\n";
    cout << "║ " << COLOR_CYAN << "2. " << COLOR_WHITE << "Playlists                                         " << COLOR_BLUE << "║\n";
    cout << "║ " << COLOR_CYAN << "3. " << COLOR_WHITE << "Browse Playlist                                   " << COLOR_BLUE << "║\n";
    cout << "║ " << COLOR_CYAN << "4. " << COLOR_WHITE << "Settings                                          " << COLOR_BLUE << "║\n";
    cout << COLOR_BLUE << "╠══════════════════════════════════════════════════════╣\n";
    
    cout << "║ " << COLOR_RED << "0. " << COLOR_WHITE << "Quit (saves state)                                " << COLOR_BLUE << "║\n";
    
    cout << "╚══════════════════════════════════════════════════════╝\n" << COLOR_RESET;
    
    cout << COLOR_CYAN << "Enter choice: " << COLOR_RESET;
}

void MainMenuScreen::handleInput() {
    int choice = InputHandler::readInt(0, 4);

    switch (choice) {
        case 1:
            app->changeScreen(new NowPlayingScreen(app));
            break;
        case 2:
            cout << "\nPlaylists Screen not implemented yet.\n";
            InputHandler::pauseForUser();
            break;
        case 3:
            cout << "\nBrowse Screen not implemented yet.\n";
            InputHandler::pauseForUser();
            break;
        case 4:
            cout << "\nSettings Screen not implemented yet.\n";
            InputHandler::pauseForUser();
            break;
        case 0:
            app->shutdown();
            break;
    }
}