// Original code copyright (C) 2022 Etay Meiri
// Modified by Filip Radovic in 2024
// Licensed under the GNU General Public License v3
// See LICENSE file in the project root for details.

#ifndef MIDPOINTDDISPLACEMENT_H
#define MIDPOINTDDISPLACEMENT_H
#include "BaseTerrain.h"


class MidpointDisplacement : public BaseTerrain {
public:
    MidpointDisplacement();

    void CreateMidpointdDisplacement(int terrainSize, float roughness, float minHeight, float maxHeight, Shader& shader);

private:
    float m_minHeight;
    float m_maxHeight;

    void SetMaxHeight(float maxHeight);
    void SquareStep(int rectangleSize, float currentHeight);
    void DiamondStep(int rectangleSize, float currentHeight);
    float RandFloat(float low, float high);
    void CreateMidPointdDisplacementInternal(float roughness);
    void InitShader(Shader& shader, float MinHeight, float MaxHeight);
    int CalcNextPow2(int x);

    /* update parameter functions */

};



#endif //MIDPOINTDDISPLACEMENT_H
