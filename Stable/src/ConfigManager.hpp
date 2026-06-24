/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#pragma once
#include <string>
#include <map>

class ConfigManager {
private:
    std::map<std::string, std::string> settings;
    std::string configFilePath;

public:
    ConfigManager(const std::string& path);
    
    void load();
    void save() const;
    
    std::string get(const std::string& key, const std::string& defaultValue = "") const;
    void set(const std::string& key, const std::string& value);
};