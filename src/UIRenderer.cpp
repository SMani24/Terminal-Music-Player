/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#include "UIRenderer.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

void UIRenderer::clearScreen() {
    system("clear"); 
}

void UIRenderer::printHeader(const string& title) {
    clearScreen();
    cout << "========================================\n";
    cout << "  " << title << "\n";
    cout << "========================================\n\n";
}