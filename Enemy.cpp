//
//  Enemy.cpp
//  Viruses
//
//  Created by Александер on 19.04.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#include "Enemy.hpp"

void Enemy::moveAndSlide(float dt) {
    dir = targetC - Vector2f{(float)x, (float)y};
    distance = sqrt(dir.x * dir.x + dir.y * dir.y);
    distanceFar = distance;
    
    dir /= distance;
    
    if (distance > 700) {
        distance = 700;
    }
    
    if (distanceFar > 6000) {
    }
    
    if (distance < 700) {
        if (coundDamage->getElapsedTime().asSeconds() >= 0.2) {
            player->health -= 6;
            coundDamage->restart();
        }
    }
    else {
        player->isDamage = false;
        coundDamage->restart();
    }
    
    if (700 - distance != 0) {
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
    
    x += velocity.x * dt * 30;
    y += velocity.y * dt * 30;
}

void Enemy::updateVitamins() {
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
                    i->x += i->x * rand();
                    i->y += i->y * rand();
                }
                sprite.setColor(Color::Green);
            }
            else if (type == VType::VSpeed) {
                sprite.setColor(Color::Yellow);
                maxSpeed += 20;
                i->x += i->x * ((float)rand() / (float)RAND_MAX);
                i->y += i->y * ((float)rand() / (float)RAND_MAX);
            }
            else if (type == VType::VEvolution) {
                sprite.setColor(Color::Blue);
                vitamins->erase(vitamins->begin() + n);
            }
        }
        
        i->update();
        i->draw(*window);
        n++;
    }
}
