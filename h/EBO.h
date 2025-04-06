//
// Created by filip on 7/15/24.
//

#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

class EBO {
public:
    EBO();
    EBO(const unsigned int* data, unsigned int count);  //32-bit indicies
    ~EBO();

    void Bind() const;
    void Unbind() const;
    void SetData(const unsigned int* data, unsigned int count);

    inline unsigned int getCount() const {
        return m_Count;
    }

private:
    unsigned int m_RendererID;
    unsigned int m_Count;

};



#endif //INDEXBUFFER_H
