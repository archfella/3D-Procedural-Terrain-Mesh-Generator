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
    vb.Bind();  //binds the VB

    //sets the layout
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
        //1.) location = i
        //2.) vecCount
        //3.) vec data type
        //4.) GL_FALSE/GL_TRUE
        //5.) stride (sizeof(vertex_data))
        //6.) pointer to where the position data begins in the buffer (0 is the beginning of the buffer)
        offset += element.count * VBElem::GetSizeOfType(element.type);
    }

}

void VAO::Bind() const {
    GLCall(glBindVertexArray(m_RendererID));
}

void VAO::Unbind() const {
    GLCall(glBindVertexArray(0));
}
