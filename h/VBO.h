//
// Created by filip on 7/15/24.
//

#ifndef VBO_H
#define VBO_H

class VBO {
public:
    VBO();
    VBO(const void* data, unsigned int size);
    ~VBO();

    void Bind() const;
    void Unbind() const;
private:
    unsigned int m_RendererID;
};



#endif //VBO_H
