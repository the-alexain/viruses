//
//  GameObject.hpp
//  Viruses
//
//  Created by Александер on 28.02.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

class GameObject {
public:
    int health = 0; int rotation = 0; int w = 0; int h = 0; int maxHealth = 0;
    float speed;
    Texture texture;
    Sprite sprite;
    CircleShape centerDebug;
    float pickupRadius;
    vector<float*> props;
    float x = 0; float y =0;
    
    GameObject(int x, int y, int rotation, string path = "/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/null.png") {
        this->x = x;
        this->pickupRadius = 0;
        this->y = y;
        this->w = 1;
        this->h = 1;
        this->rotation = rotation;
        this->centerDebug = CircleShape(5);
        this->centerDebug.setFillColor(Color::Black);
        this->centerDebug.setPosition(x, y);
        this->setTexture(path);
    }
    
    bool isClose(const float x1, const float y1, const float x2, const float y2, float radius);
    void setPosition(int x, int y);
    void updateTexture();
    void setTexture(string path);
    void move(int x, int y);
    virtual void update(float dt = 0.f);
    void setRotate(int angle);
    void remove();
    
    float clamp(float n, float lower, float upper);
};

#endif /* GameObject_hpp */
