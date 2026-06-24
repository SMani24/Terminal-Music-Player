/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#include "ConfigManager.hpp"
#include <fstream>
#include <iostream>

using namespace std;

ConfigManager::ConfigManager(const string& path) {
    configFilePath = path;
}

void ConfigManager::load() {
    ifstream file(configFilePath);
    if (!file.is_open()) return; 

    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        size_t delimiterPos = line.find('=');
        if (delimiterPos != string::npos) {
            string key = line.substr(0, delimiterPos);
            string value = line.substr(delimiterPos + 1);
            settings[key] = value;
        }
    }
    file.close();
}

void ConfigManager::save() const {
    ofstream file(configFilePath);
    if (!file.is_open()) {
        cerr << "Error: Could not save settings to " << configFilePath << "\n";
        return;
    }

    for (auto const& [key, value] : settings) {
        file << key << "=" << value << "\n";
    }
    file.close();
}

string ConfigManager::get(const string& key, const string& defaultValue) const {
    auto it = settings.find(key);
    if (it != settings.end()) {
        return it->second;
    }
    return defaultValue;
}

void ConfigManager::set(const string& key, const string& value) {
    settings[key] = value;
}