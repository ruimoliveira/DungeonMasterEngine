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

    void shaderPipeline();
    void shaderRenderer(float time);
    void use();

    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

private:
    std::string vertexShaderSource {""};
    std::string geometryShaderSource {""};
    std::string fragmentShaderSource {""};

    unsigned int vertexShaderID {0};
    unsigned int geometryShaderID {0};
    unsigned int fragmentShaderID {0};
    unsigned int shaderProgramID {0};

    unsigned int VAO {0};
    unsigned int VBO {0};
    unsigned int EBO {0};
    
    void readShader(const char* shaderPath, std::string* shaderSource);
    void compileShader(unsigned int* shaderID, const int glShader, std::string* shaderSource);
    void linkShader();
    void vertexBuilder();
    void clean();

};

#endif // shader_h
