//
// Created by filip on 8/13/24.
//

#include "BaseTerrain.h"

BaseTerrain::BaseTerrain() {
}

void BaseTerrain::InitTerrain(int worldScale, int textureScale) {
    m_worldScale = worldScale;
    m_textureScale = textureScale;
}

void BaseTerrain::InitTerrain(float WorldScale, float TextureScale, std::vector<std::string> &TextureFilenames) {
    m_worldScale = WorldScale;
    m_textureScale = TextureScale;
    m_TextureFilenames = TextureFilenames;

    m_textures.clear();

    for(int i = 0; i < m_TextureFilenames.size(); i++) {
        Texture* tex = new Texture(m_TextureFilenames[i]);
        m_textures.push_back(tex);
    }
}


void BaseTerrain::LoadHeightMap(const char *filename) {
    m_worldScale = 10.0f;
    int filesize = 0;
    unsigned char* p = (unsigned char*)ReadFile(filename, filesize);

    if(filesize % sizeof(float) != 0) {
        std::cout << "Error: file must contain a whole number of floating points!\n" << std::endl;
        exit(-3);
    }

    m_terrainSize = sqrt(filesize / sizeof(float));

    m_heightmap.InitArray2D(m_terrainSize, m_terrainSize, p);

    m_heightmap.PrintFloat();   //  print the contents of the heightmap

}

void BaseTerrain::LoadFromFile(const char *filename) {
    LoadHeightMap(filename);

    m_triangles.InitTriangles(m_terrainSize, m_terrainSize, this);
}

int BaseTerrain::GetWorldScale() const {
    return m_worldScale;
}

int BaseTerrain::GetTextureScale() const {
    return m_textureScale;
}

void BaseTerrain::Render(Shader& shader) {
    for(int i = 0; i < m_textures.size(); i++) {
        if(m_textures[i])
            m_textures[i]->Bind(i);
            shader.SetUniform1i(("gTextureHeight" + std::to_string(i)).c_str(), i);
    }
    m_triangles.Render();
}


float BaseTerrain::GetHeightInterpolated(float x, float z) const {
    float BaseHeight = GetHeight((int)x, (int)z);

    if (((int)x + 1 >= m_terrainSize) ||  ((int)z + 1 >= m_terrainSize)) {
        return BaseHeight;
    }

    float NextXHeight = GetHeight((int)x + 1, (int)z);

    float RatioX = x - floorf(x);

    float InterpolatedHeightX = (float)(NextXHeight - BaseHeight) * RatioX + (float)BaseHeight;

    float NextZHeight = GetHeight((int)x, (int)z + 1);

    float RatioZ = z - floorf(z);

    float InterpolatedHeightZ = (float)(NextZHeight - BaseHeight) * RatioZ + (float)BaseHeight;

    float FinalHeight = (InterpolatedHeightX + InterpolatedHeightZ) / 2.0f;

    return FinalHeight;
}



