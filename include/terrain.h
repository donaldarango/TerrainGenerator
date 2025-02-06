#ifndef TERRAIN_H
#define TERRAIN_H

#include <glad/glad.h>
#include "camera.h"
#include <vector>


class TerrainLoader {
    public:
        void LoadFromFile(const char* filename);
        void InitTerrain();
        void Render(Camera& camera);
        float getMaxHeight() { return maxHeight; }
        float getMinHeight() { return minHeight; }
    
    protected:
        int width, height, nChannels;
        int terrainSize;
        unsigned char* heightmap;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        float maxHeight = 0.0f;
        float minHeight = INFINITY;
};

#endif