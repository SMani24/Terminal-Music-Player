/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#include "NowPlayingScreen.hpp"
#include "PlaylistsScreen.hpp"
#include "MainMenuScreen.hpp"
#include "SettingsScreen.hpp"
#include "InputHandler.hpp"
#include "Application.hpp"
#include "UIRenderer.hpp"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void MainMenuScreen::render() {
    UIRenderer::clearScreen();
    
    cout << COLOR_BLUE << "╔══════════════════════════════════════════════════════╗\n";
    cout << "║ " << COLOR_YELLOW << left << setw(52) << setfill(' ') << "♫ Terminal Music Player ♫" << COLOR_BLUE << "     ║\n";
    
    string lastSong = app->getConfig()->get("last_song", ""); 
    
    if (!lastSong.empty()) {
        cout << COLOR_BLUE << "╠══════════════════════════════════════════════════════╣\n";
        
        string content = "Last played: " + lastSong;
        
        if (content.length() > 52) {
            content = content.substr(0, 49) + "...";
        }
        
        cout << "║ " << COLOR_GREEN << left << setw(52) << setfill(' ') << content << COLOR_BLUE << " ║\n";
    }
    
    cout << COLOR_BLUE << "╠══════════════════════════════════════════════════════╣\n";
    
    cout << "║ " << COLOR_CYAN << "1. " << COLOR_WHITE << left << setw(49) << setfill(' ') << "Now Playing" << COLOR_BLUE << " ║\n";
    cout << "║ " << COLOR_CYAN << "2. " << COLOR_WHITE << left << setw(49) << setfill(' ') << "Playlists" << COLOR_BLUE << " ║\n";
    cout << "║ " << COLOR_CYAN << "3. " << COLOR_WHITE << left << setw(49) << setfill(' ') << "Browse Playlist" << COLOR_BLUE << " ║\n";
    cout << "║ " << COLOR_CYAN << "4. " << COLOR_WHITE << left << setw(49) << setfill(' ') << "Settings" << COLOR_BLUE << " ║\n";
    cout << COLOR_BLUE << "╠══════════════════════════════════════════════════════╣\n";
    
    cout << "║ " << COLOR_RED << "0. " << COLOR_WHITE << left << setw(49) << setfill(' ') << "Quit (saves state)" << COLOR_BLUE << " ║\n";
    
    cout << COLOR_BLUE << "╚══════════════════════════════════════════════════════╝\n" << COLOR_RESET;
    
    cout << COLOR_CYAN << "Enter choice: " << COLOR_RESET;
}

void MainMenuScreen::handleInput() {
    int choice = InputHandler::readInt(0, 4);

    switch (choice) {
        case 1:
            app->changeScreen(new NowPlayingScreen(app));
            break;
        case 2:
            app->changeScreen(new PlaylistsScreen(app));
            break;
        case 3:
            cout << "\nBrowse Screen not implemented yet.\n";
            InputHandler::pauseForUser();
            break;
        case 4:
            app->changeScreen(new SettingsScreen(app));
            break;
        case 0:
            app->shutdown();
            break;
    }
}