//
// Created by natha on 05/09/2025.
//

#pragma once


#include <GLFW/glfw3.h>
#include <string>    
#include <iostream> 


class Window {

public:
    
    Window(int width, int height, const std::string& title);
    
    ~Window();

    bool Initialize();

    void SwapBuffers();

    void PollEvents();

    bool ShouldClose() const;

    void SetShouldClose(bool value) const;

    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    GLFWwindow* GetWindow() const { return m_window; }

    
private:

    GLFWwindow* m_window;
    int m_width, m_height;
    std::string m_title;
    
};



