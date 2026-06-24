/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#include "FilterScreen.hpp"
#include "Application.hpp"
#include "UIRenderer.hpp"
#include "InputHandler.hpp"
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

FilterScreen::FilterScreen(Application* appPtr) : Screen(appPtr) {
    state = FilterState::SELECT_CATEGORY;
    selectedCategory = FilterType::NONE;
}

void FilterScreen::loadItems() {
    filterItems.clear();
    Playlist* currentPlaylist = app->getPlayer()->getCurrentPlaylist();
    if (!currentPlaylist) return;

    map<string, int> counts;
    
    for (Song* song : currentPlaylist->getSongs()) {
        if (selectedCategory == FilterType::ARTIST) {
            counts[song->getArtist()]++;
        } else if (selectedCategory == FilterType::ALBUM) {
            counts[song->getAlbum()]++;
        }
    }

    for (auto const& [name, count] : counts) {
        filterItems.push_back({name, count});
    }
}

void FilterScreen::render() {
    UIRenderer::clearScreen();
    Playlist* currentPlaylist = app->getPlayer()->getCurrentPlaylist();
    string playlistName = (currentPlaylist != nullptr) ? currentPlaylist->getName() : "None";

    cout << COLOR_BLUE << "╔══════════════════════════════════════════════════════╗\n";

    if (state == FilterState::SELECT_CATEGORY) {
        string title = "Filter songs in: " + playlistName;
        cout << "║ " << COLOR_YELLOW << left << setw(52) << setfill(' ') << title << COLOR_BLUE << " ║\n";
        cout << "╠══════════════════════════════════════════════════════╣\n";
        cout << "║ " << COLOR_WHITE << left << setw(52) << setfill(' ') << "Filter by:" << COLOR_BLUE << " ║\n";
        cout << "║ " << COLOR_CYAN << "1. " << COLOR_WHITE << left << setw(49) << setfill(' ') << "Artist" << COLOR_BLUE << " ║\n";
        cout << "║ " << COLOR_CYAN << "2. " << COLOR_WHITE << left << setw(49) << setfill(' ') << "Album" << COLOR_BLUE << " ║\n";
    } 
    else if (state == FilterState::SELECT_ITEM) {
        string typeStr = (selectedCategory == FilterType::ARTIST) ? "Artists" : "Albums";
        string title = typeStr + " in " + playlistName;
        
        cout << "║ " << COLOR_YELLOW << left << setw(52) << setfill(' ') << title << COLOR_BLUE << " ║\n";
        cout << "╠══════════════════════════════════════════════════════╣\n";
        
        for (size_t i = 0; i < filterItems.size(); ++i) {
            string idx = to_string(i + 1) + ". ";
            string content = filterItems[i].first + " (" + to_string(filterItems[i].second) + " songs)";
            
            string fullLine = idx + content;
            if (fullLine.length() > 52) fullLine = fullLine.substr(0, 49) + "...";
            
            cout << "║ " << COLOR_CYAN << left << setw(idx.length()) << idx 
                 << COLOR_WHITE << left << setw(52 - idx.length()) << setfill(' ') << content << COLOR_BLUE << " ║\n";
        }
    }

    cout << "╠══════════════════════════════════════════════════════╣\n";
    cout << "║ " << COLOR_RED << "0. " << COLOR_WHITE << left << setw(49) << setfill(' ') << "Back" << COLOR_BLUE << " ║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n" << COLOR_RESET;
    
    cout << COLOR_CYAN << "Choice: " << COLOR_RESET;
}

void FilterScreen::handleInput() {
    string input = InputHandler::readLine();

    if (state == FilterState::SELECT_CATEGORY) {
        if (input == "0") {
            app->changeScreen(new BrowseScreen(app));
        } else if (input == "1") {
            selectedCategory = FilterType::ARTIST;
            loadItems();
            state = FilterState::SELECT_ITEM;
        } else if (input == "2") {
            selectedCategory = FilterType::ALBUM;
            loadItems();
            state = FilterState::SELECT_ITEM;
        }
    } 
    else if (state == FilterState::SELECT_ITEM) {
        if (input == "0") {
            state = FilterState::SELECT_CATEGORY;
            selectedCategory = FilterType::NONE;
            filterItems.clear();
        } else {
            try {
                int choice = stoi(input);
                if (choice > 0 && choice <= static_cast<int>(filterItems.size())) {
                    string selectedValue = filterItems[choice - 1].first;
                    
                    app->changeScreen(new BrowseScreen(app, selectedCategory, selectedValue));
                }
            } catch (const exception& e) {
                //Pass
            }
        }
    }
}