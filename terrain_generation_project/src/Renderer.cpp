//
// Created by filip on 7/15/24.
//

#include <iostream>
#include "../h/Renderer.h"

#include "../h/Renderable.h"

void GLClearError() {
    while(glGetError() != GL_NO_ERROR); //internal error flag is set
}

bool GLLogcall(const char* function, const char* file, int line) {
    while(GLenum error = glGetError()) {
        std::cout << "[OpenGL error] (" << error << "): " << function << " " << file << " : "<< line <<  std::endl;
        return false;
    }

    return true;
}

void Renderer::Draw(const VAO &va, const EBO &ib, const Shader &shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawPoints(VAO &va, unsigned int count) const {
    va.Bind();
    GLCall(glDrawArrays(GL_POINTS, 0, count));
    va.Unbind();
}

void Renderer::DrawRenderable(const Renderable& renderable) const {
    renderable.GetShader().Bind();
    renderable.GetVAO().Bind();
    renderable.GetEBO().Bind();
    GLCall(glDrawElements(GL_TRIANGLES, renderable.GetEBO().getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::TBODraw(const VAO &va, const EBO &ib, const Shader &shader) const {
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::setBackgroundColor(float r, float g, float b, float alpha) {
    GLCall(glClearColor(r, g, b, alpha));
}



