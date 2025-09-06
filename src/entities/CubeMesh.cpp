//
// Created by natha on 26/02/2025.
//

#include "../../src/entities/CubeMesh.h"


std::shared_ptr<Mesh> CubeMesh::Create()
{
    return std::make_shared<Mesh>(GetVertices(), GetIndices());
}

std::vector<float> CubeMesh::GetVertices() {
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

std::vector<unsigned int> CubeMesh::GetIndices() {
    return {
        0, 1, 2, 2, 3, 0,  
        4, 5, 6, 6, 7, 4, 
        4, 5, 1, 1, 0, 4, 
        7, 6, 2, 2, 3, 7,  
        4, 0, 3, 3, 7, 4, 
        5, 1, 2, 2, 6, 5 
    };
}




