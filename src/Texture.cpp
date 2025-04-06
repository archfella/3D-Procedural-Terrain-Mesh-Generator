//
// Created by filip on 7/18/24.

#include <GL/glew.h>

#include "../h/Texture.h"
#include "../h/Assertion.h"
#include "../vendor/stb_image/stb_image.h"


Texture::Texture() {}

Texture::Texture(const std::string &filepath) : m_RendererID(0), m_FilePath(filepath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0) {

    stbi_set_flip_vertically_on_load(1); // Flips the texture upside-down (openGL expects texture pixels to start from bottom-left).
    m_LocalBuffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4); // Texture data.

    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

    // Texture filtering parameters.
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if(m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}

Texture::~Texture() {
    GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));  // Specify the texture slot.
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}


void Texture::Unbind() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

unsigned int Texture::TextureFromFile(const char *path, const std::string &directory) {

    std::string filepath = std::string(path);
    filepath = directory + '/' + filepath;

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(1); //Flips the texture upside-down (openGL expects texture pixels to start from bottom-left).
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrComponents, 4); //Texture data.

    unsigned int textureID;
    GLCall(glGenTextures(1, &textureID));
    GLCall(glBindTexture(GL_TEXTURE_2D, textureID));

    //texture filtering parameters
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if(data)
        stbi_image_free(data);

    return textureID;
}

