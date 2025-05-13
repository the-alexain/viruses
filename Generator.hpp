//
//  Generator.hpp
//  Viruses
//
//  Created by Александер on 10.05.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#ifndef Generator_hpp
#define Generator_hpp

#include <stdio.h>
#include <random>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Generator {
public:
    std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<double> angleDist{0.0, 2 * 3.14159f};
    std::uniform_real_distribution<double> radiusDist{0.0, 10000.f};
    std::uniform_real_distribution<double> dist{0.0, 1.0};
    
    Generator() {};
    
    Vector2f generatePositionPolar();
    float generateBetweenZero();
};

#endif /* Generator_hpp */
