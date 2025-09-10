//
// Created by natha on 10/09/2025.
//

#pragma once

#include "../Scene.h"

class DefaultScene : public Scene {

public:
    DefaultScene();
    
    void Load() override;
    void Unload() override;
    void Update(float deltaTime) override;
    void Render() override;


private:
    
    std::shared_ptr<GameObject> CreateGround();
    std::shared_ptr<GameObject> CreateCube(const glm::vec3& position);
};

