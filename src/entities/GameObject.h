//
// Created by natha on 06/09/2025.
//

#pragma once

#include <glm/glm.hpp>
#include "../rendering/Mesh.h"
#include <memory>


class GameObject {

public:

    GameObject(std::shared_ptr<Mesh> mesh);

    void Update(float deltaTime);
    void Render() const;

    glm::mat4 GetModelMatrix() const;

    glm::vec3 position = {0, 0, 0};
    glm::vec3 rotation = {0, 0, 0};
    glm::vec3 scale = {1, 1, 1};

    glm::vec3 velocity = {0, 0, 0};
    glm::vec3 acceleration = {0, 0, 0};

private:

    std::shared_ptr<Mesh> m_mesh;
};
