#include <GL/glew.h>       
#include <GLFW/glfw3.h>  
#include <iostream>
#include "src/core/Application.h"

int main()
{
    std::cout << "=== Program start ===" << std::endl;

    Application app;
    app.Run();

    std::cout << "=== Program end ===" << std::endl;
    return EXIT_SUCCESS;
}