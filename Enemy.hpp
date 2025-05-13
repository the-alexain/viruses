//
//  Enemy.hpp
//  Viruses
//
//  Created by Александер on 19.04.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "GameObject.hpp"
#include "Vitamin.hpp"
#include "Player.hpp"

using namespace sf;
using namespace std;

class Enemy : public GameObject {
    
public:
    
    float maxSpeed = 30;
    float k = 1;
    Vector2f targetC;
    Vector2f velocity;
    float distance = 0;
    float distanceFar = 0;
    float lastDistance = 0;
    Vector2f dir;
    Player *player;
    Clock *coundDamage;
    vector<Vitamin*>* vitamins = NULL;
    RenderWindow* window = NULL;

    Enemy() : GameObject(0, 0, 0, "/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/virus.png") {}
    
    Enemy(int x, int y, Player *pl, Clock *cd, vector<Vitamin*>* v, RenderWindow* w) : GameObject(x, y, 0, "/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/virus.png") {
        this->speed = 0.08;
        health = 100;
        maxHealth = 100;
        pickupRadius = 100;
        player = pl;
        coundDamage = cd;
        window = w;
        vitamins = v;
    }
    
    void moveAndSlide(float dt);
    void updateVitamins();
    
};

#endif /* Enemy_hpp */
