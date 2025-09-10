//
// Created by natha on 10/09/2025.
//

#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../entities/GameObject.h"

class Scene {
public:

    virtual ~Scene() = default;

    virtual void Load();
    virtual void Unload();
    virtual void Update(float deltaTime);
    virtual void Render();

    const std::vector<std::shared_ptr<GameObject>>& GetObjects() const { return m_objects; }
    const std::string& GetName() const { return m_name; }

protected:
    
    std::vector<std::shared_ptr<GameObject>> m_objects;
    std::string m_name = "Unnamed Scene";
};

