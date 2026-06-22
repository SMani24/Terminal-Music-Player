/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#pragma once
#include <string>

class UIRenderer {
public:
    static void clearScreen();
    static void printHeader(const std::string& title);
};