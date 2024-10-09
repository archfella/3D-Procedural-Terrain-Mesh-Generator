//
// Created by filip on 7/15/24.
//

#include "../h/VBO.h"
#include "../h/Renderer.h"

VBO::VBO(){}

VBO::VBO(const void *data, unsigned int size) {
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VBO::~VBO() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VBO::Bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VBO::Unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
