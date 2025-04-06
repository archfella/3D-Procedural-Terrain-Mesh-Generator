//
// Created by filip on 7/18/24.
//


#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

#include "../vendor/glm/gtc/type_ptr.hpp"
#include "../h/Assertion.h"
#include "../h/Shader.h"


Shader* Shader::globalShader = nullptr;

Shader::Shader(){}

void Shader::SetGlobalShader(Shader& shader) {
    globalShader = &shader;
}

Shader* Shader::GetGlobalShader() {
    return globalShader;
}

Shader::Shader(const std::string &filepath) : m_FilePath(filepath), m_RendererID(0) {
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath) {

    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;

    while(getline(stream, line)) {

        if(line.find("#shader") != std::string::npos) {  // Determine the type of the shader (fragment or vertex).

            if(line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }

            else if(line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }

        }

        else {  // Add the remainder source code.
            ss[(int)type] << line << '\n';
        }

    }

    return {ss[0].str(), ss[1].str()};

}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    // Error handling.
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = new char[length];
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        delete[] message;
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {

    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;

}


void Shader::Bind() const {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}


void Shader::SetUniform3f(const std::string &name, float v0, float v1, float v2) {
    GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2))
}


void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3))
}

void Shader::SetUniform1i(const std::string &name, int v) {
    GLCall(glUniform1i(GetUniformLocation(name), v));
}

void Shader::SetUniform1f(const std::string &name, float v) {
    GLCall(glUniform1f(GetUniformLocation(name), v));
}


void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}


int Shader::GetUniform1i(const std::string &name) {

    int val;
    GLCall(glGetUniformiv(m_RendererID, GetUniformLocation(name), &val));
    return val;

}

float Shader::GetUniform1f(const std::string &name) {

    float val;
    GLCall(glGetUniformfv(m_RendererID, GetUniformLocation(name), &val));
    return val;

}

int Shader::GetUniformLocation(const std::string &name) {

    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if(location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;

    m_UniformLocationCache[name] = location;
    return location;

}

