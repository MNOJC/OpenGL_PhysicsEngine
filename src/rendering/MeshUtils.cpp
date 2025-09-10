//
// Created by natha on 10/09/2025.
//

#include "MeshUtils.h"
#include <cmath>
#include <memory>
#include "Mesh.h"
#include <cmath>
#include <iostream>
#include "glm/glm.hpp"

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

std::shared_ptr<Mesh> MeshUtils::CreateSphere(float radius, int segments)
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
    // Validation des paramètres
    segments = std::max(3, segments); // Minimum 3 segments
    radius = std::max(0.1f, radius);  // Rayon minimum 0.1
    
    // Couleur de base pour la sphère (blanc)
    const glm::vec3 baseColor(1.0f, 1.0f, 1.0f);
    
    // Génération des vertices
    for (int i = 0; i <= segments; ++i) {
        float latAngle = M_PI * static_cast<float>(i) / segments; // [0, π]
        
        for (int j = 0; j <= segments; ++j) {
            float longAngle = 2.0f * M_PI * static_cast<float>(j) / segments; // [0, 2π]
            
            // Position
            float x = radius * sin(latAngle) * cos(longAngle);
            float y = radius * cos(latAngle);
            float z = radius * sin(latAngle) * sin(longAngle);
            
            // Ajoute la position (3 floats)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            
            // Ajoute la couleur (3 floats) - même couleur pour tous les vertices
            vertices.push_back(baseColor.r);
            vertices.push_back(baseColor.g);
            vertices.push_back(baseColor.b);
        }
    }
    
    // Génération des indices
    for (int i = 0; i < segments; ++i) {
        for (int j = 0; j < segments; ++j) {
            int first = i * (segments + 1) + j;
            int second = first + segments + 1;
            
            // Premier triangle
            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);
            
            // Deuxième triangle
            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
    
    std::cout << "Created sphere with " << vertices.size()/6 << " vertices and " 
              << indices.size()/3 << " triangles" << std::endl;
    
    return std::make_shared<Mesh>(vertices, indices);
}
