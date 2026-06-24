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

enum class SortCriteria { TITLE, ARTIST, ALBUM, YEAR, DURATION };
enum class FilterType { NONE, ARTIST, ALBUM };

class BrowseScreen : public Screen {
private:
    std::vector<Song*> displayedSongs;
    
    bool showSortMenu;
    SortCriteria currentSort;
    bool sortAscending;

    bool isSearchMode;
    std::string searchQuery;

    FilterType currentFilterType;
    std::string currentFilterValue;

    void updateDisplay();
    void applyFilters();
    void applySort();
    
    void drawHeader();
    void drawSongTable();
    void drawFooter();
    
    void playSelectedSong(int choice);

public:
    BrowseScreen(Application* appPtr, FilterType fType = FilterType::NONE, std::string fValue = "");
    
    void render() override;
    void handleInput() override;
};