#include "renderer.h"
#include <glad/glad.h>
#include "cube.h"

void render() {
    // Clear the screen with a color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rendering logic can be added here in the future
}
