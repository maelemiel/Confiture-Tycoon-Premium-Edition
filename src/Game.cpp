//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Game.hpp"

#include <iostream>

namespace game
{
    Game::Game(raylib::Vector2 windowSize)
    {
        _window = std::make_unique<Window>(windowSize);
        _map = std::make_unique<Map>(raylib::Vector2(10, 10));
        _resourceManager = std::make_unique<ResourceManager>();
    }

    void Game::handleInput()
    {
        _lastMousePosition = _mousePosition;
        _mousePosition = GetMousePosition();
        _mouseDelta = _mousePosition - _lastMousePosition;

        _mouseButtonLeftPressed = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        _mouseButtonMiddlePressed = IsMouseButtonDown(MOUSE_BUTTON_MIDDLE);
        _mouseButtonRightPressed = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

        _mouseScrollDelta = GetMouseWheelMoveV();
    }

    void Game::update()
    {
        const auto mouseWorldPosition = _map->getScreenPositionAsWorldPosition(_mousePosition);
        const std::optional<std::shared_ptr<Tile>> hoverTile = _map->getTileAtWorldPosition(mouseWorldPosition);

        if (_mouseButtonMiddlePressed) {
            _map->setOffset(_map->getOffset() + _mouseDelta / _map->getScale());
        }
        if (_mouseScrollDelta != Vector2Zero()) {
            const auto oldMouseOffset = _map->getScreenPositionAsWorldPosition(_mousePosition);

            _map->setScale(_map->getScale() + _mouseScrollDelta.y * 0.05f);

            const auto mouseOffset = _map->getScreenPositionAsWorldPosition(_mousePosition);

            _map->setOffset(_map->getOffset() + (mouseOffset - oldMouseOffset));
        }
        if (hoverTile.has_value()) {
            _map->setHoveredTile(hoverTile.value());
        } else {
            _map->setHoveredTile(nullptr);
        }
        float deltaTime = GetFrameTime();
        _resourceManager->update(deltaTime);
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
