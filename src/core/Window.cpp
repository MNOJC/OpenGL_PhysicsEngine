//
// Created by natha on 05/09/2025.
//

#include "Window.h"

Window::Window(int width, int height, const std::string &title) : m_width(width), m_height(height), m_title(title), m_window(nullptr)
{
    std::cout << "Creating window " << width << "x" << height << std::endl;
}

Window::~Window()
{
    if (m_window)
    {
        std::cout << "Destroying window" << std::endl;
        glfwDestroyWindow(m_window);
    }

    glfwTerminate();
}

bool Window::Initialize()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    std::cout << "Window successfully initialized" << std::endl;
    return true;
    
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void Window::SetShouldClose(const bool value) const
{
    glfwSetWindowShouldClose(m_window, value);
}
