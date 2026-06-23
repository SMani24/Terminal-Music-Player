/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#pragma once
#include <string>

const std::string COLOR_RESET   = "\033[0m";
const std::string COLOR_RED     = "\033[31m";
const std::string COLOR_GREEN   = "\033[32m";
const std::string COLOR_YELLOW  = "\033[33m";
const std::string COLOR_BLUE    = "\033[34m";
const std::string COLOR_MAGENTA = "\033[35m";
const std::string COLOR_CYAN    = "\033[36m";
const std::string COLOR_WHITE   = "\033[37m";
class UIRenderer {
public:
    static void clearScreen();
    static void printHeader(const std::string& title);
};