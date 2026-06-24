/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#pragma once
#include "Screen.hpp"
#include "Song.hpp"
#include <vector>
#include <string>

enum class SortCriteria {
    TITLE,
    ARTIST,
    ALBUM,
    YEAR,
    DURATION
};

class BrowseScreen : public Screen {
private:
    std::vector<Song*> displayedSongs;
    
    bool showSortMenu;
    SortCriteria currentSort;
    bool sortAscending;

    bool isSearchMode;
    std::string searchQuery;

    void updateDisplay();

public:
    BrowseScreen(Application* appPtr);
    
    void render() override;
    void handleInput() override;
};