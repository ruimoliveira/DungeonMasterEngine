#include "engine.h"

#include <iostream>

#include "../game.h"
#include "Rendering/shader.h"

/**
 * @brief Creates an Engine instance
 */
Engine Engine::engineInstance;

/**
 * @brief Instace getter
 * 
 * @return Instance of the Engine
 */
Engine& Engine::Instance() {
    return engineInstance;
}

/**
 * @brief Runs Engine components
 */
void Engine::Run() {
    InitGLFW();
    InitOpenGL();
    MainLoop();
    Clean();
}

/**
 * @brief Initiates GLFW
 *
 * @param game Name of the game
 * @return 0 on success, 1 on failure
 */
int Engine::InitGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(800, 600, "", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    };
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return EXIT_SUCCESS;
}

/**
 * @brief Initiates OpenGL
 *
 * @return 0 on success, 1 on failure
 */
int Engine::InitOpenGL() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Main loop function
 */
void Engine::MainLoop() {
    running = true;

    shader = new Shader("Game/Engine/Rendering/Shaders/vertexShader.glsl",
                        NULL,
                        "Game/Engine/Rendering/Shaders/fragmentShader.glsl");
    shader->ShaderPipeline();

    while (running && !glfwWindowShouldClose(window)) {
        HandleEvents();
        Update();
        Render();
    }

    Clean();
}

/**
 * @brief Event Handler function
 */
void Engine::HandleEvents() {
    Game::Instance().HandleEvents();

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }
}

/**
 * @brief Updater function
 */
void Engine::Update() {
    Game::Instance().Update();
}

/**
 * @brief Render Function
 */
void Engine::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    // rendering commands start
    shader->ShaderRenderer(glfwGetTime());

    // check and call events and swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}

/**
 * @brief Cleaner function
 */
void Engine::Clean() {
    glfwTerminate();
}

/**
 * @brief Engine destructor
 */
Engine::~Engine() {
    delete shader;
}