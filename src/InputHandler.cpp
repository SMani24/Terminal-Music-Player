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
#include <termios.h>
#include <unistd.h>

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

void InputHandler::pauseForUser() {
    cout << "\nPress any key to return to the menu...";
    getRawChar(); 
}

char InputHandler::getRawChar() {
    cout.flush();
    char buf = 0;
    struct termios old = {};
    
    // 1. Get current terminal settings
    if (tcgetattr(STDIN_FILENO, &old) < 0) {
        perror("tcsetattr()");
    }
    
    // 2. Disable Canonical mode (Enter key requirement) and Echo (printing the key)
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    
    // 3. Apply new settings instantly
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old) < 0) {
        perror("tcsetattr ICANON");
    }
    
    // 4. Read the single raw byte
    if (read(STDIN_FILENO, &buf, 1) < 0) {
        perror("read()");
    }
    
    // 5. Restore normal terminal settings so the rest of the app works normally
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) < 0) {
        perror("tcsetattr ~ICANON");
    }
    
    return buf;
}

char InputHandler::getRawCharWithTimeout(int tenthsOfASecond) {
    cout.flush();
    char buf = '\0'; 
    struct termios old = {};
    
    if (tcgetattr(STDIN_FILENO, &old) < 0) {
        return '\0';
    }
    
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    
    old.c_cc[VMIN] = 0; 
    old.c_cc[VTIME] = tenthsOfASecond;
    
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    
    if (read(STDIN_FILENO, &buf, 1) > 0) {
        // If the byte is ESC (27), check for the rest of the arrow key sequence
        if (buf == '\033') { 
            char seq[2];
            
            // Shrink the timeout to grab the next two bytes instantly
            old.c_cc[VTIME] = 1; 
            tcsetattr(STDIN_FILENO, TCSANOW, &old);
            
            if (read(STDIN_FILENO, &seq[0], 1) > 0 && read(STDIN_FILENO, &seq[1], 1) > 0) {
                if (seq[0] == '[') {
                    if (seq[1] == 'C') { // Right Arrow
                        buf = 'R'; 
                    } else if (seq[1] == 'D') { // Left Arrow
                        buf = 'L'; 
                    }
                }
            }
        }
    }
    
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSADRAIN, &old);
    
    return buf;
}