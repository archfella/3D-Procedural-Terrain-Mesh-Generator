//
// Created by Filip Radovic on 4.4.25..
//

#include <GL/glew.h>
#include <iostream>

#include "../h/Assertion.h"

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