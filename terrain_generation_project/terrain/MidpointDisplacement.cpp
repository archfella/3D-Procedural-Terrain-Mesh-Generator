//
// Created by filip on 8/21/24.
//

#include "MidpointDisplacement.h"

#include <random>


MidpointDisplacement::MidpointDisplacement() {
}

void MidpointDisplacement::CreateMidpointdDisplacement(int terrainSize, float roughness, float minHeight, float maxHeight, Shader& shader) {
    if(roughness < 0.0f) {
        std::cout << "roughness must be a positive float" << std::endl;
        exit(-1);
    }

    m_terrainSize = terrainSize;
    m_minHeight = minHeight;
    m_maxHeight = maxHeight;

    m_heightmap.InitArray2D(terrainSize, terrainSize, 0.0f);

    CreateMidPointdDisplacementInternal(roughness);

    m_heightmap.Normalize(minHeight, maxHeight);

    m_triangles.InitTriangles(m_terrainSize, m_terrainSize, this);

    InitShader(shader, minHeight, maxHeight);

}



void MidpointDisplacement::CreateMidPointdDisplacementInternal(float roughness) {
    int rectSz = CalcNextPow2(m_terrainSize);
    float currHeight  = (float)rectSz / 2.0f;
    float heightReduce = pow(2.0f, -roughness);

    while(rectSz > 0) {
        DiamondStep(rectSz, currHeight);

        SquareStep(rectSz, currHeight);

        rectSz /= 2;
        currHeight *= heightReduce;
    }
}

void MidpointDisplacement::DiamondStep(int rectangleSize, float currentHeight) {
    int halfRectSz = rectangleSize / 2;

    for(int y = 0; y < m_terrainSize; y += rectangleSize) {
        for(int x = 0; x < m_terrainSize; x += rectangleSize) {
            int nextX = (x + rectangleSize) % m_terrainSize;
            int nextY = (y + rectangleSize) % m_terrainSize;

            if(nextX < x)
                nextX = m_terrainSize - 1;

            if(nextY < y)
                nextY = m_terrainSize - 1;

            float topLeft = m_heightmap.Get(x, y);
            float topRight = m_heightmap.Get(nextX, y);
            float bottomLeft = m_heightmap.Get(x, nextY);
            float bottomRight = m_heightmap.Get(nextX , nextY);

            int midX = (x + halfRectSz) % m_terrainSize;
            int midY = (y + halfRectSz) % m_terrainSize;

            float randVal = RandFloat(currentHeight, -currentHeight);
            float midPoint = (topLeft + topRight + bottomLeft + bottomRight) / 4.0f;

            m_heightmap.Set(midX, midY, midPoint + randVal);
        }
    }
}

void MidpointDisplacement::SquareStep(int rectangleSize, float currentHeight) {
    int halfRectSz = rectangleSize / 2;

    for(int y = 0; y < m_terrainSize; y += rectangleSize) {
        for(int x = 0; x < m_terrainSize; x += rectangleSize) {
            int nextX = (x + rectangleSize) % m_terrainSize;
            int nextY = (y + rectangleSize) % m_terrainSize;

            int midX = (x + halfRectSz) % m_terrainSize;
            int midY = (y + halfRectSz) % m_terrainSize;

            int prevMidX = (x - halfRectSz + m_terrainSize) % m_terrainSize;
            int prevMidY = (y - halfRectSz + m_terrainSize) % m_terrainSize;

            float currTopLeft = m_heightmap.Get(x, y);
            float currTopRight = m_heightmap.Get(nextX, y);
            float currBottomLeft = m_heightmap.Get(x, nextY);
            float currCenter = m_heightmap.Get(midX, midY);
            float prevYCenter = m_heightmap.Get(midX, prevMidY);
            float prevXCenter = m_heightmap.Get(prevMidX, midY);

            float currLeftMid = (currTopLeft + currCenter + currBottomLeft + prevXCenter)/4.0f + RandFloat(-currentHeight, currentHeight);
            float currTopMid = (currTopLeft + currCenter + currTopRight + prevYCenter)/4.0f + RandFloat(-currentHeight, currentHeight);

            m_heightmap.Set(midX, y, currTopMid);
            m_heightmap.Set(x, midY, currLeftMid);
        }
    }
}

int MidpointDisplacement::CalcNextPow2(int x) {
    int res = 1;
    while(res <= x) {
        res *= 2;
    }

    return res;
}



float MidpointDisplacement::RandFloat(float low, float high) {
    std::random_device rd;  //  seed generator
    std::mt19937 gen(rd()); //  Mersenn Twister engine
    std::uniform_real_distribution<float> dist(low, high);

    float randFloat = dist(gen);

    return randFloat;
}

void MidpointDisplacement::InitShader(Shader &shader, float MinHeight, float MaxHeight) {
    shader.SetUniform1f("maxHeight", MaxHeight);
    shader.SetUniform1f("minHeight", MinHeight);
}


