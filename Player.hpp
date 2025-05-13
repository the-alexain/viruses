//
//  Player.hpp
//  Viruses
//
//  Created by Александер on 28.02.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "GameObject.hpp"
#include "Vitamin.hpp"
#include "Generator.hpp"

using namespace sf;
using namespace std;

class Player : public GameObject {
    
public:

    float maxSpeed;
    const float _maxSpeed = 20;
    float k = 1;
    float distance = 0;
    float lastDistance = 0;
    Vector2f dir;
    Vector2f targetC;
    Vector2f velocity;
    Generator* gen;
    
    int degratation = 0;
    
    float targetVelX = 0.f; float targetVelY = 0.f;
    
    bool effected = false;
    bool isDamage = false;
    
    Player() : GameObject(0, 0, 0, "/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/pd.png") {}
    
    Player(int x, int y, Generator *g) : GameObject(x, y, 0, "/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/pd.png") {
        this->health = 100;
        this->maxHealth = 100;
        this->pickupRadius = 100;
        this->maxSpeed = _maxSpeed;
        this->gen = g;
        props.insert(props.begin(), &dir.x);
        props.insert(props.begin() + 1, &dir.y);
        props.insert(props.begin() + 2, &targetC.x);
        props.insert(props.begin() + 3, &targetC.y);
        props.insert(props.begin() + 4, &distance);
    }
    void moveAndSlide(float dt);
    void updateVitamins(vector<Vitamin*>* vitamins, RenderWindow& window, Clock* countdown, float *dt);
    
};

#endif /* Player_hpp */
