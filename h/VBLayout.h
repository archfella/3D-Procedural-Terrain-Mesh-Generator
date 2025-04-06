//
// Created by filip on 7/15/24.
//

// VBLayout.h
#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H

#include <GL/glew.h>
#include <vector>

#include "Assertion.h"

struct VBElem {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return sizeof(GLfloat);
            case GL_UNSIGNED_INT: return sizeof(GLuint);
            case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
        }
        ASSERT(false);
        return 0;
    }
};

class VBLayout {
public:
    VBLayout() : m_Stride(0) {}

    template<typename T>
    void Push(unsigned int count);

    inline const std::vector<VBElem>& GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const { return m_Stride; }

private:
    std::vector<VBElem> m_Elements;
    unsigned int m_Stride;
};

#endif //VERTEXBUFFERLAYOUT_H

