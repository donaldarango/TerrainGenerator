#include "glad_loader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

bool initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return false;
    }
    return true;
}
