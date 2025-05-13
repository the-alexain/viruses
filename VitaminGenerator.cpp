//
//  VitaminGenerator.cpp
//  Viruses
//
//  Created by Александер on 28.02.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#include "VitaminGenerator.hpp"
#include "Vitamin.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


using namespace sf;
using namespace std;


void VitaminGenerator::generator() {
    if (vitamins_ref->size() < LIMIT) {
        while (LIMIT - vitamins_ref->size() != 0) {
            generate();
        }
    }
}

void VitaminGenerator::generate() {
    z = generator_ref->generateBetweenZero();
    pos = generator_ref->generatePositionPolar();
    
    if (z < 0.1) {
        vitamins_ref->push_back(new VitaminEvolution(pos.x, pos.y, 0, 15));
    }
    else if (z > 0.1 && z < 0.5) {
        vitamins_ref->push_back(new VitaminSpeed(pos.x, pos.y, 0, 30));
    }
    else {
        vitamins_ref->push_back(new VitaminFood(pos.x, pos.y, 0, 30));
    }
}
