cmake_minimum_required(VERSION 3.30)
project(OpenGL_PhysicsEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(OpenGL_PhysicsEngine main.cpp
        src/rendering/Mesh.cpp
        src/rendering/Mesh.h
        src/entities/CubeMesh.cpp
        src/entities/CubeMesh.h
        src/entities/Platform.cpp
        src/entities/Platform.h
        src/core/Application.cpp
        src/core/Application.h
        src/core/Window.cpp
        src/core/Window.h
        src/core/Time.cpp
        src/core/Time.h
        src/rendering/Shader.cpp
        src/rendering/Shader.h
        src/rendering/Camera.cpp
        src/rendering/Camera.h
        src/rendering/Renderer.cpp
        src/rendering/Renderer.h
        src/ui/GUI.cpp
        src/ui/GUI.h
        src/entities/GameObject.cpp
        src/entities/GameObject.h)

find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)


add_subdirectory(lib/imgui)


target_link_libraries(OpenGL_PhysicsEngine
        glfw 
        OpenGL32
        GLEW::GLEW
        imgui
)

target_include_directories(OpenGL_PhysicsEngine PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends
)

foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(SHADER_NAME ${SHADER_FILE} NAME)
    configure_file(${SHADER_FILE} ${CMAKE_BINARY_DIR}/shaders/${SHADER_NAME} COPYONLY)
endforeach()