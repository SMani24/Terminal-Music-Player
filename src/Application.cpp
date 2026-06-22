/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#include "Application.hpp"
#include "CsvLoader.hpp"
#include "MainMenuScreen.hpp"
#include <iostream>

using namespace std;

Application::Application() : config("Data/settings.cfg"), activeScreen(nullptr), running(true) {}

Application::~Application() {
    if (activeScreen != nullptr) {
        delete activeScreen;
    }
}

void Application::init() {
    config.load();

    CsvLoader::load("./Data/library.csv", library);
    
    activeScreen = new MainMenuScreen(this);
}

void Application::run() {
    while (running) {
        if (activeScreen) {
            activeScreen->render();
            activeScreen->handleInput();
        }
        
        player.tick();
    }
}

void Application::shutdown() {
    config.save();
    running = false;
}

void Application::changeScreen(Screen* newScreen) {
    if (activeScreen != nullptr) {
        delete activeScreen;
    }
    activeScreen = newScreen;
}