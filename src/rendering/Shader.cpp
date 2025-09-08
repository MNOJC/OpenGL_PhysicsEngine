//
// Created by natha on 05/09/2025.
//

#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    const std::string vertexCode= LoadShaderFile(vertexPath);
    const std::string fragmentCode= LoadShaderFile(fragmentPath);

    const GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode);
    const GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

    m_id = glCreateProgram();
    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);

    CheckCompileErrors(m_id, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    std::cout << "Shader created (ID : " << m_id << ")" << std::endl;
}

Shader::~Shader()
{
    glDeleteProgram(m_id);
    std::cout << "Shader deleted (ID : " << m_id << ")" << std::endl;
}

void Shader::Use() const
{
    glUseProgram(m_id);
}

std::string Shader::LoadShaderFile(const std::string& filePath) const
{
    std::ifstream file(filePath);
    
    if (!file.is_open())
    {
        std::cout << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }

    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
    
}

GLuint Shader::CompileShader(GLenum type, const std::string& source) const
{
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    CheckCompileErrors(shader, (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT");

    return shader;
}

void Shader::CheckCompileErrors(GLuint shader, const std::string& type) const
{
    GLint success;
    GLchar infoLog[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "Shader compilation error (" << type << "): " << infoLog << std::endl;
        }
    } else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "Shader linking error (" << type << "): " << infoLog << std::endl;
        }
    }
}

void Shader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    
}