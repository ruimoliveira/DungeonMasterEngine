#include <iostream>
#include <glad/glad.h>

#include "engine.h"

/**
 * Runs everything
 */
void Engine::run() {
    initGLFW();
    initGLAD();
    initOpenGL();
    mainLoop();
    clean();
}

/**
 * Initiates GLFW
 * 
 * @return 0 on success, 1 on failure
 */
int Engine::initGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "DungeonMasterEngine", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    return EXIT_SUCCESS;
}


/**
 * Initiates GLAD
 * 
 * @return 0 on success, 1 on failure
 */
int Engine::initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/**
 * Initiates OpenGL
 */
void Engine::initOpenGL() {
    glViewport(0, 0, 800, 600);

    auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    };

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

/**
 * Initiates Game Logic
 */
void Engine::initGameLogic() {
    gameLogic = new GameLogic();

    //loadGameSettings();
}

/**
 * Main loop function
 */
void Engine::mainLoop() {
    running = true;

    initGameLogic();

    while (running && !glfwWindowShouldClose(window)) {
        handleEvents();
        render();
        update();
    }

    clean();
}

/**
 * Render Function
 */
void Engine::render() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

/**
 * Event Handler function
 */
void Engine::handleEvents() {

}

/**
 * Updater function
 */
void Engine::update() {
    //gameLogic->update();
}

/**
 * Cleaner function
 */
void Engine::clean() {
    glfwTerminate();
}