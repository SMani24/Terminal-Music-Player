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

class BrowseScreen : public Screen {
private:
    std::vector<Song*> displayedSongs;
    
public:
    BrowseScreen(Application* appPtr);
    
    void render() override;
    void handleInput() override;
};