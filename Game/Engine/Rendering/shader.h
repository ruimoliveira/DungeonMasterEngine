#pragma once

#ifndef shader_h
#define shader_h

#include <string>

/**
 * @class Shader
 *
 * @brief Implementation of basic shader functionality
 */
class Shader {
public:
    Shader(const char* vertexShaderPath, const char* geometryShaderPath, const char* fragmentShaderPath);
    ~Shader();

    void ShaderPipeline();
    void ShaderRenderer(float time);
    void Use();

    // utility uniform functions
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;

private:
    void ReadShader(const char* shaderPath, std::string* shaderSource);
    void CompileShader(unsigned int* shaderID, const int glShader, std::string* shaderSource);
    void LinkShader();
    void VertexBuilder();
    void Clean();

    std::string vertexShaderSource {""};
    std::string geometryShaderSource {""};
    std::string fragmentShaderSource {""};

    unsigned int vertexShaderID {0};
    unsigned int geometryShaderID {0};
    unsigned int fragmentShaderID {0};
    unsigned int shaderProgramID {0};

    unsigned int vao {0};
    unsigned int vbo {0};
    unsigned int ebo {0};

};

#endif // shader_h
