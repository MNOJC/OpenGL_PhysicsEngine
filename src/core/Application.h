//
// Created by natha on 05/09/2025.
//

#pragma once

#include "../rendering/Shader.h"
#include "Window.h"
#include <memory>
#include "../rendering/Renderer.h"
#include "../ui/GUI.h"
#include "Time.h"
#include "../entities/GameObject.h"
#include "../rendering/Camera.h"

class Application {
public:

    Application();
    ~Application();

    void Run();

private:

    void Initialize();
    void Shutdown();
    void ProcessInput();
    void ProcessScroll(double xoffset, double yoffset);
    void ProcessMouse(double xpos, double ypos);
    void Update(float deltaTime);
    void Render();
    void SpawnObjects(std::shared_ptr<Mesh> mesh);

    std::unique_ptr<Window> m_window;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Camera> m_camera;
    std::vector<std::shared_ptr<GameObject>> m_gameObjects;
    std::unique_ptr<Time> m_time;
    std::unique_ptr<GUI> m_gui;

    bool m_isRunning;
    float m_colorTime;
    bool m_firstMouse;
    bool m_cameraMouseControl;
    double m_lastMouseX, m_lastMouseY;
    
};


