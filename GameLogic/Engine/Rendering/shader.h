#pragma once

#ifndef shader_h
#define shader_h

class Shader {
public:
    Shader() {};
    ~Shader();

    void shaderPipeline();
    void shaderRenderer(float time);

private:
    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec3 vertexColor;\n"
        "void main() {\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "   vertexColor = aColor;\n"
        "}\0";

    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 vertexColor;\n"
        "void main() {\n"
        "   FragColor = vec4(vertexColor, 1.0);\n"
        "}\0";

    unsigned int vertexShaderID {0};
    //unsigned int geometryShaderID {0};
    unsigned int fragmentShaderID {0};
    unsigned int shaderProgramID {0};
    unsigned int VAO {0};
    unsigned int VBO {0};
    unsigned int EBO {0};

    void vertexShader();
    void geometryShader();
    void fragmentShader();
    void shaderLinker();
    void vertexBuilder();
    void use();
    void clean();

};

#endif // shader_h
