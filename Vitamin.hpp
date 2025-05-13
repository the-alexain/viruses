//
//  Vitamin.hpp
//  Viruses
//
//  Created by Александер on 28.02.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#ifndef Vitamin_hpp
#define Vitamin_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

using namespace sf;

enum VType {
    VFood, VSpeed, VEvolution, VEmpty
};

class Vitamin : public GameObject {
public:
    VType type = VType::VEmpty;
    int value;
    float shakePower = 10.5f;     // Сила тряски (в пикселях)
    float pulseSpeed = 10.f;
    float time = 0.f;
    
    Vitamin(int x, int y, int rotation) : GameObject(x, y, rotation) {
        this->health = -1;
        this->speed = 0;
    }
    
    void update(float dt = 0.f) override;
    
    void draw(RenderWindow& window) {
        window.draw(sprite);
    }
    
    ~Vitamin() {};
};

class VitaminFood : public Vitamin {
public:
    
    VitaminFood(int x, int y, int rotation, int value) : Vitamin(x, y, rotation) {
        type = VType::VFood;
        this->value = value;
        this->setTexture("/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/vf.png");
    }
};

class VitaminEvolution : public Vitamin {
public:
    
    VitaminEvolution(int x, int y, int rotation, int value) : Vitamin(x, y, rotation) {
        this->value = value;
        type = VType::VEvolution;
        this->setTexture("/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/ve.png");
    }
};

class VitaminSpeed : public Vitamin {
public:
    int value;
    
    VitaminSpeed(int x, int y, int rotation, int value) : Vitamin(x, y, rotation) {
        this->value = value;
        type = VType::VSpeed;
        this->setTexture("/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/vs.png");
    }
};

#endif /* Vitamin_hpp */
