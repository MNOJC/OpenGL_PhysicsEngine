cmake_minimum_required(VERSION 3.30)
project(OpenGL_PhysicsEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(OpenGL_PhysicsEngine main.cpp)

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