//
// Created by filip on 7/15/24.
//

#include "../h/VAO.h"
#include "../h/VBLayout.h"

VAO::VAO() {
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VAO::~VAO() {
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VAO::AddState(const VBO &vb, const VBLayout &layout) {

    Bind();
    vb.Bind();  // Binds the VB.

    // Sets the layout.
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
        offset += element.count * VBElem::GetSizeOfType(element.type);
    }

}

void VAO::Bind() const {
    GLCall(glBindVertexArray(m_RendererID));
}

void VAO::Unbind() const {
    GLCall(glBindVertexArray(0));
}
