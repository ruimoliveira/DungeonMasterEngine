#pragma once

#ifndef engine_h
#define engine_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Game;
class Shader;

/**
 * @class Engine
 * @brief Implementation of basic game engine functionality
 */
class Engine {
public:
    ~Engine();

    static Engine& Instance();

private:
    Engine() = default;

    static Engine engineInstance;

public:
    void Run();

private:
    int InitGLFW();
    int InitOpenGL();
    void MainLoop();
    void HandleEvents();
    void Update();
    void Render();
    void Clean();

    GLFWwindow* window {nullptr};
    bool running {false};
    Shader* shader {nullptr};

};

#endif // engine_h
