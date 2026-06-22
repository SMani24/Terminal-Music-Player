/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */

#include "Player.hpp"
#include <iostream>

using namespace std;

Player::Player() {
    state = PlayerState::STOPPED;
    mode = PlaybackMode::NO_REPEAT;
    currentPlaylist = nullptr;
    currentIndex = -1;
}

void Player::setPlaylist(Playlist* playlist) {
    currentPlaylist = playlist;
    stop();
}

void Player::setMode(PlaybackMode newMode) {
    mode = newMode;
}

void Player::play(int index) {
    if (currentPlaylist == nullptr || currentPlaylist->getSongs().empty()) {
        cerr << "Error: Playlist is empty or not set.\n";
        return;
    }

    if (index >= 0 && index < currentPlaylist->getSongs().size()) {
        currentIndex = index;
    } else if (currentIndex == -1) {
        currentIndex = 0;
    }

    state = PlayerState::PLAYING;
    
    cout << "PLAYING: " << getCurrentSong()->getTitle() << "\n";
}

void Player::pause() {
    if (state == PlayerState::PLAYING) {
        state = PlayerState::PAUSED;
        cout << "PAUSED\n";
    }
}

void Player::resume() {
    if (state == PlayerState::PAUSED) {
        state = PlayerState::PLAYING;
        cout << "RESUMED\n";
    }
}

void Player::stop() {
    state = PlayerState::STOPPED;
    currentIndex = -1;
    cout << "STOPPED\n";
}

void Player::advanceIndex() {
    int totalSongs = currentPlaylist->getSongs().size();
    
    if (mode == PlaybackMode::SHUFFLE) {
        currentIndex = rand() % totalSongs;
    } else if (mode == PlaybackMode::REPEAT_ONE) {
        //pass
    } else if (mode == PlaybackMode::REPEAT_ALL) {
        currentIndex = (currentIndex + 1) % totalSongs;
    } else { // NO_REPEAT
        if (currentIndex < totalSongs - 1) {
            currentIndex++;
        } else {
            stop();
        }
    }
}

void Player::next() {
    if (currentPlaylist == nullptr || currentPlaylist->getSongs().empty()) return;
    
    advanceIndex();
    
    if (state != PlayerState::STOPPED) {
        play(currentIndex);
    }
}

void Player::prev() {
    if (currentPlaylist == nullptr || currentPlaylist->getSongs().empty()) return;

    if (mode == PlaybackMode::SHUFFLE) {
        currentIndex = rand() % currentPlaylist->getSongs().size();
    } else {
        currentIndex--;
        if (currentIndex < 0) {
            currentIndex = currentPlaylist->getSongs().size() - 1; 
        }
    }

    if (state != PlayerState::STOPPED) {
        play(currentIndex);
    }
}

Song* Player::getCurrentSong() const {
    if (currentPlaylist != nullptr && currentIndex >= 0 && currentIndex < currentPlaylist->getSongs().size()) {
        return currentPlaylist->getSongs()[currentIndex];
    }
    return nullptr;
}

PlayerState Player::getState() const { return state; }
PlaybackMode Player::getMode() const { return mode; }