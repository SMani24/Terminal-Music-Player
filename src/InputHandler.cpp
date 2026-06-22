/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: camelCase
 * Constant names: UPPER_SNAKE_CASE
 */
#include "InputHandler.hpp"
#include <iostream>
#include <limits>

using namespace std;

int InputHandler::readInt(int min, int max) {
    int choice;
    while (true) {
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\nChoice: ";
        } else if (choice < min || choice > max) {
            cout << "Invalid choice. Please try again.\nChoice: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
    }
}

string InputHandler::readLine() {
    string input;
    getline(cin, input);
    return input;
}