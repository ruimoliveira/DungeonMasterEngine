#pragma once

#ifndef mesh_h
#define mesh_h

/**
 * @class Vertex
 *
 * @brief Implementation of Vertex related functionality
 */
class Mesh {
public:
    Mesh() = default;
    ~Mesh();

    void VertexBuilder();
    void Bind();

private:
    unsigned int vertexShaderID {0};

    unsigned int vao {0};
    unsigned int vbo {0};
    unsigned int ebo {0};

};

#endif // mesh_h
