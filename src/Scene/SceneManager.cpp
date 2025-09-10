//
// Created by natha on 10/09/2025.
//

#include "SceneManager.h"
#include <iostream>
#include <algorithm>

SceneManager::SceneManager()
{
    std::cout << "SceneManager created" << std::endl;
}

SceneManager::~SceneManager()
{
    if (m_currentScene) {
        m_currentScene->Unload();
    }
    std::cout << "SceneManager destroyed" << std::endl;
}

void SceneManager::Initialize()
{
    std::cout << "Initializing SceneManager..." << std::endl;

    for (const auto& pair : m_sceneRegistry) {
        m_availableScenes.push_back(pair.first);
    }

    std::sort(m_availableScenes.begin(), m_availableScenes.end());

    std::cout << "Registered scenes: ";
    for (const auto& scene : m_availableScenes) {
        std::cout << scene << " ";
    }
    std::cout << std::endl;
}

void SceneManager::LoadScene(const std::string& sceneName) {

    auto it = m_sceneRegistry.find(sceneName);
    if (it == m_sceneRegistry.end())
    {
        std::cerr << "ERROR: Scene '" << sceneName << "' not registered!" << std::endl;
        return;
    }
    
    if (m_currentScene)
    {
        std::cout << "Unloading current scene: " << m_currentScene->GetName() << std::endl;
        m_currentScene->Unload();
    }
    
    std::cout << "Loading scene: " << sceneName << std::endl;
    m_currentScene = it->second();
    
    try {
        m_currentScene->Load();
        std::cout << "Scene loaded successfully: " << m_currentScene->GetName() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "ERROR loading scene: " << e.what() << std::endl;
        m_currentScene = nullptr;
    }

    CallbackRegistry::Instance().ExecuteCallback("ReloadScene");
}

void SceneManager::ReloadCurrentScene()
{
    if (!m_currentScene) {
        std::cout << "No current scene to reload" << std::endl;
        return;
    }
    
    std::string currentSceneName = m_currentScene->GetName();
    std::cout << "Reloading scene: " << currentSceneName << std::endl;
    
    
    std::string sceneKey;
    for (const auto& pair : m_sceneRegistry) {
        auto tempScene = pair.second();
        if (tempScene->GetName() == m_currentScene->GetName()) {
            sceneKey = pair.first;
            break;
        }
    }

    m_currentScene->Unload();
    m_currentScene.reset();

    LoadScene(sceneKey);

}

void SceneManager::Update(float deltaTime)
{
    if (m_currentScene)
    {
        m_currentScene->Update(deltaTime);
    }
}

void SceneManager::Render()
{
    if (m_currentScene)
    {
        m_currentScene->Render();
    }
}