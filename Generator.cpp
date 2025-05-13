//
//  Generator.cpp
//  Viruses
//
//  Created by Александер on 10.05.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#include "Generator.hpp"

Vector2f Generator::generatePositionPolar() {
    auto fradius = radiusDist(rng);
    auto fangle = angleDist(rng) * 0.3 + angleDist(rng) * 0.7;

    return {(float)(fradius * std::cos(fangle)), (float)(fradius * std::sin(fangle))};
}

float Generator::generateBetweenZero() {
    return dist(rng);
}
