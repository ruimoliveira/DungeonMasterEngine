#include <iostream>
#include <stdexcept>

#include "GameLogic/engine.h"

int main() {
    Engine* engine = new Engine();
    std::string game = "Magic: Plane at War";

    try {
        engine->run(game);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    delete engine;

    return EXIT_SUCCESS;
}
