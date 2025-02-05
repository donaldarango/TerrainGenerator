#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <glad/glad.h>
#include <texture.h>
#include <map>
#include <string>

class TextureManager {
public:
    TextureManager();
    ~TextureManager();
    void AddTexture(const char* filename, const char* label);
private:
    std::map<std::string, Texture*> textures;
    int textureCount = 0;
};

#endif