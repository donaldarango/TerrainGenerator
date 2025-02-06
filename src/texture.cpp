#include "texture.h"
#include <iostream>

Texture::Texture(const char* filename) {
    this->filename = filename;
}

Texture::~Texture() {
    glDeleteTextures(1, &textureHandle);
}

void Texture::setTextureHandle(GLuint handle) {
    textureHandle = handle;
}