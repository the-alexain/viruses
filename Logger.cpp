//
//  Logger.cpp
//  Viruses
//
//  Created by Александер on 13.04.2025.
//  Copyright © 2025 Александер. All rights reserved.
//

#include "Logger.hpp"
#include <iostream>

using namespace std;

template<typename T> T logger(T message) {
    cout << message << endl;
}
