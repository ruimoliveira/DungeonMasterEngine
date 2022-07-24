#pragma once

#ifndef shader_h
#define shader_h

class Shader {
public:
	Shader() {};
	~Shader();

	void shaderPipeline();
	void renderShader();

private:
	const char* vertexShaderSource = "#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main() {\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 460 core\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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
	void clean();

};

#endif // shader_h