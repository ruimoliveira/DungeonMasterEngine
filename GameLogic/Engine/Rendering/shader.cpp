#include "shader.h"

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * Deletes used shader data
 */
Shader::Shader(const char* vertexShaderPath, const char* geometryShaderPath, const char* fragmentShaderPath) {
    readShader(vertexShaderPath, &vertexShaderSource);
    //readShader(geometryShaderPath, &geometryShaderSource);
    readShader(fragmentShaderPath, &fragmentShaderSource);
}

/**
 * Deletes used shader data
 */
Shader::~Shader() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgramID);
}

/**
 * Shader pipeline function
 */
void Shader::shaderPipeline() {
    if (vertexShaderSource.empty() || fragmentShaderSource.empty()) {
        std::cout << "ERROR::SHADER::NO_SHADER_CODE_COMPILED" << std::endl;
        return;
    }
    compileShader(&vertexShaderID, GL_VERTEX_SHADER, &vertexShaderSource);
    //compileShader(&geometryShaderID, GL_GEOMETRY_SHADER,&geometryShaderSource);
    compileShader(&fragmentShaderID, GL_FRAGMENT_SHADER, &fragmentShaderSource);
    
    linkShader();
    clean();

    vertexBuilder();
}

/**
 * GLSL shader code reader
 */
void Shader::readShader(const char* shaderPath, std::string* shaderSource) {
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
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << shaderPath << std::endl;
        glslCode = "";
    }
    *shaderSource = glslCode;
}

/**
 * Shader compiler function
 */
void Shader::compileShader(unsigned int* shaderID, const int glShader, std::string* shaderSource) {
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
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

/**
 * Vertex Attribute Linker
 */
void Shader::linkShader() {
    // shader program
    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    //glAttachShader(shaderProgramID, geometryShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);

    // check for compile errors
    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

/**
 * Shape Builder
 */
void Shader::vertexBuilder() {
    // vertex input
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // linking vertex attributes
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/**
 * Render function
 */
void Shader::shaderRenderer(float time) {
    use();
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

/**
 * Vertex Shader stage
 */
void Shader::use() {
    glUseProgram(shaderProgramID);
}

/**
 * GLSL uniform bool variable setter 
 */
void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), (int)value);
}

/**
 * GLSL uniform int variable setter 
 */
void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}

/**
 * GLSL uniform float variable setter 
 */
void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}

/**
 * Vertex Shader stage
 */
void Shader::clean() {
    // shader clean
    glDeleteShader(vertexShaderID);
    //glDeleteShader(geometryShaderID);
    glDeleteShader(fragmentShaderID);
}
