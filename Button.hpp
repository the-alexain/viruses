//
//  Button.hpp
//  Viruses
//
//  Created by Александер on 19.04.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

#include <stdio.h>
#include <iostream>
#include "GameObject.hpp"

using namespace sf;
using namespace std;

class Button : public GameObject {
public:

    Button(string path) : GameObject(0, 0, 0, path) {};
};

#endif /* Button_hpp */
