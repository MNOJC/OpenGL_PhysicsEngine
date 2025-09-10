//
// Created by natha on 10/09/2025.
//

#include "SphereScene.h"
#include "../../rendering/MeshUtils.h"



SphereScene::SphereScene()
{
    m_name = "Sphere";
}

void SphereScene::Load()
{
    std::cout << "Loading Default Scene..." << std::endl;
    
    auto ground = CreateSphere();
    m_objects.push_back(ground);
    
    std::cout << "Default Scene loaded with " << m_objects.size() << " objects" << std::endl;
}

std::shared_ptr<GameObject> SphereScene::CreateSphere()
{
    auto groundMesh = MeshUtils::CreateSphere(10.0f, 100.0f);
    auto ground = std::make_shared<GameObject>(groundMesh);
    
    ground->position = glm::vec3(0.0f, -10.0f, 0.0f);
    ground->color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f); 
    
    return ground;
}

void SphereScene::Unload() {
    Scene::Unload();
}

void SphereScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}

void SphereScene::Render()
{
    Scene::Render();
}
