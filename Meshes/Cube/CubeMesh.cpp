//
// Created by natha on 26/02/2025.
//

#include "CubeMesh.h"

#include <iostream>
#include <ostream>

CubeMesh::CubeMesh() : Mesh(CubeVertices(), CubeIndices()) {
    std::cout << "Construct CubeMesh" << std::endl;
}

std::vector<float> CubeMesh::CubeVertices() {
    return {
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f  
    };
}

std::vector<unsigned int> CubeMesh::CubeIndices() {
    return {
        0, 1, 2, 2, 3, 0,  
        4, 5, 6, 6, 7, 4, 
        4, 5, 1, 1, 0, 4, 
        7, 6, 2, 2, 3, 7,  
        4, 0, 3, 3, 7, 4, 
        5, 1, 2, 2, 6, 5 
    };
}


CubeMesh::~CubeMesh() {
    std::cout << "Destroying CubeMesh" << std::endl;
}




