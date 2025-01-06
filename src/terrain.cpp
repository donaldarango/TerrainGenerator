#include "terrain.h"
#include "stb_image/stb_image.h"
#include <iostream>

// Code adapted from: https://learnopengl.com/Guest-Articles/2021/Tessellation/Height-map

void TerrainLoader::LoadFromFile(const char* filename) {
    heightmap = stbi_load(filename, &width, &height, &nChannels, 0);
    if (heightmap==NULL) {
        std::cout << "Failed to load heightmap image" << std::endl;
        exit(1);
    }   

    std::cout << "Heightmap loaded with: Width: " << width << " Height: " << height << " Channels: " << nChannels << std::endl;
}

void TerrainLoader::InitTerrain() {
    float yScale = 64.0f / 256.0f, yShift = 16.0f;  // apply a scale+shift to the height data
    for(unsigned int i = 0; i < height; i++)
    {
        for(unsigned int j = 0; j < width; j++)
        {
            // retrieve texel for (i,j) tex coord
            unsigned char* texel = heightmap + (j + width * i) * nChannels;
            // raw height at coordinate
            unsigned char y = texel[0];

            // vertex
            vertices.push_back( -height/2.0f + i);        // v.x
            vertices.push_back( (int)y * yScale - yShift); // v.y
            vertices.push_back( -width/2.0f + j);        // v.z
            vertices.push_back( (float)j / width);        // v.u
            vertices.push_back( (float)i / height);       // v.v
        }
    }

    stbi_image_free(heightmap);

    // index generation
    for(unsigned int i = 0; i < height-1; i++)       // for each row a.k.a. each strip
    {
        for(unsigned int j = 0; j < width; j++)      // for each column
        {
            for(unsigned int k = 0; k < 2; k++)      // for each side of the strip
            {
                indices.push_back(j + width * (i + k));
            }
        }
    }
}

void TerrainLoader::Render(Camera& camera) {
    int numStrips = height - 1;
    int numVerticesPerStrip = width * 2; 

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // register VAO
    GLuint terrainVAO, terrainVBO, terrainEBO;
    glGenVertexArrays(1, &terrainVAO);
    glBindVertexArray(terrainVAO);

    glGenBuffers(1, &terrainVBO);
    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
    glBufferData(GL_ARRAY_BUFFER,
                vertices.size() * sizeof(float),       // size of vertices buffer
                &vertices[0],                          // pointer to first element
                GL_STATIC_DRAW);

    int POS_LOC = 0;
    int TEX_LOC = 1;
    int stride = 5 * sizeof(float); // 3 for position + 2 for texture coordinates

    // position attribute
    glVertexAttribPointer(POS_LOC, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(POS_LOC);

    // texture attribute
    glVertexAttribPointer(TEX_LOC, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(TEX_LOC);

    glGenBuffers(1, &terrainEBO);   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                indices.size() * sizeof(unsigned int), // size of indices buffer
                &indices[0],                           // pointer to first element
                GL_STATIC_DRAW);

    // draw mesh
    glBindVertexArray(terrainVAO);
    // render the mesh triangle strip by triangle strip - each row at a time
    for(unsigned int strip = 0; strip < numStrips; ++strip)
    {
        glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
                    numVerticesPerStrip, // number of indices to render
                    GL_UNSIGNED_INT,     // index data type
                    (void*)(strip * numVerticesPerStrip * sizeof(unsigned int)));
    }
}