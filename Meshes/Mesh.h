//
// Created by natha on 26/02/2025.
//

#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>


class Mesh {
public:
    
    
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();
    
    void Draw() const;

    unsigned int VAO, VBO, EBO;
    
    std::vector<unsigned int> indices;

    glm::vec3 position = { 0.0f, 0.0f, 0.0f };
    float rotationAngle = 0.0f;
    float velocityY = 0.0f;
};



#endif //MESH_H
