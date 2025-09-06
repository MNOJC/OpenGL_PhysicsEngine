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