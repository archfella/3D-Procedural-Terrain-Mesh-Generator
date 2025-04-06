//
// Created by filip on 8/13/24.
//

#include <random>

#include "Terrain.h"
#include "../h/Shader.h"
#include "../terrain/Triangles.h"

Terrain* Terrain::instance = nullptr;

Terrain::Terrain() {
    m_triangles = new Triangles();
}

Terrain *Terrain::GetInstance() {
    if (!instance) {
        instance = new Terrain();
    }
    return instance;
}


void Terrain::InitTerrain(int worldScale, int textureScale) {
    m_worldScale = worldScale;
    m_textureScale = textureScale;
}

void Terrain::InitTerrain(float WorldScale, float TextureScale, std::vector<std::string> &TextureFilenames) {
    m_worldScale = WorldScale;
    m_textureScale = TextureScale;
    m_TextureFilenames = TextureFilenames;

    m_textures.clear();

    for(int i = 0; i < m_TextureFilenames.size(); i++) {
        Texture* tex = new Texture(m_TextureFilenames[i]);
        m_textures.push_back(tex);
    }
}

void Terrain::InitBiome(BiomeType type) {

    int terrainSize = 256;
    float roughness, minHeight, maxHeight, worldScale, textureScale;
    std::vector<std::string> textureFilenames;

    Shader* shader = Shader::GetGlobalShader();

    switch (type) {
        case BiomeType::ALPS:

            roughness = 1.0f;
            worldScale = 1.0f, textureScale = 4.0f;
            minHeight = 0.0f, maxHeight = 250.0f;

            textureFilenames.push_back("../resources/terrainTextures/alps/IMGP5525_seamless.jpg");
            textureFilenames.push_back("../resources/terrainTextures/alps/IMGP5487_seamless.jpg");
            textureFilenames.push_back("../resources/terrainTextures/alps/grass.png");
            textureFilenames.push_back("../resources/terrainTextures/alps/ice.jpg");

            this->InitTerrain(worldScale, textureScale, textureFilenames);
            this->CreateMidpointDisplacement(terrainSize, roughness, minHeight, maxHeight, *shader);

            break;
        case BiomeType::ROCKY:

            roughness = 1.0f;
            worldScale = 1.0f, textureScale = 4.0f;
            minHeight = 50.0f, maxHeight = 250.0f;

            textureFilenames.push_back("../resources/terrainTextures/rocky_mountains/IMGP5525_seamless.jpg");
            textureFilenames.push_back("../resources/terrainTextures/rocky_mountains/orangeRock.jpg");
            textureFilenames.push_back("../resources/terrainTextures/rocky_mountains/gravel.jpg");
            textureFilenames.push_back("../resources/terrainTextures/rocky_mountains/yellowRock.jpg");

            this->InitTerrain(worldScale, textureScale, textureFilenames);
            this->CreateMidpointDisplacement(terrainSize, roughness, minHeight, maxHeight, *shader);

            break;
        case BiomeType::FLAT:

            roughness = 1.0f;
            worldScale = 1.0f, textureScale = 4.0f;
            minHeight = 150.0f, maxHeight = 200.0f;

            textureFilenames.push_back("../resources/terrainTextures/flatlands/gravel.jpg");
            textureFilenames.push_back("../resources/terrainTextures/flatlands/dirt.jpg");
            textureFilenames.push_back("../resources/terrainTextures/flatlands/mudgrass.jpg");
            textureFilenames.push_back("../resources/terrainTextures/flatlands/grass.jpg");

            this->InitTerrain(worldScale, textureScale, textureFilenames);
            this->CreateMidpointDisplacement(terrainSize, roughness, minHeight, maxHeight, *shader);

            break;
        case BiomeType::DESERT:

            roughness = 1.0f;
            worldScale = 1.0f, textureScale = 4.0f;
            minHeight = 150.0f, maxHeight = 200.0f;

            textureFilenames.push_back("../resources/terrainTextures/desert/bumpyRock.jpg");
            textureFilenames.push_back("../resources/terrainTextures/desert/sandStone.jpg");
            textureFilenames.push_back("../resources/terrainTextures/desert/sandStone.jpg");
            textureFilenames.push_back("../resources/terrainTextures/desert/sand.jpg");

            this->InitTerrain(worldScale, textureScale, textureFilenames);
            this->CreateMidpointDisplacement(terrainSize, roughness, minHeight, maxHeight, *shader);

            break;
        case BiomeType::TUNDRA:

            roughness = 1.0f;
            worldScale = 1.0f, textureScale = 4.0f;
            minHeight = 75.0f, maxHeight = 200.0f;

            textureFilenames.push_back("../resources/terrainTextures/tundra/asphalt.jpg");
            textureFilenames.push_back("../resources/terrainTextures/tundra/moss.jpg");
            textureFilenames.push_back("../resources/terrainTextures/tundra/snow.jpg");
            textureFilenames.push_back("../resources/terrainTextures/tundra/ice.jpg");

            this->InitTerrain(worldScale, textureScale, textureFilenames);
            this->CreateMidpointDisplacement(terrainSize, roughness, minHeight, maxHeight, *shader);

            break;

        default:

            std::cerr << "Unknown biome type" << std::endl;
            break;

    }
}



void Terrain::LoadHeightMap(const char *filename) {

    m_worldScale = 10.0f;

    int filesize = 0;
    unsigned char* dataPointer = (unsigned char*)ReadFile(filename, filesize);

    if(filesize % sizeof(float) != 0) {
        std::cout << "Error: file must contain a whole number of floating points!\n" << std::endl;
        exit(-3);
    }

    /* There are [a^2 = filesize/sizeof(float)] heightpoints in a heightmap.
     * 'm_terrainSize' is essentially one side of a heightmap square.*/
    m_terrainSize = sqrt(filesize / sizeof(float));

    // Initializes a heightmap data buffer.
    m_heightmap.InitArray2D(m_terrainSize, m_terrainSize, dataPointer);

    // Print the contents of the heightmap.
    m_heightmap.PrintFloat();

}

void Terrain::LoadFromFile(const char *filename) {

    LoadHeightMap(filename);

    // Initializes all the triangle coordinates, ready for rendering.
    m_triangles->InitTriangles(m_terrainSize, m_terrainSize, this);

}

int Terrain::GetWorldScale() const {
    return m_worldScale;
}

int Terrain::GetTextureScale() const {
    return m_textureScale;
}

void Terrain::Render(Shader& shader) {
    for(int i = 0; i < m_textures.size(); i++) {
        if(m_textures[i])
            m_textures[i]->Bind(i);
        shader.SetUniform1i(("gTextureHeight" + std::to_string(i)).c_str(), i);
    }
    m_triangles->Render();
}

float Terrain::GetHeight(int x, int z) const {
    return m_heightmap.Get(x, z);
}

int Terrain::GetSize() const {
    return  m_terrainSize;
}


float Terrain::GetHeightInterpolated(float x, float z) const {
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


/* MidpointDisplacement */

float Terrain::RandFloat(float low, float high) {
    std::random_device rd;  //  seed generator
    std::mt19937 gen(rd()); //  Mersenn Twister engine
    std::uniform_real_distribution<float> dist(low, high);

    float randFloat = dist(gen);

    return randFloat;
}

int Terrain::CalcNextPow2(int x) {
    /* This is used in every case (is essential when Terrain Size is not a power of 2). */
    int res = 1;
    while(res <= x) {
        res *= 2;
    }

    return res;
}

void Terrain::DiamondStep(int rectangleSize, float currentHeight) {

    /* For each 'rectangleSize', we displace the center of the rectangle by a random displacement in range of 'currentHeight'.
     * Note that for each Quadrant (in the first iteration we have 4 Quadrants), only one corner is raised - other 3 corners
     * remain the same height. The result when doing only the Diamond step is unrealistic (assume the base height is 0).
     * That is the reason why we must execute the 'Square Step'. */

    int halfRectSz = rectangleSize / 2;

    for(int y = 0; y < m_terrainSize; y += rectangleSize) {

        for(int x = 0; x < m_terrainSize; x += rectangleSize) {

            int nextX = (x + rectangleSize) % m_terrainSize;
            int nextY = (y + rectangleSize) % m_terrainSize;

            if(nextX < x)
                nextX = m_terrainSize - 1;

            if(nextY < y)
                nextY = m_terrainSize - 1;

            // Rectangle vertices.
            float topLeft = m_heightmap.Get(x, y);
            float topRight = m_heightmap.Get(nextX, y);
            float bottomLeft = m_heightmap.Get(x, nextY);
            float bottomRight = m_heightmap.Get(nextX , nextY);

            // Center of the rectangle.
            int midX = (x + halfRectSz) % m_terrainSize;
            int midY = (y + halfRectSz) % m_terrainSize;

            // We displace the middle of the rectangle by a random value.
            float randVal = RandFloat(currentHeight, -currentHeight);
            float midPoint = (topLeft + topRight + bottomLeft + bottomRight) / 4.0f;
            m_heightmap.Set(midX, midY, midPoint + randVal);

        }

    }

}


void Terrain::SquareStep(int rectangleSize, float currentHeight) {
    /* We calculate the  */
    int halfRectSz = rectangleSize / 2;

    for(int y = 0; y < m_terrainSize; y += rectangleSize) {
        for(int x = 0; x < m_terrainSize; x += rectangleSize) {

            int nextX = (x + rectangleSize) % m_terrainSize;
            int nextY = (y + rectangleSize) % m_terrainSize;

            int midX = (x + halfRectSz) % m_terrainSize;
            int midY = (y + halfRectSz) % m_terrainSize;

            int prevMidX = (x - halfRectSz + m_terrainSize) % m_terrainSize;
            int prevMidY = (y - halfRectSz + m_terrainSize) % m_terrainSize;

            // We extract heights from the 6 different locations:
                // curr - Current rectangle.
                // prevX - The rectangle to the left of the current rectangle.
                // prevY - The rectangle above the current rectangle.
                // (left, right, bottom, top) - vertices of the rectangle
                // center - center vertex of the rectangle
            float currTopLeft = m_heightmap.Get(x, y);
            float currTopRight = m_heightmap.Get(nextX, y);
            float currBottomLeft = m_heightmap.Get(x, nextY);
            float currCenter = m_heightmap.Get(midX, midY);
            float prevYCenter = m_heightmap.Get(midX, prevMidY);
            float prevXCenter = m_heightmap.Get(prevMidX, midY);

            /* We already displaced the 'currCenter' by a random value.
             * 'currLeftMid' and 'currTopMid' are the other two vertices of the sub-rectangle (in total we displaced 3 out of 4
             *  sub-rectangle vertices, the 4th vertex will be displaced via adjacent Square Step).
             *
             *  We now calculate their values by taking the average of the previously extracted heights and adding the
             *  random height displacement.
             *  By doing this, we achieve smoother and more realistic terrain (averaging), but also we are displacing all of the
             *  sub-rectangle vertices (in Diamond Step we were displacing only one).
             */
            float currLeftMid = (currTopLeft + currCenter + currBottomLeft + prevXCenter)/4.0f + RandFloat(-currentHeight, currentHeight);
            float currTopMid = (currTopLeft + currCenter + currTopRight + prevYCenter)/4.0f + RandFloat(-currentHeight, currentHeight);

            m_heightmap.Set(midX, y, currTopMid);
            m_heightmap.Set(x, midY, currLeftMid);

        }
    }
}


void Terrain::InitShader(Shader &shader, float MinHeight, float MaxHeight) {
    shader.SetUniform1f("maxHeight", MaxHeight);
    shader.SetUniform1f("minHeight", MinHeight);
}

void Terrain::CreateMidPointDisplacementInternal(float roughness) {
    int rectSz = CalcNextPow2(m_terrainSize);
    float currHeight  = (float)rectSz / 2.0f;
    float heightReduce = pow(2.0f, -roughness);

    // We do the 'DiamondStep' and 'SquareStep' recursively for each rectangle size.
    while(rectSz > 0) {
        DiamondStep(rectSz, currHeight);

        SquareStep(rectSz, currHeight);

        rectSz /= 2;
        currHeight *= heightReduce;
    }
}

void Terrain::CreateMidpointDisplacement(int terrainSize, float roughness, float minHeight, float maxHeight, Shader &shader) {

    m_terrainSize = terrainSize;
    m_minHeight = minHeight;
    m_maxHeight = maxHeight;

    m_heightmap.InitArray2D(terrainSize, terrainSize, 0.0f);

    CreateMidPointDisplacementInternal(roughness);

    m_heightmap.Normalize(minHeight, maxHeight);

    m_triangles->InitTriangles(m_terrainSize, m_terrainSize, this);

    InitShader(shader, minHeight, maxHeight);

}



