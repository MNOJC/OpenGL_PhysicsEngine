cmake_minimum_required(VERSION 3.30)
project(OpenGLCubeRenderer)

set(CMAKE_CXX_STANDARD 20)

add_executable(OpenGLCubeRenderer main.cpp)

find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(OpenGLCubeRenderer glfw OpenGL32 GLEW::GLEW)
include_directories(${GLM_INCLUDE_DIRS})

foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(SHADER_NAME ${SHADER_FILE} NAME)
    configure_file(${SHADER_FILE} ${CMAKE_BINARY_DIR}/shaders/${SHADER_NAME} COPYONLY)
endforeach()
