#include "texture_manager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include <iostream>

TextureManager::TextureManager() {
    
}

TextureManager::~TextureManager() {
    for (auto const& [key, val] : textures) {
        val->~Texture();
    }
}

// adapted from https://learnopengl.com/Getting-started/Textures
void TextureManager::AddTexture(const char* filename, const char* label) {
    Texture *texture = new Texture(filename);
    GLuint textureHandle;
    
    glGenTextures(1, &textureHandle);
    glActiveTexture(GL_TEXTURE0 + textureCount);
    glBindTexture(GL_TEXTURE_2D, textureHandle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
    
    std::cout << "Loading " << filename << std::endl;
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return;
    }

    std::cout << "Width: " << width << " Height: " << height << " Channels: " << nrChannels << std::endl;
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture data" << std::endl;
        exit(1);
    }
    stbi_image_free(data);

    std::cout << "Texture " << filename << " loaded successfully (" << textureCount << ")" << std::endl;
    
    texture->setTextureHandle(textureHandle);
    textures[label] = texture;
    textureCount++;

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
        exit(1);
    }
    
}