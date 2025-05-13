//
//  ConsoleWriting.hpp
//  Viruses
//
//  Created by Александер on 13.04.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#ifndef ConsoleWriting_hpp
#define ConsoleWriting_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <regex>
#include "GameObject.hpp"
#include "Player.hpp"

using namespace sf;
using namespace std;

class Console {
    
public:
    bool *refDebug;
    bool *refGod;
    Player *refPlayer;
    Text *textMsg;
    
    bool msgAllow = false;
    
    Console(bool *DEBUG, Player *PLAYER, Text *MSG, bool *GOD) {
        refDebug = DEBUG;
        refPlayer = PLAYER;
        textMsg = MSG;
        refGod = GOD;
    }
    
    void run(string input);
    
    void msg(string message);
    void msg(float x, float y);
    void msg(float message);
    
    template<typename T>
    void msg(vector<T> elements) {
        if (msgAllow) {
            string msg;
            for (T i : elements) {
                msg += to_string(i) + " ";
            }
            
            textMsg->setString(msg);
        }
    };
    
    template<typename T>
    void msg(vector<T> elements, vector<string> keys) {
        string msg = "ERROR";
        if (msgAllow) {
            if (elements.size() == keys.size()) {
                msg = "";
                for (int i = 0; i < elements.size(); i++) {
                    msg += keys[i] + ": " + to_string(elements[i]) + " ";
                }
            }
            
            textMsg->setString(msg);
        }
    };
};


#endif /* ConsoleWriting_hpp */
