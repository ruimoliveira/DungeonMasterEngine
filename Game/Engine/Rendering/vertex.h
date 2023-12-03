#pragma once

#ifndef vertex_h
#define vertex_h

#include <string>

/**
 * @class Vertex
 *
 * @brief Implementation of Vertex related functionality
 */
class Vertex {
public:
    Vertex() = default;
    ~Vertex();

    void VertexBuilder();
    void Bind();

private:
    unsigned int vertexShaderID {0};

    unsigned int vao {0};
    unsigned int vbo {0};
    unsigned int ebo {0};

};

#endif // vertex_h
