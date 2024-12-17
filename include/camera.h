#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum KEYBOARD_INPUT {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float movementSpeed = 2.5f);

    glm::mat4 getViewMatrix();

    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
    void processKeyboardInput(KEYBOARD_INPUT input, float deltaTime);

    // Camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Camera options
    float yaw; // Rotation around the y-axis
    float pitch; // Rotation around the x-axis
    float movementSpeed;
    float mouseSensitivity;

private:
    void updateCameraVectors();
};

#endif // CAMERA_H
