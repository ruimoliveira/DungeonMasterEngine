#include <iostream>
#include <glad/glad.h>

#include "engine.h"


/**
 * Engine destructor
 */
Engine::~Engine() {
    delete shader;
    delete gameLogic;
}

/**
 * Runs everything
 */
void Engine::run(std::string game) {
    initGLFW(game);
    initOpenGL();
    mainLoop(game);
    clean();
}

/**
 * Initiates GLFW
 *
 * @return 0 on success, 1 on failure
 */
int Engine::initGLFW(std::string game) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    //TODO: loadUserConfigs();

    window = glfwCreateWindow(800, 600, game.c_str(), NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    return EXIT_SUCCESS;
}

/**
 * Initiates OpenGL
 *
 * @return 0 on success, 1 on failure
 */
int Engine::initOpenGL() {
    auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    };
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    gladLoadGL();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/**
 * Initiates Game Logic
 */
void Engine::initGameLogic(std::string game) {
    gameLogic = new GameLogic();

    //TODO: loadGameSettings(game);
}

/**
 * Main loop function
 */
void Engine::mainLoop(std::string game) {
    running = true;

    initGameLogic(game);

    shader = new Shader();
    shader->shaderPipeline();

    while (running && !glfwWindowShouldClose(window)) {
        handleEvents();
        update();
        render();
    }

    clean();
}

/**
 * Event Handler function
 */
void Engine::handleEvents() {
    // TODO: handle game logic events
    
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }
}

/**
 * Updater function
 */
void Engine::update() {
    //gameLogic->update();
}

/**
 * Render Function
 */
void Engine::render() {
    // rendering commands start
    shader->shaderRenderer(glfwGetTime());

    // check and call events and swap the buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
}

/**
 * Cleaner function
 */
void Engine::clean() {
    glfwTerminate();
}
