/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#include "MainMenuScreen.hpp"
#include "Application.hpp"
#include "UIRenderer.hpp"
#include "InputHandler.hpp"
#include <iostream>
#include <string>

using namespace std;

void MainMenuScreen::render() {
    UIRenderer::clearScreen();
    
    cout << COLOR_CYAN << "╔══════════════════════════════════════════════════════╗\n";
    
    cout << "║ " << COLOR_YELLOW << "♫ Terminal Music Player ♫                            " << COLOR_CYAN << "║\n";
    cout << "╠══════════════════════════════════════════════════════╣\n";
    
    string lastSong = app->getConfig()->get("last_song", "None");
    string content = "Last played: " + lastSong;
    
    int spacesNeeded = 52 - content.length();
    
    if (spacesNeeded < 0) {
        content = content.substr(0, 48) + "...";
        spacesNeeded = 0;
    }
    
    string padding(spacesNeeded, ' ');
    
    cout << "║ " << COLOR_RESET << content << padding << COLOR_CYAN << " ║\n";
    cout << "╠══════════════════════════════════════════════════════╣\n";
    
    cout << "║ " << COLOR_RESET << "1. Now Playing                                       " << COLOR_CYAN << "║\n";
    cout << "║ " << COLOR_RESET << "2. Playlists                                         " << COLOR_CYAN << "║\n";
    cout << "║ " << COLOR_RESET << "3. Browse Playlist                                   " << COLOR_CYAN << "║\n";
    cout << "║ " << COLOR_RESET << "4. Settings                                          " << COLOR_CYAN << "║\n";
    cout << "╠══════════════════════════════════════════════════════╣\n";
    
    cout << "║ " << COLOR_RESET << "0. Quit (saves state)                                " << COLOR_CYAN << "║\n";
    
    cout << "╚══════════════════════════════════════════════════════╝\n" << COLOR_RESET;
    
    cout << "Enter choice: ";
}

void MainMenuScreen::handleInput() {
    int choice = InputHandler::readInt(0, 4);

    switch (choice) {
        case 1:
            cout << "\nNow Playing Screen not implemented yet.\n";
            InputHandler::pauseForUser();
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