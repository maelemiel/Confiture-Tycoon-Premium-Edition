//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Game.hpp"

#include <iostream>

#include "Structures/Tree.hpp"

namespace game
{
    Game::Game(raylib::Vector2 windowSize)
    {
        _window = std::make_unique<Window>(windowSize);
        _map = std::make_unique<Map>(raylib::Vector2(10, 10));
    }

    void Game::handleInput()
    {
        _lastMousePosition = _mousePosition;
        _mousePosition = GetMousePosition();
        _mouseDelta = _mousePosition - _lastMousePosition;

        _mouseButtonLeftDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        _mouseButtonMiddleDown = IsMouseButtonDown(MOUSE_BUTTON_MIDDLE);
        _mouseButtonRightDown = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

        _mouseButtonLeftPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        _mouseButtonMiddlePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        _mouseButtonRightPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        _mouseButtonLeftReleased = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
        _mouseButtonMiddleReleased = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
        _mouseButtonRightReleased = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

        _mouseScrollDelta = GetMouseWheelMoveV();
    }

    void Game::update()
    {
        const auto mouseWorldPosition = _map->getScreenPositionAsWorldPosition(_mousePosition);
        const std::shared_ptr<Tile> hoverTile = _map->getTileAtWorldPosition(mouseWorldPosition);

        if (_mouseButtonMiddleDown) {
            _map->setOffset(_map->getOffset() + _mouseDelta / _map->getScale());
        }
        if (_mouseScrollDelta != Vector2Zero()) {
            const auto oldMouseOffset = _map->getScreenPositionAsWorldPosition(_mousePosition);

            _map->setScale(_map->getScale() + _mouseScrollDelta.y * 0.05f);

            const auto mouseOffset = _map->getScreenPositionAsWorldPosition(_mousePosition);

            _map->setOffset(_map->getOffset() + (mouseOffset - oldMouseOffset));
        }
        _map->setHoveredTile(hoverTile);
        if (_mouseButtonLeftDown) {
            if (hoverTile != nullptr && !hoverTile->hasStructure()) {
                hoverTile->setStructure(std::make_unique<Structure::Tree>());
            }
        }
        if (_mouseButtonRightDown) {
            if (hoverTile != nullptr && hoverTile->hasStructure()) {
                hoverTile->setStructure(nullptr);
            }
        }
    }

    void Game::draw() const
    {
        raylib::Window &raylibWindow = _window->getRaylibWindow();

        raylibWindow.BeginDrawing();
        raylibWindow.ClearBackground(WHITE);
        _map->draw(*_window);
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
        return _window->isOpen();
    }
} // game
