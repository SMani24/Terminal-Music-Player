/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#pragma once

class Application; 

class Screen {
protected:
    Application* app;

public:
    Screen(Application* appPtr) : app(appPtr) {}
    
    virtual ~Screen() = default; 

    virtual void render() = 0;
    virtual void handleInput() = 0;
};