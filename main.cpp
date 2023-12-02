#include <iostream>
#include <stdexcept>

#include "Game/game.h"

int main() {
    try {
        Game::Instance().Run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
