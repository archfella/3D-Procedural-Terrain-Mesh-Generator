//
// Created by Filip Radovic on 4.4.25..
//

#ifndef ASSERTION_H
#define ASSERTION_H

#include <csignal>


#define ASSERT(x) if(!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogcall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogcall(const char* function, const char* file, int line);

#endif //ASSERTION_H
