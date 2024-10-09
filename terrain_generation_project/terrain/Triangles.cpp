//
// Created by filip on 8/13/24.
//

#include "Triangles.h"
#include "BaseTerrain.h"

Triangles::Triangles() {

}

void Triangles::Vertex3::InitVertex(BaseTerrain *terrain, float x, float z) {
    float y = terrain->GetHeight(x, z);

    float worldScale = terrain->GetWorldScale();
    position = glm::vec3(x*worldScale, y, z*worldScale);

    float size = terrain->GetSize();
    float textureScale = terrain->GetTextureScale();

    texCoords = glm::vec2(textureScale * x / size, textureScale * z / size);  //  UV coordinates
    normal = glm::vec3(0, 0, 0);
}

void Triangles::InitTriangles(int width, int depth, BaseTerrain *terrain) {
    m_width = width;
    m_depth = depth;

    CreateGLContext(terrain);
}

void Triangles::CreateGLContext(BaseTerrain* terrain) {
    std::vector<Vertex3> vertices;
    vertices.resize(m_width * m_depth);

    int ind = 0;

    //  init vertices
    for(int z = 0; z < m_depth; z++) {
        for(int x = 0; x < m_width; x++) {
            if(ind < vertices.size()) {
                vertices[ind].InitVertex(terrain, x, z);
                ind++;
            }
            else {
                std::cout << "Error: vertices overflow!" << std::endl;
            }
        }
    }   //  fill the vertices vector


    //generate indices for ebo
    std::vector<unsigned int> indices;
    unsigned int NumQuads = (m_width - 1) * (m_depth - 1);
    indices.resize(NumQuads * 6);
    InitIndices(indices);


    //calculate normals
    for(int i = 0; i < indices.size(); i+=3) {
        unsigned int index0 = indices[i];
        unsigned int index1 = indices[i+1];
        unsigned int index2 = indices[i+2];
        glm::vec3 vector1 = vertices[index1].position - vertices[index0].position;
        glm::vec3 vector2 = vertices[index2].position - vertices[index0].position;
        glm::vec3 normal = normalize(cross(vector1, vector2));

        vertices[index0].normal = normal;
       vertices[index1].normal = normal;
       vertices[index2].normal = normal;
    }


    //populate buffers, create OpenGL state
    vao = new VAO();
    vao->Bind();
    ebo = new EBO(indices.data(), indices.size());
    vbo = new VBO(vertices.data(), vertices.size()*sizeof(vertices[0]));
    layout = new VBLayout();
    layout->Push<float>(3); //  position
    layout->Push<float>(2); //  texCoords
    layout->Push<float>(3); //  triangle normals
    vao->AddState(*vbo, *layout);
    vao->Unbind();
}



void Triangles::InitIndices(std::vector<unsigned int> &indices) {
    int ind = 0;
    for(int z = 0; z < m_depth - 1; z++) {
        for(int x = 0; x < m_width - 1; x++) {
            unsigned int bottomLeft = z * m_width + x;
            unsigned int topLeft = (z + 1) * m_width + x;
            unsigned int topRight = (z + 1) * m_width + x + 1;
            unsigned int bottomRight = z * m_width + x + 1;

            //  top left triangle
            indices[ind++] = bottomLeft;
            indices[ind++] = topLeft;
            indices[ind++] = topRight;

            //  bottom right triangle
            indices[ind++] = bottomLeft;
            indices[ind++] = topRight;
            indices[ind++] = bottomRight;
        }
    }
}


void Triangles::Render() {
    vao->Bind();
    GLCall(glDrawElements(GL_TRIANGLES, (m_depth - 1)*(m_width - 1)*6, GL_UNSIGNED_INT, NULL));
    vao->Unbind();
}

