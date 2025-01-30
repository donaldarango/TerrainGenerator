#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float movementSpeed)
    : position(position), worldUp(up), yaw(yaw), pitch(pitch),
      movementSpeed(movementSpeed), mouseSensitivity(.3f) {
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboardInput(KEYBOARD_INPUT input, float deltaTime) {
    float velocity = movementSpeed * deltaTime;

    if (input == KEYBOARD_INPUT::FORWARD) 
        position += front * velocity;
    if (input == KEYBOARD_INPUT::BACKWARD) 
        position -= front * velocity;
    if (input == KEYBOARD_INPUT::LEFT) 
        position -= right * velocity;
    if (input == KEYBOARD_INPUT::RIGHT)
        position += right * velocity;
}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
