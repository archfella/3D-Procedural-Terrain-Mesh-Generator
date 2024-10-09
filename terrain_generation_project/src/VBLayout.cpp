//
// Created by filip on 7/15/24.
//

#include "../h/VBLayout.h"

template<>
void VBLayout::Push<float>(unsigned int count) {
    m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_Stride += count * VBElem::GetSizeOfType(GL_FLOAT);
}

template<>
void VBLayout::Push<unsigned int>(unsigned int count) {
    m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_Stride += count * VBElem::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VBLayout::Push<unsigned char>(unsigned int count) {
    m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_Stride += count * VBElem::GetSizeOfType(GL_UNSIGNED_BYTE);
}

