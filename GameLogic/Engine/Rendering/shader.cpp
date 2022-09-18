#include "shader.h"

#include <glad/glad.h>
#include <iostream>

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
    vertexShader();
    geometryShader();
    fragmentShader();

    shaderLinker();
    clean();

    vertexBuilder();
}

/**
 * Vertex Shader stage
 */
void Shader::vertexShader() {
    // vertex shader pipeline commands
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderID);

    // check for compile errors
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

/**
 * Geometry Shader stage
 */
void Shader::geometryShader() {
    // geometry shader pipeline commands

}

/**
 * Fragment Shader stage
 */
void Shader::fragmentShader() {
    // fragment shader pipeline commands
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderID);

    // check for compile errors
    int  success;
    char infoLog[512];
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::FRAGMENT::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

/**
 * Vertex Attribute Linker
 */
void Shader::shaderLinker() {
    // shader program
    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    //glAttachShader(shaderProgram, geometryShaderID);
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
 * Vertex Shader stage
 */
void Shader::clean() {
    // shader clean
    glDeleteShader(vertexShaderID);
    //glDeleteShader(geometryShaderID);
    glDeleteShader(fragmentShaderID);
}
