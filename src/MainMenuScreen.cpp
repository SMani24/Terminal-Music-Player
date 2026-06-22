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

using namespace std;

void MainMenuScreen::render() {
    UIRenderer::printHeader("Terminal Music Player - Main Menu");
    
    string lastSong = app->getConfig()->get("last_song", "None");
    if (lastSong != "None") {
        cout << "Last played: " << lastSong << "\n\n";
    }

    cout << "1. Now Playing\n";
    cout << "2. Playlists\n";
    cout << "3. Browse Playlist\n";
    cout << "4. Settings\n";
    cout << "0. Quit (saves state)\n\n";
    cout << "Enter choice: ";
}

void MainMenuScreen::handleInput() {
    int choice = InputHandler::readInt(0, 4);

    switch (choice) {
        case 1:
            cout << "Now Playing Screen not implemented yet.\n";
            break;
        case 2:
            cout << "Playlists Screen not implemented yet.\n";
            break;
        case 3:
            cout << "Browse Screen not implemented yet.\n";
            break;
        case 4:
            cout << "Settings Screen not implemented yet.\n";
            break;
        case 0:
            app->shutdown();
            break;
    }
}