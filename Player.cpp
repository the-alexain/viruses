//
//  Player.cpp
//  Viruses
//
//  Created by Александер on 28.02.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "GameObject.hpp"
#include "Vitamin.hpp"
#include "Logger.hpp"


using namespace sf;
using namespace std;

void Player::moveAndSlide(float dt) {
    
    dir = targetC - Vector2f{(float)x, (float)y};
    distance = sqrt(dir.x * dir.x + dir.y * dir.y);
    
    dir /= distance;
    
    if (distance > 400) {
        distance = 400;
    }
    
    if (400 - distance != 0) {
        k = -1;
    }
    else {
        k = 1;
    }
    
    speed += maxSpeed / distance * dt * 500 * k;
    speed = clamp(speed, 0, maxSpeed);
    
    velocity = dir * speed * 3.f;
    
    if (speed == 0) {
        velocity = Vector2f{0,0};
        targetC = Vector2f{(float)x, (float)y};
        dir = Vector2f{0, 0};
    }
    
    x += velocity.x * dt * 50;
    y += velocity.y * dt * 50;
    
//    x = clamp(x, -10000, 10000);
//    y = clamp(y, -10000, 10000);
    
}

void Player::updateVitamins(vector<Vitamin*> *vitamins, RenderWindow& window, Clock* countdown, float *dt) {
    
    if (effected) {
        if (countdown->getElapsedTime().asSeconds() > 2) {
            effected = false;
            maxSpeed = _maxSpeed;
            sprite.setColor(Color::White);
        }
    }
    
    for (size_t n = 0; n < vitamins->size();) {
        Vitamin *i = vitamins->operator[](n);
        float vx = i->x;
        float vy = i->y;
        
        float d = (x - vx)*(x - vx) + (y - vy)*(y - vy);
        if (d <= pickupRadius * pickupRadius) {
            
            VType type = i->type;
            if (type == VType::VFood) {
                if (health < maxHealth) {
                    health += i->value;
                }
                
                sprite.setColor(Color::Green);
            }
            else if (type == VType::VSpeed) {
                if (!effected) {
                    sprite.setColor(Color::Yellow);
                    cout << i->value << endl;;
                    maxSpeed += 20;
                    effected = true;
                    countdown->restart();
                }
            }
            else if (type == VType::VEvolution) {
                sprite.setColor(Color::Blue);
                degratation += 8;
                sprite.setScale(sprite.getScale().x + 0.1, sprite.getScale().y + 0.1);
                pickupRadius += 5;
            }
            i->x = gen->generatePositionPolar().x;
            i->y = gen->generatePositionPolar().y;
        }
        
        i->update(*dt);
        i->draw(window);
        n++;
    }
}

