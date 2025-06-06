#include "Game.hpp"
#include "raylib-cpp.hpp"

int main() {
    auto game = game::Game(raylib::Vector2(1920, 1080));

    while (game.isRunning()) {
        game.handleInput();
        game.update();
        game.draw();
    }

    return 0;
}
