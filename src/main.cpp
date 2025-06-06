#include "Game.hpp"
#include "raylib-cpp.hpp"

int main() {
    const auto game = game::Game(raylib::Vector2(1920, 1080));

    while (game.isRunning()) {
        game.update();
    }
    return 0;
}
