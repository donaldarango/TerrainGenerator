#ifndef TERRAIN_H
#define TERRAIN_H


class TerrainLoader {
    public:
        void LoadFromFile(const char* filename);
    
    protected:
        int terrainSize;
        float* heightmap;

};

#endif