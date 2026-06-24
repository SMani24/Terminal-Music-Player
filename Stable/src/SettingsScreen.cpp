/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#include "SettingsScreen.hpp"
#include "MainMenuScreen.hpp"
#include "Application.hpp"
#include "UIRenderer.hpp"
#include "InputHandler.hpp"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void SettingsScreen::render() {
    UIRenderer::clearScreen();
    
    cout << COLOR_BLUE << "╔══════════════════════════════════════════════════════╗\n";
    cout << "║ " << COLOR_YELLOW << left << setw(52) << setfill(' ') << "Settings - Playback Mode" << COLOR_BLUE << " ║\n";
    cout << "╠══════════════════════════════════════════════════════╣\n";

    Player* player = app->getPlayer();
    string currentModeStr;
    switch (player->getMode()) {
        case PlaybackMode::NO_REPEAT: currentModeStr = "NO_REPEAT"; break;
        case PlaybackMode::REPEAT_ONE: currentModeStr = "REPEAT_ONE"; break;
        case PlaybackMode::REPEAT_ALL: currentModeStr = "REPEAT_ALL"; break;
        case PlaybackMode::SHUFFLE: currentModeStr = "SHUFFLE"; break;
    }

    string modeDisplay = "Current Mode: " + currentModeStr;
    cout << "║ " << COLOR_GREEN << left << setw(52) << setfill(' ') << modeDisplay << COLOR_BLUE << " ║\n";
    cout << "╠══════════════════════════════════════════════════════╣\n";
    
    cout << "║ " << COLOR_CYAN << "1. " << COLOR_WHITE << left << setw(49) << setfill(' ') << "Normal (No Repeat)" << COLOR_BLUE << " ║\n";
    cout << "║ " << COLOR_CYAN << "2. " << COLOR_WHITE << left << setw(49) << setfill(' ') << "Repeat One" << COLOR_BLUE << " ║\n";
    cout << "║ " << COLOR_CYAN << "3. " << COLOR_WHITE << left << setw(49) << setfill(' ') << "Repeat All" << COLOR_BLUE << " ║\n";
    cout << "║ " << COLOR_CYAN << "4. " << COLOR_WHITE << left << setw(49) << setfill(' ') << "Shuffle" << COLOR_BLUE << " ║\n";
    cout << "╠══════════════════════════════════════════════════════╣\n";
    
    cout << "║ " << COLOR_WHITE << left << setw(52) << setfill(' ') << "Enter number to change mode. [0] back" << COLOR_BLUE << " ║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n" << COLOR_RESET;
    
    cout << COLOR_CYAN << "Choice: " << COLOR_RESET;
}

void SettingsScreen::handleInput() {
    int choice = InputHandler::readInt(0, 4);

    if (choice == 0) {
        app->changeScreen(new MainMenuScreen(app));
        return;
    }

    Player* player = app->getPlayer();
    ConfigManager* config = app->getConfig();
    string modeString = "";

    switch (choice) {
        case 1:
            player->setMode(PlaybackMode::NO_REPEAT);
            modeString = "NO_REPEAT";
            break;
        case 2:
            player->setMode(PlaybackMode::REPEAT_ONE);
            modeString = "REPEAT_ONE";
            break;
        case 3:
            player->setMode(PlaybackMode::REPEAT_ALL);
            modeString = "REPEAT_ALL";
            break;
        case 4:
            player->setMode(PlaybackMode::SHUFFLE);
            modeString = "SHUFFLE";
            break;
    }

    config->set("playback_mode", modeString);
}