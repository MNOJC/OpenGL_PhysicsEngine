//
// Created by natha on 27/02/2025.
//

#include "Platform.h"

#include <iostream>
#include <ostream>

Platform::Platform() : Mesh(PlatformVertices(), PlatformIndices()) {
    std::cout << "Construct CubeMesh" << std::endl;
}

std::vector<float> Platform::PlatformVertices() {
    return {
        -20.0f, -10.0f, -20.0f,  0.5f, 0.5f, 0.5f,  
        20.0f, -10.0f, -20.0f,  0.5f, 0.5f, 0.5f,  
        20.0f, -10.0f,  20.0f,  0.5f, 0.5f, 0.5f,  
        -20.0f, -10.0f,  20.0f,  0.5f, 0.5f, 0.5f   
    };
}

std::vector<unsigned int> Platform::PlatformIndices() {
    return {
        0, 1, 2, 
        2, 3, 0 
    };
}


Platform::~Platform() {
    std::cout << "Destroying CubeMesh" << std::endl;
}
