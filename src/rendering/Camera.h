//
// Created by natha on 05/09/2025.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = 0.0f, float pitch = 0.0f);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float aspectRatio) const;

    void SetTarget(glm::vec3 position);
    void UpdateYawPitchFromDirection(const glm::vec3& direction);


    void ProcessKeyboard(int direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

    glm::vec3 GetPosition() const { return m_position; };
    glm::vec3 GetFront() const { return m_front; };
    float GetZoom() const { return m_zoom; };

    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_zoom;

private:
    
    void UpdateCameraVectors();
    
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    float m_yaw;
    float m_pitch;
    
};


