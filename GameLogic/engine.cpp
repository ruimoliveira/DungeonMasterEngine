#include <iostream>
#include <glad/glad.h>

#include "engine.h"

/**
 * Initiates GLFW components and engine functions
 */
void Engine::run() {
    initGLFW();
    initGLAD();
    initOpenGL();
    mainLoop();
    clean();
}

int Engine::initGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    return EXIT_SUCCESS;
}

int Engine::initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void Engine::initOpenGL() {
    glViewport(0, 0, 800, 600);

    auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    };

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void Engine::initGameLogic() {
    gameLogic = new GameLogic();
}

void Engine::mainLoop() {
    running = true;

    initGameLogic();

    while (running && !glfwWindowShouldClose(window)) {
        render();
        handleEvents();
        update();
    }

    clean();
}

void Engine::render() {
    glfwSwapBuffers(window);
}

void Engine::handleEvents() {
    glfwPollEvents();
}

void Engine::update() {
    //gameLogic->update();
}

void Engine::clean() {
    glfwTerminate();
}