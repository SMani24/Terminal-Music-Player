/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#pragma once
#include <string>

class InputHandler {
public:
    static int readInt(int min, int max);
    
    static std::string readLine();
    static void pauseForUser();
};