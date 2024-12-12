#ifndef GLFW_MANAGER_H
#define GLFW_MANAGER_H

#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* initGLFW(int width, int height, const char* title);
void terminateGLFW();

#endif