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
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

BrowseScreen::BrowseScreen(Application* appPtr) : Screen(appPtr) {
    showSortMenu = false;
    currentSort = SortCriteria::TITLE;
    sortAscending = true;

    Playlist* currentPlaylist = app->getPlayer()->getCurrentPlaylist();
    if (currentPlaylist != nullptr) {
        displayedSongs = currentPlaylist->getSongs();
        applySort();
    }
}

void BrowseScreen::applySort() {
    std::sort(displayedSongs.begin(), displayedSongs.end(), [this](Song* a, Song* b) {
        if (currentSort == SortCriteria::TITLE) {
            return sortAscending ? (a->getTitle() < b->getTitle()) : (a->getTitle() > b->getTitle());
        } else if (currentSort == SortCriteria::ARTIST) {
            return sortAscending ? (a->getArtist() < b->getArtist()) : (a->getArtist() > b->getArtist());
        } else if (currentSort == SortCriteria::ALBUM) {
            return sortAscending ? (a->getAlbum() < b->getAlbum()) : (a->getAlbum() > b->getAlbum());
        } else if (currentSort == SortCriteria::YEAR) {
            return sortAscending ? (a->getYear() < b->getYear()) : (a->getYear() > b->getYear());
        } else {
            return sortAscending ? (a->getDurationSec() < b->getDurationSec()) : (a->getDurationSec() > b->getDurationSec());
        }
    });
}

void BrowseScreen::render() {
    UIRenderer::clearScreen();
    
    Playlist* currentPlaylist = app->getPlayer()->getCurrentPlaylist();
    string playlistName = (currentPlaylist != nullptr) ? currentPlaylist->getName() : "None";
    int songCount = displayedSongs.size();

    cout << COLOR_BLUE << "╔══════════════════════════════════════════════════════╗\n";
    
    string sortName;
    switch (currentSort) {
        case SortCriteria::TITLE: sortName = "Title"; break;
        case SortCriteria::ARTIST: sortName = "Artist"; break;
        case SortCriteria::ALBUM: sortName = "Album"; break;
        case SortCriteria::YEAR: sortName = "Year"; break;
        case SortCriteria::DURATION: sortName = "Dur"; break;
    }
    
    string arrow = sortAscending ? "\xE2\x86\x91" : "\xE2\x86\x93"; // UTF-8 Up (↑) or Down (↓)
    
    string leftTitle = playlistName + " (" + to_string(songCount) + " songs)";
    string rightTitle = "Sort: " + sortName + " " + arrow;
    
    int rightTitleVisualLength = rightTitle.length() - 2; 
    
    int titleSpaces = 52 - leftTitle.length() - rightTitleVisualLength;
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
            string activeMarker = isActive ? "\xE2\x96\xB6 " : "  "; 
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
    if (!showSortMenu) {
        cout << "║ " << COLOR_WHITE << "[num] play song  [s] sort  [f] filter  [/] search   " << COLOR_BLUE << " ║\n";
        cout << "║ " << COLOR_WHITE << "[0] back                                            " << COLOR_BLUE << " ║\n";
        cout << "╚══════════════════════════════════════════════════════╝\n" << COLOR_RESET;
        cout << COLOR_CYAN << "Choice: " << COLOR_RESET;
    } else {
        cout << "║ " << COLOR_WHITE << "Sort by: 1.Title  2.Artist  3.Album  4.Year  5.Dur  " << COLOR_BLUE << " ║\n";
        cout << "║ " << COLOR_WHITE << "Add + for descending (e.g. 4+ for Year desc)        " << COLOR_BLUE << " ║\n";
        cout << "╚══════════════════════════════════════════════════════╝\n" << COLOR_RESET;
        cout << COLOR_CYAN << "Sort choice: " << COLOR_RESET;
    }
}

void BrowseScreen::handleInput() {
    string input = InputHandler::readLine();

    if (showSortMenu) {
        if (input == "1" || input == "1+") { currentSort = SortCriteria::TITLE; sortAscending = (input == "1"); }
        else if (input == "2" || input == "2+") { currentSort = SortCriteria::ARTIST; sortAscending = (input == "2"); }
        else if (input == "3" || input == "3+") { currentSort = SortCriteria::ALBUM; sortAscending = (input == "3"); }
        else if (input == "4" || input == "4+") { currentSort = SortCriteria::YEAR; sortAscending = (input == "4"); }
        else if (input == "5" || input == "5+") { currentSort = SortCriteria::DURATION; sortAscending = (input == "5"); }
        
        applySort();
        showSortMenu = false;
        return;
    }

    if (input == "0") {
        app->changeScreen(new MainMenuScreen(app));
    } else if (input == "s") {
        showSortMenu = true; 
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