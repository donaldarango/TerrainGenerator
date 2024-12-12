#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

// Constructor
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, unsigned int scrWidth, unsigned int scrHeight)
    : position(position), worldUp(up), yaw(yaw), pitch(pitch),
      movementSpeed(2.5f), mouseSensitivity(0.1f) {
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    lastX = scrWidth / 2.0f;
    lastY = scrHeight / 2.0f;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::keyboardCallback(GLFWwindow* window, float deltaTime) {
        float velocity = movementSpeed * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // Forward
            position += front * velocity;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // Backward
            position -= front * velocity;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // Left
            position -= right * velocity;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // Right
            position += right * velocity;
    }

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    // Recalculate right and up vectors
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
