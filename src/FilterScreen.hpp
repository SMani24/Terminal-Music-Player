/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#pragma once
#include "Screen.hpp"
#include "BrowseScreen.hpp"
#include <string>
#include <vector>

enum class FilterState {
    SELECT_CATEGORY,
    SELECT_ITEM
};

class FilterScreen : public Screen {
private:
    FilterState state;
    FilterType selectedCategory;
    
    std::vector<std::pair<std::string, int>> filterItems;
    
    void loadItems();

public:
    FilterScreen(Application* appPtr);
    
    void render() override;
    void handleInput() override;
};