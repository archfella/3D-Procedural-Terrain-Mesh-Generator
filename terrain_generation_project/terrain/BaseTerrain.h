// Original code copyright (C) 2022 Etay Meiri
// Modified by Filip Radovic in 2024
// Licensed under the GNU General Public License v3
// See LICENSE file in the project root for details.

#ifndef BASETERRAIN_H
#define BASETERRAIN_H

#include "../utils/Array2D.h"
#include "../utils/utils.h"
#include "Triangles.h"
#include "../h/Texture.h"

class BaseTerrain {
public:
    BaseTerrain();

    void InitTerrain(int worldScale, int textureScale);
    virtual void Render(Shader& shader);
    void LoadFromFile(const char* filename);
    float GetHeight(int x, int z) const { return m_heightmap.Get(x, z);}
    int GetWorldScale() const;
    int GetTextureScale() const;
    int GetSize() const {return  m_terrainSize;}
    float GetHeightInterpolated(float x, float z) const;
    void InitTerrain(float WorldScale, float TextureScale, std::vector<std::string>& TextureFilenames);
protected:
    void LoadHeightMap(const char* filename);

    int m_worldScale;
    int m_textureScale;
    int m_terrainSize;
    std::vector<std::string> m_TextureFilenames;
    Array2D<float> m_heightmap;
    Triangles m_triangles;
    std::vector<Texture*> m_textures;
};

#endif // BASETERRAIN_H
