#include "shader.h"

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * Shader constructor
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
}

/**
 * Shader destructor
 */
Shader::~Shader() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shaderProgramID);
}

/**
 * Shader pipeline function
 */
void Shader::ShaderPipeline() {
    if (vertexShaderSource.empty() || fragmentShaderSource.empty()) {
        std::cout << "ERROR::SHADER::NO_SHADER_CODE_COMPILED" << std::endl;
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

    VertexBuilder();
}

/**
 * GLSL shader code reader
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
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << shaderPath << std::endl;
        glslCode = "";
    }
    *shaderSource = glslCode;
}

/**
 * Shader compiler function
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
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

/**
 * Vertex Attribute Linker
 */
void Shader::LinkShader() {
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
void Shader::VertexBuilder() {
    // vertex input
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f    // top
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
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
 *
 * @param time Time since last frame
 */
void Shader::ShaderRenderer(float time) {
    Use();
    
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

/**
 * Shader activation function
 */
void Shader::Use() {
    glUseProgram(shaderProgramID);
}

/**
 * GLSL uniform bool variable setter 
 */
void Shader::SetBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), (int)value);
}

/**
 * GLSL uniform int variable setter 
 */
void Shader::SetInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}

/**
 * GLSL uniform float variable setter 
 */
void Shader::SetFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}

/**
 * Cleaner function
 */
void Shader::Clean() {
    glDeleteShader(vertexShaderID);
    //glDeleteShader(geometryShaderID);
    glDeleteShader(fragmentShaderID);
}
