//
// Created by filip on 7/15/24.
//

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "VBO.h"

class VBLayout;

class VAO {
public:
    VAO();
    ~VAO();

    void AddState(const VBO &vb, const VBLayout &layout);

    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_RendererID;
};



#endif //VERTEXARRAY_H
