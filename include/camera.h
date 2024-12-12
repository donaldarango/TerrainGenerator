#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, unsigned int scrWidth, unsigned int scrHeight);

    glm::mat4 getViewMatrix();


    void processMouseMovement(GLFWwindow* window, float xOffset, float yOffset, bool constrainPitch = true);
    void keyboardCallback(GLFWwindow* window, float deltaTime);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

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
    float lastX, lastY;
    
    bool firstMouse = true;

private:
    void updateCameraVectors();

};

#endif // CAMERA_H
