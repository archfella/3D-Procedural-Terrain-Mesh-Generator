// Original code copyright (C) 2023 Etay Meiri
// Modified by Filip Radovic in 2024
// Licensed under the GNU General Public License v3
// See LICENSE file in the project root for details.

#ifndef TRIANGLES_H
#define TRIANGLES_H

class BaseTerrain;
#include "../h/VAO.h"
#include "../h/VBO.h"
#include "../h/EBO.h"
#include "../h/VBLayout.h"



class Triangles {
public:
    Triangles();

    void InitTriangles(int width, int depth, BaseTerrain* terrain);
    void Render();
private:
    struct Vertex3 {
        glm::vec3 position;
        glm::vec2 texCoords;
        glm::vec3 normal;
        void InitVertex(BaseTerrain* terrain, float x, float z);
    };
    void CreateGLContext(BaseTerrain* terrain);
    void InitIndices(std::vector<unsigned int>& indices);

    int m_width = 0;
    int m_depth = 0;
    VAO* vao;
    VBO* vbo;
    VBLayout* layout;
    EBO* ebo;
};

#endif // TRIANGLES_H
