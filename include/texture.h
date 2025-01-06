#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture {
public:
    Texture(const char* filename);
    ~Texture();
    GLuint getTexture();
private:
    GLuint texture;
};

#endif 