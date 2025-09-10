//
// Created by natha on 05/09/2025.
//

#include "Camera.h"
#include <iostream>

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_movementSpeed(SPEED), m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM)
{
    m_position = position;
    m_worldUp = up;
    m_yaw = yaw;
    m_pitch = pitch;
    
    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) const
{
    return glm::perspective(glm::radians(m_zoom), aspectRatio, 0.1f, 100.0f);
}

void Camera::SetTarget(glm::vec3 position)
{
    glm::vec3 direction = glm::normalize(m_position - position);
    UpdateYawPitchFromDirection(direction);
    m_position = position - direction * 3.0f;
    UpdateCameraVectors();
}

void Camera::ProcessKeyboard(int direction, float deltaTime)
{
    float velocity = m_movementSpeed * deltaTime;
    
    if (direction == 0)
        m_position += m_front * velocity;
    if (direction == 1)
        m_position -= m_front * velocity;
    if (direction == 2)
        m_position -= m_right * velocity;
    if (direction == 3)
        m_position += m_right * velocity;
    if (direction == 4)
        m_position -= m_up * velocity;
    if (direction == 5)
        m_position += m_up * velocity;
    
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (constrainPitch)
    {
        if (m_pitch > 89)
            m_pitch = 89;
        if (m_pitch < -89)
            m_pitch = -89;
    }

    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    m_zoom -= yoffset;
    if (m_zoom < 1.0f)
        m_zoom = 1.0f;
    if (m_zoom > 45.0f)
        m_zoom = 45.0f;


}

void Camera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
    
}

void Camera::UpdateYawPitchFromDirection(const glm::vec3& direction)
{
    m_yaw = glm::degrees(atan2(direction.z, direction.x));
    m_pitch = glm::degrees(asin(direction.y));
    
    if (m_yaw < 0) m_yaw += 360.0f;
    if (m_yaw >= 360.0f) m_yaw -= 360.0f;
    m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);
}