//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Game.hpp"

namespace game
{
    Game::Game(raylib::Vector2 windowSize)
    {
        m_window = std::make_unique<Window>(windowSize);
        m_map = std::make_unique<Map>(raylib::Vector2(10, 10));
    }

    void Game::update() const
    {
        raylib::Window &raylibWindow = m_window->getRaylibWindow();

        raylibWindow.BeginDrawing();
        raylibWindow.ClearBackground(WHITE);
        m_map->draw(*m_window);
        raylib::DrawText(
            "Idle JeuConfiture Tycoon (a Jamsoft game)",
            10,
            10,
            20,
            BLACK
        );
        raylibWindow.EndDrawing();
    }

    bool Game::isRunning() const
    {
        return m_window->isOpen();
    }
} // game
