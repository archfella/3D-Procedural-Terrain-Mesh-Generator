//
// Created by filip on 7/18/24.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture {

public:

    Texture();
    Texture(const std::string& filepath);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
    static unsigned int TextureFromFile(const char* path, const std::string& directory);

private:

    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;   //Width, Height, Bits-Per-Pixel.

};
#endif //TEXTURE_H
