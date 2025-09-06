//
// Created by natha on 26/02/2025.
//

#pragma once

#include <GL/glew.h>
#include <vector>

class Mesh {
public:

    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void Draw() const;

private:
    
    GLuint m_VAO, m_VBO, m_EBO;
    std::vector<unsigned int> m_indices;
};

