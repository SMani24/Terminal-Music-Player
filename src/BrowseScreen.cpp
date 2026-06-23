/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#include "BrowseScreen.hpp"
#include "MainMenuScreen.hpp"
#include "NowPlayingScreen.hpp"
#include "Application.hpp"
#include "UIRenderer.hpp"
#include "InputHandler.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

BrowseScreen::BrowseScreen(Application* appPtr) : Screen(appPtr) {
    Playlist* currentPlaylist = app->getPlayer()->getCurrentPlaylist();
    if (currentPlaylist != nullptr) {
        displayedSongs = currentPlaylist->getSongs();
    }
}

void BrowseScreen::render() {
    UIRenderer::clearScreen();
    
    Playlist* currentPlaylist = app->getPlayer()->getCurrentPlaylist();
    string playlistName = (currentPlaylist != nullptr) ? currentPlaylist->getName() : "None";
    int songCount = displayedSongs.size();

    cout << COLOR_BLUE << "╔══════════════════════════════════════════════════════╗\n";
    
    string leftTitle = playlistName + " (" + to_string(songCount) + " songs)";
    string rightTitle = "Sort: Title \xE2\x86\x91";
    
    int titleSpaces = 52 - leftTitle.length() - 13;
    if (titleSpaces < 0) titleSpaces = 0;
    string titlePadding(titleSpaces, ' ');
    
    cout << "║ " << COLOR_YELLOW << leftTitle << titlePadding << rightTitle << COLOR_BLUE << " ║\n";
    cout << "╠══════════════════════════════════════════════════════╣\n";
    
    cout << "║ " << COLOR_CYAN << "#   Title                  Artist               Dur  " << COLOR_BLUE << "║\n";
    cout << "╠══════════════════════════════════════════════════════╣\n";

    if (displayedSongs.empty()) {
        cout << "║ " << COLOR_RED << left << setw(52) << setfill(' ') << "No songs to display." << COLOR_BLUE << " ║\n";
    } else {
        Song* currentlyPlaying = app->getPlayer()->getCurrentSong();

        for (size_t i = 0; i < displayedSongs.size(); ++i) {
            Song* song = displayedSongs[i];
            
            string idx = to_string(i + 1);
            if (idx.length() < 2) idx += " "; 
            
            bool isActive = (song == currentlyPlaying);
            string activeMarker = isActive ? "\xE2\x96\xB6 " : "  "; // UTF-8 Hex for Play Arrow (▶)
            string activeColor = isActive ? COLOR_GREEN : COLOR_WHITE;

            string t = song->getTitle();
            if (t.length() > 22) t = t.substr(0, 21) + ".";
            string titlePad(23 - t.length(), ' ');

            string a = song->getArtist();
            if (a.length() > 19) a = a.substr(0, 18) + ".";
            string artistPad(20 - a.length(), ' ');

            int mins = song->getDurationSec() / 60;
            int secs = song->getDurationSec() % 60;
            stringstream ss;
            ss << setfill('0') << setw(2) << mins << ":" << setfill('0') << setw(2) << secs;
            string dur = ss.str();

            cout << "║ " << COLOR_WHITE << idx << activeColor << activeMarker << COLOR_WHITE 
                 << t << titlePad << a << artistPad << dur << COLOR_BLUE << " ║\n";
        }
    }

    cout << "╠══════════════════════════════════════════════════════╣\n";
    cout << "║ " << COLOR_WHITE << "[num] play song  [s] sort  [f] filter  [/] search   " << COLOR_BLUE << " ║\n";
    cout << "║ " << COLOR_WHITE << "[0] back                                            " << COLOR_BLUE << " ║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n" << COLOR_RESET;
    
    cout << COLOR_CYAN << "Choice: " << COLOR_RESET;
}

void BrowseScreen::handleInput() {
    string input = InputHandler::readLine();

    if (input == "0") {
        app->changeScreen(new MainMenuScreen(app));
    } else if (input == "s") {
        cout << "\nSort Menu coming soon...\n";
        InputHandler::pauseForUser();
    } else if (input == "f") {
        cout << "\nFilter Menu coming soon...\n";
        InputHandler::pauseForUser();
    } else if (input == "/") {
        cout << "\nSearch Input coming soon...\n";
        InputHandler::pauseForUser();
    } else {
        try {
            int choice = stoi(input);
            if (choice > 0 && choice <= static_cast<int>(displayedSongs.size())) {
                Song* selectedSong = displayedSongs[choice - 1];
                
                Playlist* currentPlaylist = app->getPlayer()->getCurrentPlaylist();
                auto allSongs = currentPlaylist->getSongs();
                
                int originalIndex = 0;
                for (size_t i = 0; i < allSongs.size(); ++i) {
                    if (allSongs[i] == selectedSong) {
                        originalIndex = i;
                        break;
                    }
                }
                
                app->getPlayer()->play(originalIndex);
                app->changeScreen(new NowPlayingScreen(app));
            }
        } catch (const exception& e) {
            //Pass
        }
    }
}