//
// Created by natha on 05/09/2025.
//

#pragma once

#include <GL/glew.h>  
#include <string>
#include <glm/glm.hpp>


class Shader {
public:

    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    ~Shader();

    void Use() const;

    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetMat4(const std::string& name, const glm::mat4& mat) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetVec4(const std::string& name, const glm::vec4& value) const;

    GLuint GetID() const { return m_id; }

private:
    
    GLuint m_id;

    std::string LoadShaderFile(const std::string& filePath) const;

    GLuint CompileShader(GLenum type, const std::string& source) const;

    void CheckCompileErrors(GLuint shader, const std::string& type) const;
};


