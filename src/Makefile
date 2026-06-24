# Compiler and compilation flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g -pthread -lm

# Target executable name
TARGET = music_player_test

# Source files
SRCS = main.cpp \
       Song.cpp \
       MusicLibrary.cpp \
       CsvLoader.cpp \
       Playlist.cpp \
       M3uLoader.cpp \
       Player.cpp \
       ConfigManager.cpp \
       InputHandler.cpp \
       UIRenderer.cpp \
       MainMenuScreen.cpp \
       NowPlayingScreen.cpp \
       PlaylistsScreen.cpp \
       SettingsScreen.cpp \
       BrowseScreen.cpp \
       FilterScreen.cpp \
       Application.cpp

# Object files (automatically swaps .cpp extension for .o)
OBJS = $(SRCS:.cpp=.o)

# Default target when you just run 'make'
all: $(TARGET)

# Rule to link object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile individual .cpp files into .o object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets to prevent conflicts with files named 'all' or 'clean'
.PHONY: all clean