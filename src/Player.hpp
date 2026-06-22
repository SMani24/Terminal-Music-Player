/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */

#pragma once
#include "Playlist.hpp"
#include <vector>
#include <cstdlib>

enum class PlayerState {
    STOPPED,
    PLAYING,
    PAUSED
};

enum class PlaybackMode {
    NO_REPEAT,
    REPEAT_ONE,
    REPEAT_ALL,
    SHUFFLE
};

class Player {
private:
    PlayerState state;
    PlaybackMode mode;
    Playlist* currentPlaylist;
    int currentIndex;

    void advanceIndex(); 

public:
    Player();
    
    void setPlaylist(Playlist* playlist);
    void setMode(PlaybackMode newMode);
    
    void play(int index = -1);
    void pause();
    void resume();
    void stop();
    void next();
    void prev();
    
    Song* getCurrentSong() const;
    PlayerState getState() const;
    PlaybackMode getMode() const;
};