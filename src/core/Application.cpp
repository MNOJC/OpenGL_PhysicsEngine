//
// Created by natha on 05/09/2025.
//

#include <GL/glew.h> 
#include "Application.h"
#include <iostream>
#include <chrono>
#include <imgui.h>
#include "../entities/GameObject.h"
#include "../entities/CubeMesh.h"

Application::Application() : m_isRunning(false) {}

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
        m_time->Update();
        
        ProcessInput();
        Update(m_time->GetDeltaTime());
        Render();
    }

    Shutdown();
}

void Application::Initialize()
{

    m_time = std::make_unique<Time>();
    
    m_cameraMouseControl = false;
    
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
    
    m_shader = std::make_unique<Shader>("../shaders/vertex_shader.vert", "../shaders/fragment_shader.frag");

    auto cubeMesh = CubeMesh::Create();
    auto gameObject = std::make_shared<GameObject>(cubeMesh);
    gameObject->position = glm::vec3(0.0f, 0.0f, 0.0f);
    gameObject->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    gameObject->scale = glm::vec3(1.0f, 1.0f, 1.0f);
    m_gameObjects.push_back(gameObject);

    m_camera = std::make_unique<Camera>(glm::vec3(-3.0f, 0.0f, 0.0f));
    
    m_lastMouseX = m_window->GetWidth() / 2.0f;
    m_lastMouseY = m_window->GetHeight() / 2.0f;
    
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

    m_gui = std::make_unique<GUI>();
    m_gui->Initialize(m_window->GetWindow());
    
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
    if (glfwGetMouseButton(m_window->GetWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        if (!m_cameraMouseControl)
        {
            m_cameraMouseControl = true;
            m_firstMouse = true;
            glfwSetInputMode(m_window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    } else
    {
        if (m_cameraMouseControl)
        {
            m_cameraMouseControl = false;
            glfwSetInputMode(m_window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    if (m_cameraMouseControl)
    {
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            m_isRunning = false;

        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
            m_camera->ProcessKeyboard(0, m_time->GetDeltaTime()); 
    
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
            m_camera->ProcessKeyboard(1, m_time->GetDeltaTime()); 
    
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
            m_camera->ProcessKeyboard(2, m_time->GetDeltaTime()); 
    
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
            m_camera->ProcessKeyboard(3, m_time->GetDeltaTime());
        
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_Q) == GLFW_PRESS)
            m_camera->ProcessKeyboard(4, m_time->GetDeltaTime());

        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_E) == GLFW_PRESS)
            m_camera->ProcessKeyboard(5, m_time->GetDeltaTime());
    }
    
}

void Application::ProcessScroll(double xoffset, double yoffset)
{
    m_camera->ProcessMouseScroll(yoffset);
}

void Application::ProcessMouse(double xpos, double ypos)
{
    if (!m_cameraMouseControl) {
        m_firstMouse = true; 
        return;
    }
    
    int windowWidth, windowHeight;
    glfwGetWindowSize(m_window->GetWindow(), &windowWidth, &windowHeight);
    double centerX = windowWidth / 2.0;
    double centerY = windowHeight / 2.0;
    
    if (m_firstMouse) {
        m_lastMouseX = xpos;
        m_lastMouseY = ypos;
        m_firstMouse = false;
        
        return;
    }
    
    float xoffset = xpos - m_lastMouseX;
    float yoffset = m_lastMouseY - ypos;
    
    m_lastMouseX = xpos;
    m_lastMouseY = ypos;
    
    m_camera->ProcessMouseMovement(xoffset, yoffset);

    if (abs(xpos - centerX) > windowWidth * 0.3 || abs(ypos - centerY) > windowHeight * 0.3)
    {
        glfwSetCursorPos(m_window->GetWindow(), centerX, centerY);
        m_lastMouseX = centerX;
        m_lastMouseY = centerY;
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
    glm::vec3 ClearColor = m_gui->GetClearColorValue();
    
    glClearColor(ClearColor[0], ClearColor[1], ClearColor[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_gui->IsWireframeEnabled())
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glm::mat4 view = m_camera->GetViewMatrix();
    glm::mat4 projection = m_camera->GetProjectionMatrix(static_cast<float>(m_window->GetWidth()) / static_cast<float>(m_window->GetHeight()));
    
    
    m_shader->Use();
    m_shader->SetMat4("view", view);
    m_shader->SetMat4("projection", projection);
    m_shader->SetVec4("u_Color", glm::vec4(1, 1, 1, 1.0f));

    m_gui->SetPerformanceData(m_time->GetFPS(), m_time->GetDeltaTime() * 1000.0f, m_time->GetDeltaTime());

    for (auto& obj : m_gameObjects)
    {
        m_gui->SetSceneObjects(m_gameObjects);
        m_shader->SetMat4("model", obj->GetModelMatrix());
        obj->Render();
    }
    
    m_gui->BeginFrame();
    m_gui->RenderSidePanel(); 
    m_gui->EndFrame();
    
    m_window->SwapBuffers();
    m_window->PollEvents();

    

    if (m_window->ShouldClose())
    {
        m_isRunning = false;
    }
    
}