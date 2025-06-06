//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Game.hpp"

#include <iostream>

namespace game
{
    Game::Game(raylib::Vector2 windowSize)
    {
        m_window = std::make_unique<Window>(windowSize);
        m_map = std::make_unique<Map>(raylib::Vector2(10, 10));
    }

    void Game::handleInput()
    {
        m_lastMousePosition = m_mousePosition;
        m_mousePosition = GetMousePosition();
        m_mouseDelta = m_mousePosition - m_lastMousePosition;

        m_mouseButtonLeftPressed = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        m_mouseButtonMiddlePressed = IsMouseButtonDown(MOUSE_BUTTON_MIDDLE);
        m_mouseButtonRightPressed = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

        m_mouseScrollDelta = GetMouseWheelMoveV();
    }

    void Game::update()
    {
        if (m_mouseButtonMiddlePressed) {
            m_map->setOffset(m_map->getOffset() + m_mouseDelta / m_map->getScale());
        }
        if (m_mouseScrollDelta != Vector2Zero()) {
            // TODO: Make the zoom centered on the mouse position.
            m_map->setScale(m_map->getScale() + m_mouseScrollDelta.y * 0.05f);
        }
    }

    void Game::draw() const
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
