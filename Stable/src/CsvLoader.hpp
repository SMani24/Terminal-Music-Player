/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#pragma once
#include "MusicLibrary.hpp"
#include <string>

class CsvLoader {
public:
    static void load(const std::string& filePath, MusicLibrary& library);
};