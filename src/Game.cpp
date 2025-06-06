//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Game.hpp"

#include <iostream>

#include "Structures/House.hpp"
#include "Structures/Tree.hpp"

namespace game
{
    Game::Game(const raylib::Vector2 windowSize) :
        _window(windowSize),
        _map(raylib::Vector2(50, 50)),
        _resourceManager(std::make_unique<ResourceManager>()),
        _isMouseInWindow(false),
        _mouseButtonLeftPressed(false),
        _mouseButtonMiddlePressed(false),
        _mouseButtonRightPressed(false),
        _selectedStructure("House")
    {}

    void Game::handleInput()
    {
        _lastMousePosition = _mousePosition;
        _mousePosition = _window.getMousePosition();
        _mouseDelta = _mousePosition - _lastMousePosition;

        _mouseButtonLeftDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        _mouseButtonMiddleDown = IsMouseButtonDown(MOUSE_BUTTON_MIDDLE);
        _mouseButtonRightDown = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

        _mouseButtonLeftPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        _mouseButtonMiddlePressed = IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE);
        _mouseButtonRightPressed = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);

        _mouseButtonLeftReleased = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
        _mouseButtonMiddleReleased = IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE);
        _mouseButtonRightReleased = IsMouseButtonReleased(MOUSE_BUTTON_RIGHT);

        if (IsKeyPressed(KEY_T)) {
            _selectedStructure = "Tree";
        } else if (IsKeyPressed(KEY_H)) {
            _selectedStructure = "House";
        } else if (IsKeyPressed(KEY_G)) {
            _selectedStructure = "Generator";
        }

        _mouseScrollDelta = GetMouseWheelMoveV();
    }

    void Game::update()
    {
        const auto mouseWorldPosition = _map.getScreenPositionAsWorldPosition(_mousePosition);
        const std::shared_ptr<Tile> hoverTile = _map.getTileAtWorldPosition(mouseWorldPosition);
        const auto structure = _factory.getStructure(_selectedStructure);

        if (structure != nullptr) {
            _map.setHoverSize(structure->getSize());
        } else {
            _map.setHoverSize(0);
        }
        if (_mouseButtonMiddleDown) {
            _map.setOffset(_map.getOffset() + _mouseDelta / _map.getScale());
        }
        if (_mouseScrollDelta != Vector2Zero()) {
            const auto oldMouseOffset = _map.getScreenPositionAsWorldPosition(_mousePosition);

            _map.setScale(_map.getScale() + _mouseScrollDelta.y * 0.05f);

            const auto mouseOffset = _map.getScreenPositionAsWorldPosition(_mousePosition);

            _map.setOffset(_map.getOffset() + (mouseOffset - oldMouseOffset));
        }
        _map.setHoveredTile(hoverTile);
        if (_mouseButtonLeftDown) {
            if (hoverTile != nullptr && !hoverTile->hasStructure()
                && _map.areAllHoveredTilesEmpty()) {
                hoverTile->setStructure(structure);
            }
        }
        if (_mouseButtonRightDown) {
            if (hoverTile != nullptr && hoverTile->hasStructure()) {
                hoverTile->setStructure(nullptr);
            }
        }
        float deltaTime = GetFrameTime();
        _resourceManager->update(deltaTime);
    }

    void Game::draw() const
    {
        _window.beginDraw();
        _window.clear(raylib::Color::White());
        _map.draw(_window);
        raylib::DrawText(
            "Idle JeuConfiture Tycoon (a Jamsoft game)",
            10,
            10,
            20,
            BLACK
        );
        _ui.draw();
        _window.endDraw();
    }

    bool Game::isRunning()
    {
        return _window.isOpen();
    }

    std::string Game::getSelectedStructure() const
    {
        return _selectedStructure;
    }

} // game
