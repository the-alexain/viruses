//
//  Vitamin.cpp
//  Viruses
//
//  Created by Александер on 28.02.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#include "Vitamin.hpp"
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

using namespace sf;

void Vitamin::update(float dt) {
    GameObject::update();
    
    time += dt;
        
    // 1. Пульсация размера (синусоида)
    float pulse = std::sin(time * pulseSpeed) * 0.1f;
    sprite.setScale(1 + pulse, 1 + pulse);
    
    // 2. Случайное дрожание (перлин-шум или синус)
    float angle = std::sin(time * 4.5f) * shakePower;
    GameObject::setRotate(angle);
//    move(offsetX * dt, offsetY * dt);
}


