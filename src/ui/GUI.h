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


class GUI {
public:
    GUI();
    ~GUI();
    
    void Initialize(GLFWwindow* window);
    void Shutdown();

    void BeginFrame();
    void Render();
    void EndFrame();

    void RenderSidePanel();                
    void RenderPerformanceSection();       
    void RenderRendererSection();          
    void RenderSceneHierarchySection();    
    void RenderPhysicsSection();

    bool  AddButton(const std::string& label);
    void AddSliderFloat(const std::string& label, float* value, float min, float max, const char* format);
    void AddSliderInt(const std::string& label, int* value, int min, int max, const char* format);
    void AddCheckbox(const std::string& label, bool* value);
    void AddText(const std::string& text);

    void SetPerformanceData(int fps, float frameTime, float deltaTime);
    void SetSceneObjects(const std::vector<std::shared_ptr<GameObject>>& objects);
    void SetSelectedObject(std::shared_ptr<GameObject> object);

    bool IsWireframeEnabled() const { return m_wireframeMode; }
    float GetGravityValue() const { return m_gravityValue; }

private:


    void SetupStyle();
    
    std::vector<std::shared_ptr<GameObject>> m_sceneObjects;
    std::shared_ptr<GameObject> m_selectedObject;

    bool m_wireframeMode = false;
    float m_gravityValue = 9.81f;

    int m_fps = 0;
    float m_frameTime = 0.0f;
    float m_deltaTime = 0.0f;

    bool m_showPerformance = true;
    bool m_showRenderer = true;
    bool m_showSceneHierarchy = true;
    bool m_showPhysics = true;
    bool m_depthTest = true;
};

