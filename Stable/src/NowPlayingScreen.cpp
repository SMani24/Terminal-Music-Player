/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#include "NowPlayingScreen.hpp"
#include "MainMenuScreen.hpp"
#include "InputHandler.hpp"
#include "Application.hpp"
#include "UIRenderer.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

void NowPlayingScreen::render() {
    UIRenderer::clearScreen();
    
    cout << COLOR_BLUE << "╔══════════════════════════════════════════════════════╗\n";
    
    cout << "║ " << COLOR_YELLOW << left << setw(52) << setfill(' ') << "Now Playing" << COLOR_BLUE << " ║\n";
    cout << "╠══════════════════════════════════════════════════════╣\n";

    Player* player = app->getPlayer();
    Song* currentSong = player->getCurrentSong();

    if (currentSong == nullptr) {
        cout << "║ " << COLOR_RED << left << setw(52) << setfill(' ') << "No song is currently playing or selected." << COLOR_BLUE << " ║\n";
    } else {
        
        auto drawPaddedLine = [](const string& label, const string& value, const string& valueColor) {
            string rawText = label + value;
            int visualLength = rawText.length();
            
            if (label == "► ") {
                visualLength -= 2; 
            }
            
            int spacesNeeded = 52 - visualLength;
            if (spacesNeeded < 0) {
                spacesNeeded = 0;
            }
            
            string padding(spacesNeeded, ' ');
            cout << "║ " << COLOR_CYAN << label << valueColor << value << padding << COLOR_BLUE << " ║\n";
        };

        drawPaddedLine("Title:  ", currentSong->getTitle(), COLOR_WHITE);
        drawPaddedLine("Artist: ", currentSong->getArtist(), COLOR_WHITE);
        drawPaddedLine("Album:  ", currentSong->getAlbum(), COLOR_WHITE);
        drawPaddedLine("Genre:  ", currentSong->getGenre(), COLOR_WHITE);
        drawPaddedLine("Year:   ", "[" + to_string(currentSong->getYear()) + "]", COLOR_WHITE);
        
        cout << COLOR_BLUE << "║ " << setw(52) << setfill(' ') << "" << " ║\n";

        string stateStr, stateColor;
        switch (player->getState()) {
            case PlayerState::PLAYING: stateStr = "PLAYING"; stateColor = COLOR_GREEN; break;
            case PlayerState::PAUSED:  stateStr = "PAUSED"; stateColor = COLOR_YELLOW; break;
            case PlayerState::STOPPED: stateStr = "STOPPED"; stateColor = COLOR_RED; break;
        }
        drawPaddedLine("► ", stateStr, stateColor);

        string modeStr;
        switch (player->getMode()) {
            case PlaybackMode::NO_REPEAT: modeStr = "NO_REPEAT"; break;
            case PlaybackMode::REPEAT_ONE: modeStr = "REPEAT_ONE"; break;
            case PlaybackMode::REPEAT_ALL: modeStr = "REPEAT_ALL"; break;
            case PlaybackMode::SHUFFLE: modeStr = "SHUFFLE"; break;
        }
        drawPaddedLine("Mode: ", modeStr, COLOR_WHITE);

        string playlistName = "Unknown";
        if (player->getCurrentPlaylist() != nullptr) {
            playlistName = player->getCurrentPlaylist()->getName();
        }
        drawPaddedLine("Playlist: ", playlistName, COLOR_WHITE);

        int duration = currentSong->getDurationSec();
        int mins = duration / 60;
        int secs = duration % 60;
        
        stringstream ss;
        ss << setfill('0') << setw(2) << mins << ":" << setfill('0') << setw(2) << secs;
        drawPaddedLine("Duration: ", ss.str(), COLOR_WHITE);
    }

    cout << COLOR_BLUE << "╠══════════════════════════════════════════════════════╣\n";
    
    cout << "║ " << COLOR_WHITE << left << setw(52) << setfill(' ') << "[p] pause/play  [n] next  [b] prev  [s] stop" << COLOR_BLUE << " ║\n";
    cout << "║ " << COLOR_WHITE << left << setw(52) << setfill(' ') << "[0] menu" << COLOR_BLUE << " ║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n" << COLOR_RESET;
    
    cout << COLOR_CYAN << "Choice: " << COLOR_RESET;
}

void NowPlayingScreen::handleInput() {
    string input = InputHandler::readLine();
    Player* player = app->getPlayer();

    if (input == "0") {
        app->changeScreen(new MainMenuScreen(app));
    } else if (input == "p") {
        if (player->getState() == PlayerState::PLAYING) {
            player->pause();
        } else {
            player->resume();
            if (player->getState() == PlayerState::STOPPED) {
                player->play(); 
            }
        }
    } else if (input == "n") {
        player->next();
    } else if (input == "b") {
        player->prev();
    } else if (input == "s") {
        player->stop();
    } else {
        //Pass
    }
}