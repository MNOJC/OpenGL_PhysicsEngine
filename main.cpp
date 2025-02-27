#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Meshes/Cube/CubeMesh.h"
#include "Meshes/Platform/Platform.h"

float windowsWidth = 1920;
float windowsHeight = 1080;

float gravity = 9.81f;
float deltaTime = 0.016f;

std::vector<std::unique_ptr<CubeMesh>> cubes;

float rotationAngle = 0.0f;

void DrawCube(CubeMesh& cube) {
    cube.Draw();
}

std::string readShaderFile(const char* filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier shader: " << filePath << std::endl;
        return "";
    }

    std::stringstream shaderStream;
    shaderStream << file.rdbuf();
    return shaderStream.str();
}


int main()
{
    GLFWwindow* window;
    
    if (!glfwInit()) return -1;
    
    window = glfwCreateWindow(windowsWidth, windowsHeight, "Cube 3D", NULL, NULL);

    if (!window) {
        std::cerr << "Erreur de création de fenêtre GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    std::string vertexShaderSource = readShaderFile("../shaders/vertex_shader.vert");
    std::string fragmentShaderSource = readShaderFile("../shaders/fragment_shader.frag");
    
    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Erreur d'initialisation de GLEW !" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, windowsWidth, windowsHeight);

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderCode = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderCode = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);
    
    
    GLuint  shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(windowsWidth) / static_cast<float>(windowsHeight), 0.1f, 100.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -50.0f));
    view = glm::rotate(view, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    Platform platformMesh;
    
    while (!glfwWindowShouldClose(window)) {
        
        glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Physics Engine");
        
        ImGui::Text("Cube Generator");
        
        ImGui::Separator();
        
        if (ImGui::Button("Add Cube")) {
            cubes.push_back(std::make_unique<CubeMesh>());
        }
        
        ImGui::Spacing();
        
        if (ImGui::Button("Clear Cubes")) {
            cubes.clear();
        }
        
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glUseProgram(shaderProgram);
        
        glm::mat4 PlatformModel = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(PlatformModel));
        platformMesh.Draw();
        
        for (auto& cube : cubes) {

            cube->velocityY -= gravity * deltaTime; 
            cube->position.y += cube->velocityY * deltaTime;

            if (cube->position.y < -3.0f) {
                cube->position.y = -3.0f;
                cube->velocityY = 0.0f; 
            }
            
            cube->rotationAngle += 1.0f; 
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cube->position);
            model = glm::rotate(model, glm::radians(cube->rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            cube->Draw();
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
