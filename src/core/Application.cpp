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

    m_camera = std::make_unique<Camera>(glm::vec3(-3.0f, 0.0f, 0.0f));
    m_lastX = m_window->GetWidth() / 2.0f;
    m_lastY = m_window->GetHeight() / 2.0f;
    m_firstMouse = true;

    glfwSetWindowUserPointer(m_window->GetWindow(), this);
    auto mouseCallback = [](GLFWwindow* window, double xpos, double ypos) {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->ProcessMouse(xpos, ypos);
    };

    glfwSetCursorPosCallback(m_window->GetWindow(), mouseCallback);

    auto scrollCallback = [](GLFWwindow* window, double xoffset, double yoffset) {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->ProcessScroll(xoffset, yoffset);
    };
    glfwSetScrollCallback(m_window->GetWindow(), scrollCallback);

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
        m_isRunning = false;

    if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
        m_camera->ProcessKeyboard(0, m_lastFrameTime); 
    
    if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
        m_camera->ProcessKeyboard(1, m_lastFrameTime); 
    
    if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
        m_camera->ProcessKeyboard(2, m_lastFrameTime); 
    
    if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
        m_camera->ProcessKeyboard(3, m_lastFrameTime); 
    
    
}

void Application::ProcessScroll(double xoffset, double yoffset)
{
    m_camera->ProcessMouseScroll(yoffset);
}

void Application::ProcessMouse(double xpos, double ypos)
{
    if (m_firstMouse) {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }
    
    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos;
    
    m_lastX = xpos;
    m_lastY = ypos;
    
    m_camera->ProcessMouseMovement(xoffset, yoffset);
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

    glm::mat4 view = m_camera->GetViewMatrix();
    glm::mat4 projection = m_camera->GetProjectionMatrix(static_cast<float>(m_window->GetWidth()) / static_cast<float>(m_window->GetHeight()));
    
    
    m_shader->Use();
    m_shader->SetMat4("view", view);
    m_shader->SetMat4("projection", projection);
    
    m_colorTime += 0.05f;
    float r = (sin(m_colorTime * 0.7f) + 1.0f) / 2.0f;  // Entre 0 et 1
    float g = (sin(m_colorTime * 1.3f) + 1.0f) / 2.0f;  // Entre 0 et 1
    float b = (sin(m_colorTime * 2.1f) + 1.0f) / 2.0f;  // Entre 0 et 1
    m_shader->SetVec4("u_Color", glm::vec4(r, g, b, 1.0f));

    for (auto& obj : m_gameObjects)
    {
        m_shader->SetMat4("model", obj->GetModelMatrix());
        obj->Render();
    }


    std::cout << "=== DEBUG INFO ===" << std::endl;
    std::cout << "Camera position: " << m_camera->GetPosition().x << ", " 
              << m_camera->GetPosition().y << ", " 
              << m_camera->GetPosition().z << std::endl;

    for (size_t i = 0; i < m_gameObjects.size(); ++i) {
        std::cout << "Cube " << i << " position: " 
                  << m_gameObjects[i]->position.x << ", "
                  << m_gameObjects[i]->position.y << ", "
                  << m_gameObjects[i]->position.z << std::endl;
    }
    
    m_window->SwapBuffers();
    m_window->PollEvents();

    if (m_window->ShouldClose())
    {
        m_isRunning = false;
    }
}