#pragma once

#ifndef texture_h
#define texture_h

/**
 * @class Texture
 *
 * @brief Implementation of Texture related functionality
 */
class Texture {
public:
    Texture() = default;
    ~Texture() = default;

private:
    void LoadTexture();
    void CreateTexture();
};

#endif // texture_h
