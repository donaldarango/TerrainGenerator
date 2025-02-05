#include "texture.h"
#include <iostream>

Texture::Texture(const char* filename) {
    this->filename = filename;
}

Texture::~Texture() {
    glDeleteTextures(1, &textureHandle);
    std::cout << "Deleted texture " << filename << std::endl;
}

GLuint Texture::getTextureHandle() {
    return textureHandle;
}

void Texture::setTextureHandle(GLuint handle) {
    textureHandle = handle;
}