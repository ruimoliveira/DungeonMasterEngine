#pragma once

#ifndef engine_h
#define engine_h

#include <GLFW/glfw3.h>
#include <string>

#include "gameLogic.h"
#include "Game/game.h"
#include "Engine/Rendering/shader.h"

/**
 * @class Engine
 * @brief Implementation of basic game engine functionality
 */
class Engine {
public:
    Engine() {};
    ~Engine();
    void run(std::string game);

private:
    GLFWwindow* window {nullptr};
    GameLogic* gameLogic {nullptr};
    bool running {false};
    Shader* shader {nullptr};

    int initGLFW(std::string game);
    int initOpenGL();
    void initGameLogic(std::string game);
    void mainLoop(std::string game);
    void handleEvents();
    void update();
    void render();
    void clean();
};

#endif // engine_h
