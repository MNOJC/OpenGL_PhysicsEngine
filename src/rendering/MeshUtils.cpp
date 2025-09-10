//
// Created by natha on 10/09/2025.
//

#include "MeshUtils.h"
#include <cmath>
#include <memory>
#include "Mesh.h"

std::shared_ptr<Mesh> MeshUtils::CreatePlane(float width, float depth) {
    std::vector<float> vertices = {
        // Positions          // Colors (vert pour le sol)
        -width/2, 0.0f, -depth/2,  0.3f, 0.6f, 0.3f,  // Vertex 0
         width/2, 0.0f, -depth/2,  0.3f, 0.6f, 0.3f,  // Vertex 1
         width/2, 0.0f,  depth/2,  0.3f, 0.6f, 0.3f,  // Vertex 2
        -width/2, 0.0f,  depth/2,  0.3f, 0.6f, 0.3f   // Vertex 3
    };
    
    std::vector<unsigned int> indices = {
        0, 1, 2,  
        2, 3, 0   
    };
    
    return std::make_shared<Mesh>(vertices, indices);
}