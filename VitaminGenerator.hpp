//
//  VitaminGenerator.hpp
//  Viruses
//
//  Created by Александер on 28.02.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#ifndef VitaminGenerator_hpp
#define VitaminGenerator_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Vitamin.hpp"
#include "Generator.hpp"

using namespace sf;
using namespace std;

class VitaminGenerator {
public:
    Player* player_ref;
    RenderWindow* window_ref;
    vector<Vitamin*>* vitamins_ref;
    Generator* generator_ref;
    const int LIMIT = 60;
    float z;
    Vector2f pos;
    
    VitaminGenerator(Player* player, RenderWindow* window, vector<Vitamin*>* vitamins, Generator *g) {
        player_ref = player;
        window_ref = window;
        vitamins_ref = vitamins;
        generator_ref = g;
    }
    
    void generate();
    void generator();
    
    inline void generatePosition();
};

#endif /* VitaminGenerator_hpp */
