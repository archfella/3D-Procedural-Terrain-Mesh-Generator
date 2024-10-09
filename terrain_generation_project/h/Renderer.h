#ifndef RENDERER_H
#define RENDERER_H

#include <csignal>
#include "../glad/glad.h"  // Include glad first to handle all OpenGL function loading
#include "VAO.h"
#include "EBO.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogcall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogcall(const char* function, const char* file, int line);

class Renderable;

class Renderer {
public:
    void Clear() const;
    void Draw(const VAO& va, const EBO& ib, const Shader& shader) const;
    void DrawPoints(VAO& va, unsigned int count) const;
    void DrawRenderable(const Renderable& renderable) const;
    void TBODraw(const VAO& va, const EBO& ib, const Shader& shader) const;
    void setBackgroundColor(float r, float g, float b, float alpha);
};

#endif // RENDERER_H
