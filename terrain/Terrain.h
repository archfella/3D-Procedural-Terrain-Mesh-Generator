// Original code copyright (C) 2022 Etay Meiri
// Modified by Filip Radovic in 2024
// Licensed under the GNU General Public License v3
// See LICENSE file in the project root for details.

#ifndef TERRAIN_H
#define TERRAIN_H

#include "../utils/Array2D.h"
#include "../utils/utils.h"
#include "../h/Texture.h"

class Triangles;
class Shader;

class Terrain {
public:
    // Loads a terrain heightmap from file.
    void LoadFromFile(const char* filename);

    // Setter.
    void InitTerrain(int worldScale, int textureScale);

    // Sets the biome-specific attributes.
    enum struct BiomeType {ALPS, ROCKY, FLAT, DESERT, TUNDRA};
    void InitBiome(BiomeType type);

    // Getters.
    float GetHeight(int x, int z) const;
    int GetWorldScale() const;
    int GetTextureScale() const;
    int GetSize() const;
    float GetHeightInterpolated(float x, float z) const;
    static Terrain* GetInstance();

    // Renders the terrain.
    void Render(Shader& shader);

private:

    /* Base terrain attributes. */
    Terrain();
    void LoadHeightMap(const char* filename);

    static Terrain* instance;
    int m_worldScale;
    int m_textureScale;
    int m_terrainSize;
    std::vector<std::string> m_TextureFilenames;
    Array2D<float> m_heightmap;
    Triangles* m_triangles;
    std::vector<Texture*> m_textures;

    void InitTerrain(float WorldScale, float TextureScale, std::vector<std::string>& TextureFilenames);

    /* Midpoint Displacement Technique. */

    void CreateMidpointDisplacement(int terrainSize, float roughness, float minHeight, float maxHeight, Shader& shader);
    void SquareStep(int rectangleSize, float currentHeight);
    void DiamondStep(int rectangleSize, float currentHeight);
    float RandFloat(float low, float high);
    void CreateMidPointDisplacementInternal(float roughness);
    void InitShader(Shader& shader, float MinHeight, float MaxHeight);
    int CalcNextPow2(int x);

    float m_minHeight;
    float m_maxHeight;

};

#endif // TERRAIN_H
