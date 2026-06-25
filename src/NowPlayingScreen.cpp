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
        
        auto drawPaddedLine = [](const string& label, const string& value, const string& valueColor, bool isFav = false) {
            int visualLength = label.length() + value.length();
            if (isFav) visualLength += 2; // "♥ " takes 2 visual spaces
            
            if (label == "► ") {
                visualLength -= 2; 
            }
            if (value.find("⭐") != string::npos) {
                visualLength -= 1; 
            }
            if (value.find("♥") != string::npos && !isFav) {
                visualLength -= 2;
            }
            
            int spacesNeeded = 52 - visualLength;
            if (spacesNeeded < 0) spacesNeeded = 0;
            
            string padding(spacesNeeded, ' ');
            cout << "║ " << COLOR_CYAN << label;
            
            if (isFav) {
                cout << COLOR_RED << "♥ " << COLOR_WHITE;
            }
            
            cout << valueColor << value << padding << COLOR_BLUE << " ║\n";
        };

        drawPaddedLine("Title:  ", currentSong->getTitle(), COLOR_WHITE, currentSong->getIsFavorite());
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

        int totalDur = currentSong->getDurationSec();
        int tMins = totalDur / 60;
        int tSecs = totalDur % 60;
        
        int curTime = player->getCurrentTimeSec(); 
        int cMins = curTime / 60;
        int cSecs = curTime % 60;
        
        stringstream ss;
        ss << setfill('0') << setw(2) << cMins << ":" << setfill('0') << setw(2) << cSecs 
           << " / " 
           << setfill('0') << setw(2) << tMins << ":" << setfill('0') << setw(2) << tSecs;
           
        drawPaddedLine("Time: ", ss.str(), COLOR_WHITE);
    }

    cout << COLOR_BLUE << "╠══════════════════════════════════════════════════════╣\n";
    cout << "║ " << COLOR_WHITE << left << setw(52) << setfill(' ') << "[p] pause/play  [n] next  [b] prev  [s] stop" << COLOR_BLUE << " ║\n";
    cout << "║ " << COLOR_WHITE << left << setw(52) << setfill(' ') << "[<->] seek +/- 10s  [0] menu  [f] heart" << COLOR_BLUE << " ║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n" << COLOR_RESET;
    
    cout << COLOR_CYAN << "Choice: " << COLOR_RESET;
}

void NowPlayingScreen::handleInput() {
    char input = InputHandler::getRawCharWithTimeout(10);
    Player* player = app->getPlayer();

    if (input == '\0') {
        return; 
    }

    if (input == '0') {
        app->changeScreen(new MainMenuScreen(app));
    } else if (input == 'p') {
        if (player->getState() == PlayerState::PLAYING) {
            player->pause();
        } else {
            player->resume();
            if (player->getState() == PlayerState::STOPPED) {
                player->play(); 
            }
        }
    } else if (input == 'n') {
        player->next();
    } else if (input == 'b') {
        player->prev();
    } else if (input == 's') {
        player->stop();
    } else if (input == 'f') {
        if (player->getCurrentSong() != nullptr) {
            player->getCurrentSong()->toggleFavorite();
        }
    } else if (input == 'R') {
        player->seekBy(10);
    } else if (input == 'L') {
        player->seekBy(-10);
    } else {
        //Pass
    }
}