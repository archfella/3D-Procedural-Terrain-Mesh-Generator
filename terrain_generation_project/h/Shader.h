//
// Created by filip on 7/18/24.
//

#ifndef SHADER_H
#define SHADER_H

#include <vector>
#include <string>
#include <unordered_map>
#include <../vendor/glm/glm.hpp>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader {
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
    //caching for uniforms
public:
    Shader();
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    //Set uniforms
    void SetUniform1i(const std::string& name, int v);
    void SetUniform1f(const std::string& name, float v);
    void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
    void SetUniform3f(const std::string& name, float v0, float v1, float f2);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

    //Get uniforms
    int GetUniform1i(const std::string& name);
    float GetUniform1f(const std::string& name);

    //TBO
    void SetTransformFeedbackVaryings(const std::vector<const char*>& varyings);
private:
    bool CompileShader();
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    int GetUniformLocation(const std::string& name);
};



#endif //SHADER_H
