//
//  GameObject.cpp
//  Viruses
//
//  Created by Александер on 28.02.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

void GameObject::setTexture(string path) {
    texture.loadFromFile(path);
    this->updateTexture();
}

void GameObject::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
    sprite.setPosition(x, y);
}


void GameObject::updateTexture() {
    this->sprite.setTexture(texture, true);
    this->w = sprite.getLocalBounds().getSize().x;
    this->h = sprite.getLocalBounds().getSize().y;
    
    sprite.setOrigin(w / 2, h /2);
}

void GameObject::update(float dt) {
    this->setPosition(x, y);
    this->texture.setSmooth(true);
    this->centerDebug.setPosition(x, y);
}

void GameObject::setRotate(int angle) {
    if (rotation != angle) {
        int newAngle = rotation - angle;
        sprite.rotate(newAngle);
//        DebugCollision.rotate(newAngle);
        rotation = angle;
    }
}

void GameObject::remove() {
}


bool GameObject::isClose(const float x1, const float y1, const float x2, const float y2, float radius) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    
    return (dx * dx + dy * dy) <= (radius * radius);
}

float GameObject::clamp(float n, float lower, float upper)  {
    return std::max(lower, std::min(n, upper));
}
