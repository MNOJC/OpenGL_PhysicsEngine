//
// Created by natha on 06/09/2025.
//

#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject(std::shared_ptr<Mesh> mesh) : m_mesh(mesh) {}

void GameObject::Update(float deltaTime)
{
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
}

void GameObject::Render() const {
    
    m_mesh->Draw();
}

glm::mat4 GameObject::GetModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    return model;
}
