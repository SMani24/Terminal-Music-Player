/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#include "PlaylistsScreen.hpp"
#include "MainMenuScreen.hpp"
#include "Application.hpp"
#include "UIRenderer.hpp"
#include "InputHandler.hpp"
#include <iostream>
#include <string>

using namespace std;

void PlaylistsScreen::render() {
    UIRenderer::clearScreen();
    
    cout << COLOR_BLUE << "╔══════════════════════════════════════════════════════╗\n";
    cout << "║ " << COLOR_YELLOW << "Playlists                                            " << COLOR_BLUE << "║\n";
    cout << "╠══════════════════════════════════════════════════════╣\n";
    cout << "║ " << COLOR_CYAN << "#   Name                         Songs               " << COLOR_BLUE << "║\n";
    cout << "╠══════════════════════════════════════════════════════╣\n";

    auto& playlists = app->getPlaylists();
    Playlist* activePlaylist = app->getPlayer()->getCurrentPlaylist();

    for (size_t i = 0; i < playlists.size(); ++i) {
        bool isActive = (&playlists[i] == activePlaylist);
        
        string indexStr = to_string(i + 1);
        string nameStr = playlists[i].getName();
        string songsStr = to_string(playlists[i].getSongs().size());
        
        if (isActive) {
            nameStr = "▶ " + nameStr;
            songsStr += " [active]";
        } else {
            nameStr = "  " + nameStr;
        }

        string pIndex = indexStr;
        while(pIndex.length() < 3) pIndex += " ";
        pIndex += " ";

        int nameVisibleLength = nameStr.length();
        if (isActive) {
            nameVisibleLength -= 2;
        }
        if (nameStr.find("⭐") != string::npos) {
            nameVisibleLength -= 1; 
        }
        
        string pName = nameStr;
        int namePadding = 29 - nameVisibleLength;
        if (namePadding > 0) pName.append(namePadding, ' ');

        string pSongs = songsStr;
        int songsPadding = 19 - pSongs.length();
        if (songsPadding > 0) pSongs.append(songsPadding, ' ');

        string rowColor = isActive ? COLOR_GREEN : COLOR_RESET;
        
        cout << "║ " << rowColor << pIndex << pName << pSongs << COLOR_BLUE << " ║\n";
    }

    cout << COLOR_BLUE << "╠══════════════════════════════════════════════════════╣\n";
    cout << "║ " << COLOR_WHITE << "Enter number to switch active playlist. [0] back     " << COLOR_BLUE << "║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n" << COLOR_RESET;
    
    cout << COLOR_CYAN << "Choice: " << COLOR_RESET;
}

void PlaylistsScreen::handleInput() {
    auto& playlists = app->getPlaylists();
    
    int choice = InputHandler::readInt(0, playlists.size());

    if (choice == 0) {
        app->changeScreen(new MainMenuScreen(app));
    } else {
        Playlist* selectedPlaylist = &playlists[choice - 1];
        Playlist* activePlaylist = app->getPlayer()->getCurrentPlaylist();

        if (selectedPlaylist != activePlaylist) {
            app->getPlayer()->setPlaylist(selectedPlaylist);
            
            app->getConfig()->set("active_playlist", selectedPlaylist->getName());
        }
    }
}