//
// Created by natha on 10/09/2025.
//

#pragma once

#include "../Scene.h"

class SphereScene : public Scene {

public:

    SphereScene();
        
    void Load() override;
    void Unload() override;
    void Update(float deltaTime) override;
    void Render() override;

private:
    
    std::shared_ptr<GameObject> CreateSphere();

};

