#ifndef CUBE_H
#define CUBE_H

#include <glad/glad.h>
#include "camera.h"

class Cube {
public:
    Cube();
    ~Cube();

    void draw(Camera cam);

private:
    unsigned int VAO, VBO;
};

#endif
