/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#pragma once
#include "Screen.hpp"

class PlaylistsScreen : public Screen {
public:
    PlaylistsScreen(Application* appPtr) : Screen(appPtr) {}
    
    void render() override;
    void handleInput() override;
};