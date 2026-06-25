/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */

#define MINIAUDIO_IMPLEMENTATION
#include "Player.hpp"
#include <iostream>

using namespace std;

Player::Player() {
    state = PlayerState::STOPPED;
    mode = PlaybackMode::NO_REPEAT;
    currentPlaylist = nullptr;
    currentIndex = -1;
    isSoundLoaded = false;

    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        cerr << "Failed to initialize miniaudio engine!\n";
    }
}

Player::~Player() {
    if (isSoundLoaded) {
        ma_sound_uninit(&sound);
    }
    ma_engine_uninit(&engine);
}

void Player::setPlaylist(Playlist* playlist) {
    currentPlaylist = playlist;
    stop();
}

void Player::setMode(PlaybackMode newMode) {
    mode = newMode;
}

void Player::play(int index) {
    if (currentPlaylist == nullptr || currentPlaylist->getSongs().empty()) return;

    if (index >= 0 && index < static_cast<int>(currentPlaylist->getSongs().size())) {
        currentIndex = index;
    } else if (currentIndex == -1) {
        currentIndex = 0;
    }

    Song* songToPlay = getCurrentSong();
    if (!songToPlay) return;

    if (isSoundLoaded) {
        ma_sound_uninit(&sound);
        isSoundLoaded = false;
    }

    string fullPath = "Data/" + songToPlay->getFilePath();
    
    if (ma_sound_init_from_file(&engine, fullPath.c_str(), 0, NULL, NULL, &sound) != MA_SUCCESS) {
        cerr << "Warning: Failed to load audio file: " << fullPath << "\n";
        return; 
    }

    isSoundLoaded = true;
    ma_sound_start(&sound);
    state = PlayerState::PLAYING;
    
    songToPlay->incrementPlayCount();
}

void Player::pause() {
    if (state == PlayerState::PLAYING && isSoundLoaded) {
        ma_sound_stop(&sound);
        state = PlayerState::PAUSED;
        cout << "Paused. \n";
    }
}

void Player::resume() {
    if (state == PlayerState::PAUSED && isSoundLoaded) {
        ma_sound_start(&sound);
        state = PlayerState::PLAYING;
        cout << "Resumed.\n";
    }
}

void Player::stop() {
    if (isSoundLoaded) {
        ma_sound_stop(&sound);
        ma_sound_seek_to_pcm_frame(&sound, 0);
    }
    state = PlayerState::STOPPED;
    currentIndex = -1;
    cout << "Stopped.\n";
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

void Player::tick() {
    if (state == PlayerState::PLAYING && isSoundLoaded && ma_sound_at_end(&sound)) {
        next();
    }
}

Song* Player::getCurrentSong() const {
    if (currentPlaylist != nullptr && currentIndex >= 0 && currentIndex < static_cast<int> (currentPlaylist->getSongs().size())) {
        return currentPlaylist->getSongs()[currentIndex];
    }
    return nullptr;
}

PlayerState Player::getState() const { return state; }
PlaybackMode Player::getMode() const { return mode; }
Playlist* Player::getCurrentPlaylist() const { return currentPlaylist; }

int Player::getCurrentTimeSec() {
    if (!isSoundLoaded || state == PlayerState::STOPPED) {
        return 0;
    }

    ma_uint64 cursorInFrames = 0;
    ma_sound_get_cursor_in_pcm_frames(&sound, &cursorInFrames);
    
    ma_uint32 sampleRate = ma_engine_get_sample_rate(&engine);
    
    if (sampleRate > 0) {
        return static_cast<int>(cursorInFrames / sampleRate);
    }
    
    return 0;
}

void Player::seekBy(int seconds) {
    if (!isSoundLoaded) return; 

    ma_uint64 cursor, length;
    ma_sound_get_cursor_in_pcm_frames(&sound, &cursor);
    ma_sound_get_length_in_pcm_frames(&sound, &length);
    
    ma_uint32 rate = ma_engine_get_sample_rate(&engine);
    
    ma_int64 newFrame = (ma_int64)cursor + (ma_int64)seconds * rate;
    
    if (newFrame < 0) newFrame = 0;
    
    if ((ma_uint64)newFrame >= length) { 
        next(); 
        return; 
    }
    
    ma_sound_seek_to_pcm_frame(&sound, (ma_uint64)newFrame);
}