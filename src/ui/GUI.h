//
// Created by natha on 05/09/2025.
//

#pragma once

#include "../entities/GameObject.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <map>

#include "../Scene/SceneManager.h"


class GUI {
public:
    GUI();
    ~GUI();
    
    void Initialize(GLFWwindow* window);
    void Shutdown();

    void BeginFrame();
    void Render();
    void EndFrame();

    void RenderLeftSidePanel();
    void RenderRightSidePanel();  
    void RenderPerformanceSection();       
    void RenderRendererSection();          
    void RenderSceneHierarchySection();    
    void RenderPhysicsSection();
    void RenderCameraSection();
    void RenderSceneSection();

    bool  AddButton(const std::string& label);
    void AddSliderFloat(const std::string& label, float* value, float min, float max, const char* format);
    void AddSliderInt(const std::string& label, int* value, int min, int max, const char* format);
    void AddCheckbox(const std::string& label, bool* value);
    void AddText(const std::string& text);

    void SetPerformanceData(int fps, float frameTime, float deltaTime);
    void SetCameraControlsData(float sensitivity, float speed);
    void SetSceneObjects(const std::vector<std::shared_ptr<GameObject>>& objects);
    void SetSelectedObject(std::shared_ptr<GameObject> object);

    bool IsWireframeEnabled() const { return m_wireframeMode; }
    bool IsDepthTestEnabled() const { return m_depthTest; }
    float GetGravityValue() const { return m_gravityValue; }
    glm::vec3 GetClearColorValue() const { return m_clearColorValue ; };
    void GetCameraControlsData(float &sensibility, float &speed) { sensibility = m_cameraSensitivity; speed = m_cameraSpeed; };
    int GetObjectIndex(const std::shared_ptr<GameObject>& object);
    std::shared_ptr<GameObject> GetSelectedObject() {return m_selectedObject;};
    void SetSceneManager(std::shared_ptr<SceneManager> sceneManager);

    void RegisterCallback(const std::string& buttonName, std::function<void()> callback);
    void ExecuteCallback(const std::string& buttonName);

private:


    void SetupStyle();

    std::map<std::string, std::function<void()>> m_callbacks;
    
    std::vector<std::shared_ptr<GameObject>> m_sceneObjects;
    std::shared_ptr<GameObject> m_selectedObject;
    std::shared_ptr<SceneManager> m_sceneManager;

    bool m_wireframeMode = false;
    float m_gravityValue = 9.81f;

    int m_fps = 0;
    float m_frameTime = 0.0f;
    float m_deltaTime = 0.0f;

    float m_cameraSensitivity;
    float m_cameraSpeed;

    bool m_showPerformance = true;
    bool m_showRenderer = true;
    bool m_showSceneHierarchy = true;
    bool m_showPhysics = true;
    bool m_depthTest = true;

    glm::vec3 m_clearColorValue = glm::vec3(0.0f, 0.0f, 0.0f);
};

