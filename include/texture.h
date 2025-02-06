#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>

class Texture {
public:
    Texture(const char* filename);
    ~Texture();
    GLuint getTextureHandle() { return textureHandle; };
    void setTextureHandle(GLuint handle);
private:
    GLuint textureHandle;
    std::string filename;
};

#endif 