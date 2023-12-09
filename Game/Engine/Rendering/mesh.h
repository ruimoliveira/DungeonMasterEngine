#pragma once

#ifndef mesh_h
#define mesh_h

#include <string>

/**
 * @class Mesh
 *
 * @brief Implementation of Mesh related functionality
 */
class Mesh {
public:
    Mesh() = default;
    ~Mesh();

    void VertexBuilder();
    void BindVertex();
    void LoadTexture(std::string texturePath);
    void BindTexture();

private:
    unsigned int vertexShaderID {0};
    unsigned int textureID {0};

    unsigned int vao {0};
    unsigned int vbo {0};
    unsigned int ebo {0};

};

#endif // mesh_h
