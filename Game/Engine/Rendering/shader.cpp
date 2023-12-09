#include "shader.h"

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "mesh.h"

/**
 * @brief Shader constructor
 *
 * @param vertexShaderPath Path to vertex shader GLSL code
 * @param geometryShaderPath Path to geometry shader GLSL code
 * @param fragmentShaderPath Path to fragment shader GLSL code
 */
Shader::Shader(const char* vertexShaderPath, const char* geometryShaderPath, const char* fragmentShaderPath) {
    if (vertexShaderPath != NULL) {
        ReadShader(vertexShaderPath, &vertexShaderSource);
    }
    if (geometryShaderPath != NULL) {
        ReadShader(geometryShaderPath, &geometryShaderSource);
    }
    if (fragmentShaderPath != NULL) {
        ReadShader(fragmentShaderPath, &fragmentShaderSource);
    }

    mesh = new Mesh();
}

/**
 * @brief Shader destructor
 */
Shader::~Shader() {
    delete mesh;
    glDeleteProgram(shaderProgramID);
}

/**
 * @brief Shader pipeline function
 */
void Shader::ShaderPipeline() {
    if (vertexShaderSource.empty() || fragmentShaderSource.empty()) {
        std::cout << "ERROR::SHADER : No shader code compiled" << std::endl;
        return;
    }

    if (!vertexShaderSource.empty()) {
        CompileShader(&vertexShaderID, GL_VERTEX_SHADER, &vertexShaderSource);
    }
    if (!geometryShaderSource.empty()) {
        CompileShader(&geometryShaderID, GL_GEOMETRY_SHADER,&geometryShaderSource);
    }
    if (!fragmentShaderSource.empty()) {
        CompileShader(&fragmentShaderID, GL_FRAGMENT_SHADER, &fragmentShaderSource);
    }

    LinkShader();
    Clean();

    //TODO: Eventually move to scene builder and resource loading and managing
    mesh->VertexBuilder();
    mesh->LoadTexture("Game/Assets/GameData/wall.jpg");
}

/**
 * @brief GLSL shader code reader
 *
 * @param shaderPath Path to shader GLSL code
 * @param shaderSource Variable to save source code into
 */
void Shader::ReadShader(const char* shaderPath, std::string* shaderSource) {
    std::string glslCode;
    std::ifstream shaderFile;
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        glslCode = shaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER : Shader file not read at " << shaderPath << std::endl;
        glslCode = "";
    }
    *shaderSource = glslCode;
}

/**
 * @brief Shader compiler function
 *
 * @param shaderID Variable to save shader ID on
 * @param glShader Type of shader to be compiled
 * @param shaderSource Shader GLSL source code
 */
void Shader::CompileShader(unsigned int* shaderID, const int glShader, std::string* shaderSource) {
    //shader pipeline commands
    *shaderID = glCreateShader(glShader);
    const char* source = (*shaderSource).c_str();
    glShaderSource(*shaderID, 1, &source, NULL);
    glCompileShader(*shaderID);
    
    //check for compile errors
    int  success;
    char infoLog[512];
    glGetShaderiv(*shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(*shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER : Shader compiler errors:\n" << infoLog << std::endl;
    }
}

/**
 * @brief Vertex Attribute Linker
 */
void Shader::LinkShader() {
    // shader program
    shaderProgramID = glCreateProgram();

    if (!vertexShaderSource.empty()) {
        glAttachShader(shaderProgramID, vertexShaderID);
    }
    if (!geometryShaderSource.empty()) {
        glAttachShader(shaderProgramID, geometryShaderID);
    }
    if (!fragmentShaderSource.empty()) {
        glAttachShader(shaderProgramID, fragmentShaderID);
    }
    glLinkProgram(shaderProgramID);

    // check for compile errors
    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER : Shader linker errors :\n" << infoLog << std::endl;
    }
}

/**
 * @brief Render function
 *
 * @param time Time since last frame
 */
void Shader::ShaderRenderer(float time) {
    mesh->BindTexture();
    Use();
    mesh->BindVertex();
}

/**
 * @brief Shader activation function
 */
void Shader::Use() {
    glUseProgram(shaderProgramID);
}

/**
 * @brief GLSL uniform bool variable setter 
 */
void Shader::SetBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), (int)value);
}

/**
 * @brief GLSL uniform int variable setter 
 */
void Shader::SetInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}

/**
 * @brief GLSL uniform float variable setter 
 */
void Shader::SetFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}

/**
 * @brief Cleaner function
 */
void Shader::Clean() {
    if (!vertexShaderSource.empty()) {
        glDeleteShader(vertexShaderID);
    }
    if (!geometryShaderSource.empty()) {
        glDeleteShader(geometryShaderID);
    }
    if (!fragmentShaderSource.empty()) {
        glDeleteShader(fragmentShaderID);
    }
}
