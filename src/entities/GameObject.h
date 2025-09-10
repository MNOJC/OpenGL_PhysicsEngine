//
// Created by natha on 06/09/2025.
//

#pragma once

#include <glm/glm.hpp>
#include "../rendering/Mesh.h"
#include "../rendering/Shader.h"
#include <memory>
#include <iostream>


class GameObject {

public:

    GameObject(std::shared_ptr<Mesh> mesh);
    ~GameObject(){
        std::cout << "GameObject destroyed" << std::endl;
    };

    void Update(float deltaTime);
    void Render() const;

    glm::mat4 GetModelMatrix() const;

    glm::vec3 position = {0, 0, 0};
    glm::vec3 rotation = {0, 0, 0};
    glm::vec3 scale = {1, 1, 1};

    glm::vec3 velocity = {0, 0, 0};
    glm::vec3 acceleration = {0, 0, 0};

    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    std::shared_ptr<Mesh> GetMesh() const { return m_mesh; }

private:

    std::shared_ptr<Mesh> m_mesh;
};
