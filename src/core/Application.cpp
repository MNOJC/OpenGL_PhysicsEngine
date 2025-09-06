//
// Created by natha on 05/09/2025.
//

#include <GL/glew.h> 
#include "Application.h"
#include <iostream>
#include <chrono>
#include "../entities/GameObject.h"
#include "../entities/CubeMesh.h"

Application::Application() : m_isRunning(false), m_lastFrameTime(0.0f) {}

Application::~Application()
{
    Shutdown();
}

void Application::Run()
{
    Initialize();

    if (!m_isRunning)
    {
        return;
    }

    while (m_isRunning)
    {
        float currentTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentTime - m_lastFrameTime;
        m_lastFrameTime = currentTime;

        ProcessInput();
        Update(deltaTime);
        Render();
    }

    Shutdown();
}

void Application::Initialize()
{
    m_window = std::make_unique<Window>(800, 600, "Physics Engine");
    if (!m_window->Initialize())
    {
        std::cerr << "Failed to initialize window." << std::endl;
        m_isRunning = false;
        return;
    }

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        m_isRunning = false;
        return;
    }

    m_colorTime = 0.0f;
    m_shader = std::make_unique<Shader>("../shaders/vertex_shader.vert", "../shaders/fragment_shader.frag");

    auto cubeMesh = CubeMesh::Create();
    auto gameObject = std::make_shared<GameObject>(cubeMesh);
    gameObject->position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_gameObjects.push_back(gameObject);
    
    
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, m_window->GetWidth(), m_window->GetHeight());

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    m_lastFrameTime = static_cast<float>(glfwGetTime());
    m_isRunning = true;
    
}

void Application::Shutdown()
{
    m_shader.reset();
    m_window.reset();
    glfwTerminate();
}

void Application::ProcessInput()
{
    if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        m_isRunning = false;
    }
}

void Application::Update(float deltaTime)
{
    for (auto& obj : m_gameObjects)
    {
        obj->Update(deltaTime);
    }
}

void Application::Render()
{
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader->Use();
    
    m_colorTime += 0.05f;
    float r = (sin(m_colorTime * 0.7f) + 1.0f) / 2.0f;  // Entre 0 et 1
    float g = (sin(m_colorTime * 1.3f) + 1.0f) / 2.0f;  // Entre 0 et 1
    float b = (sin(m_colorTime * 2.1f) + 1.0f) / 2.0f;  // Entre 0 et 1
    m_shader->SetVec4("u_Color", glm::vec4(r, g, b, 1.0f));

    for (auto& obj : m_gameObjects)
    {
        obj->Render();
    }


    m_window->SwapBuffers();
    m_window->PollEvents();

    if (m_window->ShouldClose())
    {
        m_isRunning = false;
    }
}