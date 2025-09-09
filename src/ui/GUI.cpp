//
// Created by natha on 05/09/2025.
//

#include "GUI.h"
#include "../core/Window.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

GUI::GUI()
{
    std::cout << "GUI created" << std::endl;
}

GUI::~GUI()
{
    Shutdown();
    std::cout << "GUI destroyed" << std::endl;
}

void GUI::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    std::cout << "GUI shutdown" << std::endl;
}

void GUI::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUI::EndFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::RenderSidePanel()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(300, ImGui::GetIO().DisplaySize.y));
    
    ImGui::Begin("Control Panel", nullptr, 
        ImGuiWindowFlags_NoMove | 
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar);
    
    if (ImGui::CollapsingHeader("PERFORMANCE", ImGuiTreeNodeFlags_DefaultOpen))
    {
        RenderPerformanceSection();
    }
    
    if (ImGui::CollapsingHeader("RENDERER SETTINGS", ImGuiTreeNodeFlags_DefaultOpen))
    {
        RenderRendererSection();
    }
    
    if (ImGui::CollapsingHeader("SCENE HIERARCHY", ImGuiTreeNodeFlags_DefaultOpen))
    {
        RenderSceneHierarchySection();
    }
    
    if (ImGui::CollapsingHeader("PHYSICS SETTINGS", ImGuiTreeNodeFlags_DefaultOpen))
    {
        RenderPhysicsSection();
    }
    
    ImGui::End();
}

void GUI::RenderPhysicsSection()
{
    AddSliderFloat("Gravity", &m_gravityValue, 0.0f, 20.0f, "%.2f m/s²");
    
    ImGui::Spacing();
    
    if (AddButton("Add Cube"))
    {
        std::cout << "Add Cube button pressed" << std::endl;
    }
    
    if (AddButton("Clear All"))
    {
        std::cout << "Clear All button pressed" << std::endl;
    }
    
    ImGui::Spacing();
}

bool  GUI::AddButton(const std::string &label)
{
    return ImGui::Button(label.c_str());
}

void GUI::AddSliderFloat(const std::string& label, float* value, float min, float max, const char* format)
{
    ImGui::SliderFloat(label.c_str(), value, min, max, format);
}

void GUI::AddSliderInt(const std::string& label, int* value, int min, int max, const char* format)
{
    ImGui::SliderInt(label.c_str(), value, min, max, format);
}

void GUI::AddCheckbox(const std::string &label, bool *value)
{
    ImGui::Checkbox(label.c_str(), value);
}

void GUI::AddText(const std::string &text)
{
    ImGui::Text("%s", text.c_str());
}

void GUI::SetPerformanceData(int fps, float frameTime, float deltaTime)
{
    m_fps = fps;
    m_frameTime = frameTime;
    m_deltaTime = deltaTime;
}

void GUI::SetSceneObjects(const std::vector<std::shared_ptr<GameObject>> &objects)
{
    m_sceneObjects = objects;
}

void GUI::SetSelectedObject(std::shared_ptr<GameObject> object)
{
    m_selectedObject = object;
}

void GUI::SetupStyle()
{
    ImGui::StyleColorsDark();
    
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 5.0f;
    style.FrameRounding = 3.0f;
    style.GrabRounding = 3.0f;

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.94f);
    colors[ImGuiCol_Header] = ImVec4(0.29f, 0.00f, 0.51f, 1.00f); 
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.39f, 0.00f, 0.61f, 1.00f); 
    colors[ImGuiCol_HeaderActive] = ImVec4(0.49f, 0.00f, 0.71f, 1.00f); 
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.40f, 0.80f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.45f, 0.85f, 1.00f);

    colors[ImGuiCol_PlotHistogram]       = ImVec4(0.20f, 0.80f, 0.20f, 1.00f); 
    colors[ImGuiCol_PlotHistogramHovered]= ImVec4(0.30f, 0.90f, 0.30f, 1.00f);
}

void GUI::Initialize(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    
    SetupStyle();

    std::cout << "GUI initialized successfully" << std::endl;
}

void GUI::Render()
{
    RenderSidePanel();
}

void GUI::RenderPerformanceSection()
{
    ImGui::Text("FPS: %d", m_fps);
    ImGui::Text("Frame Time: %.2f ms", m_frameTime);
    ImGui::Text("Delta Time: %.3f s", m_deltaTime);

    ImGui::Spacing();
    
    
    float fpsRatio = static_cast<float>(m_fps) / 144.0f;
    ImGui::ProgressBar(fpsRatio, ImVec2(-1, 0), "FPS BAR");
    ImGui::Dummy(ImVec2(0, 10));
}

void GUI::RenderRendererSection()
{
    AddCheckbox("Wireframe Mode", &m_wireframeMode);
    AddCheckbox("Depth Test", &m_depthTest);
    
    static float bgColor[3] = {0.2f, 0.3f, 0.4f};
    AddSliderFloat("R", &bgColor[0], 0.0f, 1.0f, "%.3f");
    AddSliderFloat("G", &bgColor[1], 0.0f, 1.0f, "%.3f");
    AddSliderFloat("B", &bgColor[2], 0.0f, 1.0f, "%.3f");

    m_clearColorValue = glm::vec3(bgColor[0], bgColor[1], bgColor[2]);
    
    if (AddButton("Reset Background Color"))
    {
        bgColor[0] = 0.2f; bgColor[1] = 0.3f; bgColor[2] = 0.4f;
    }
    
    ImGui::Spacing();
    ImGui::Dummy(ImVec2(0, 5));
}

void GUI::RenderSceneHierarchySection()
{
    if (m_sceneObjects.empty()) {
        ImGui::Text("No objects in scene");
        return;
    }
    
    for (size_t i = 0; i < m_sceneObjects.size(); ++i) {
        std::string label = "Object " + std::to_string(i);
        if (ImGui::Selectable(label.c_str(), m_selectedObject == m_sceneObjects[i])) {
            m_selectedObject = m_sceneObjects[i];
        }
    }
    ImGui::Dummy(ImVec2(0, 5));
}