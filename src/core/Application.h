//
// Created by natha on 05/09/2025.
//

#pragma once

#include "../rendering/Shader.h"
#include "Window.h"
#include <memory>
#include "../entities/GameObject.h"

class Application {
public:

    Application();
    ~Application();

    void Run();

private:

    void Initialize();
    void Shutdown();
    void ProcessInput();
    void Update(float deltaTime);
    void Render();

    std::unique_ptr<Window> m_window;
    std::unique_ptr<Shader> m_shader;

    bool m_isRunning;
    float m_lastFrameTime;
    std::vector<std::shared_ptr<GameObject>> m_gameObjects;
    float m_colorTime;
};


