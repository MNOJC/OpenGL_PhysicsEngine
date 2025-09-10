//
// Created by natha on 10/09/2025.
//

#include "DefaultScene.h"
#include "../../rendering/MeshUtils.h"

DefaultScene::DefaultScene()
{
    m_name = "Default";
}

void DefaultScene::Load()
{
    std::cout << "Loading Default Scene..." << std::endl;
    
    auto ground = CreateGround();
    m_objects.push_back(ground);
    
    std::cout << "Default Scene loaded with " << m_objects.size() << " objects" << std::endl;
}

std::shared_ptr<GameObject> DefaultScene::CreateGround()
{
    auto groundMesh = MeshUtils::CreatePlane(20.0f, 20.0f);
    auto ground = std::make_shared<GameObject>(groundMesh);
    
    ground->position = glm::vec3(0.0f, 5.0f, 0.0f);
    ground->color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f); 
    
    return ground;
}

void DefaultScene::Unload() {
    std::cout << "Unloading Default Scene..." << std::endl;
    m_objects.clear();
}

void DefaultScene::Update(float deltaTime)
{
  
}

void DefaultScene::Render()
{

}