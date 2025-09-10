//
// Created by natha on 10/09/2025.
//

#pragma once

#include <memory>
#include <unordered_map>
#include "Scene.h"
#include <functional>
#include "../core/CallbackRegistry.h"


class SceneManager {
public:

    SceneManager();
    ~SceneManager();

    void Initialize();
    void LoadScene(const std::string& sceneName);
    void ReloadCurrentScene();

    void Update(float deltaTime);
    void Render();

    template<typename T>
    void RegisterScene(const std::string& name)
    {
        m_sceneRegistry[name] = []() { return std::make_shared<T>(); };
    }

    std::shared_ptr<Scene> GetCurrentScene() const { return m_currentScene; }
    const std::vector<std::string>& GetAvailableScenes() const { return m_availableScenes; }


private:
    
    std::shared_ptr<Scene> m_currentScene;
    std::unordered_map<std::string, std::function<std::shared_ptr<Scene>()>> m_sceneRegistry;
    std::vector<std::string> m_availableScenes;
};

