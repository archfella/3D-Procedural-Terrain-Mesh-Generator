//
// Created by filip on 8/21/24.
//

#ifndef STBIMAGE_H
#define STBIMAGE_H

#include "glm/vec3.hpp"


class STBImage {
public:
    STBImage() {}

    ~STBImage() {
        if (m_imageData) {
            Unload();
        }
    }

    void Load(const char* pFilename);

    void Unload();

    glm::vec3 GetColor(int x, int y) const;

    int m_width = 0;
    int m_height = 0;
    int m_bpp = 0;
    unsigned char* m_imageData = NULL;
};



#endif //STBIMAGE_H
