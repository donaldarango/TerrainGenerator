#include "glad_loader.h"
#include "shader.h"
#include "glfw_manager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "renderer.h"
#include "camera.h"
#include "cube.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow *window);
// static void mouseCallback(GLFWwindow *window, float xpos, float ypos);

int main() {
    // Initialize GLFW
    GLFWwindow* window = initGLFW(SCR_WIDTH, SCR_HEIGHT, "Terrain Generator");
    if (!window) return -1;

    // Initialize GLAD
    if (!initGLAD()) {
        terminateGLFW();
        return -1;
    }

    Shader shader("shaders/test.vs", "shaders/test.fs"); 
    shader.use();

    glm::vec3 position(0.0f, 0.0f, 3.0f);
    glm::vec3 up(0.0f, 1.0f, 0.0f);
    float yaw = -90.0f;
    float pitch = 0.0f;

    Camera camera(position, up, yaw, pitch, SCR_WIDTH, SCR_HEIGHT);
    float deltaTime = 0.0f, lastFrame = 0.0f;

    Cube cube; 

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    shader.setMat4("projection", projection);  

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Poll events
        glfwPollEvents();
        processInput(window);
        camera.keyboardCallback(window, deltaTime);
        // camera.processMouseMovement(window, 0, 0, true);

        // Render
        render();

        cube.draw(camera);

        glm::mat4 model = glm::mat4(1.0f);
        shader.setMat4("model", model);
        glm::mat4 view = camera.getViewMatrix();
        shader.setMat4("view", view);  

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Clean up and exit
    terminateGLFW();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// static void mouseCallback(GLFWwindow* window, double xpos, double ypos)
// {
//     if (firstMouse) 
//     {
//         lastX = xpos;
//         lastY = ypos;
//         firstMouse = false;
//     }
  
//     float xoffset = xpos - lastX;
//     float yoffset = lastY - ypos; 
//     lastX = xpos;
//     lastY = ypos;

//     float sensitivity = 0.1f;
//     xoffset *= sensitivity;
//     yoffset *= sensitivity;

//     yaw   += xoffset;
//     pitch += yoffset;

//     if(pitch > 89.0f)
//         pitch = 89.0f;
//     if(pitch < -89.0f)
//         pitch = -89.0f;

//     glm::vec3 direction;
//     direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//     direction.y = sin(glm::radians(pitch));
//     direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//     front = glm::normalize(direction);
// }  
