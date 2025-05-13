//
//  ConsoleWriting.cpp
//  Viruses
//
//  Created by Александер on 13.04.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#include "ConsoleWriting.hpp"

using namespace sf;

void Console::msg(string message) {
    if (msgAllow) {
        textMsg->setString(message);
    }
}

void Console::msg(float message) {
    if (msgAllow) {
        textMsg->setString(to_string(message));
    }
}

void Console::msg(float x, float y) {
    if (msgAllow) {
        textMsg->setString(to_string(x) + "; " + to_string(y));
    }
}


void Console::run(string input) { // p.health 50
    static const std::regex cmd_regex(
                R"(^(\w+)\.(\w+)\s+([^\s].*?)\s*$)",
                std::regex_constants::optimize
            );

    std::smatch matches;
    

    if (regex_match(input, matches, cmd_regex)) {
        const std::string& obj = matches[1];
        const std::string& prop = matches[2];
        const std::string& value = matches[3];
        if (obj == "player" || obj == "p") {
            if (prop == "health") {
                int h = 0;
                if (value == "max") {
                    h = refPlayer->maxHealth;
                }
                else {
                    h = stoi(value);
                }
                refPlayer->health = h;
                cout << "PLAYER: Changed HP to " + value << endl;
            }
            
            else if (prop == "pos") {
                if (value == "0") {
                    refPlayer->x = 0;
                    refPlayer->y = 0;
                }
            }
            
            else if (prop == "deg") {
                if (stoi(value) && stoi(value) >= 0) {
                    refPlayer->degratation = stoi(value);
                }
            }
            
            else if (prop == "god") {
                *refGod = value == "1";
            }
        }
        
        else if (obj == "console" || obj == "c" ) {
            if (prop == "msg") {
                msgAllow = value == "1";
            }
        }
    }
}
