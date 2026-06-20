/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */

#include "CsvLoader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void CsvLoader::load(const string& filePath, MusicLibrary& library) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Could not open " << filePath << '\n';
        return;
    }

    string line;    

    while (getline(file, line)) {
        if (line.empty()) 
            continue;

        stringstream ss(line);
        string title, artist, album, genre, yearStr, durationStr, songFilePath;

        getline(ss, title, ',');
        getline(ss, artist, ',');
        getline(ss, album, ',');
        getline(ss, genre, ',');
        getline(ss, yearStr, ',');
        getline(ss, durationStr, ',');
        getline(ss, songFilePath, ',');

        if (title.empty() || songFilePath.empty()) {
            cerr << "Invalid row in CSV. \n";
            continue;
        }

        try {
            int year = stoi(yearStr);
            int durationSec = stoi(durationStr);
            
            Song* newSong = new Song(title, artist, album, genre, year, durationSec, songFilePath);
            library.addSong(newSong);
            
        } catch (const exception& e) {
            cerr << "Data format error in CSV row. \n";
        }
    }
    
    file.close();
}