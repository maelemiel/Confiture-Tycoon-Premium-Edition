//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Game.hpp"
#include <string>

#include <iostream>

#include "Structures/House.hpp"
#include "Structures/Tree.hpp"

namespace game
{
    Game::Game(const raylib::Vector2 windowSize) :
        _window(windowSize),
        _map(_camera, raylib::Vector2(50, 50)),
        _resourceManager(std::make_unique<ResourceManager>()),
        _ui(*_resourceManager),
        _eventManager(_map),
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
        } else if (IsKeyPressed(KEY_S)) {
            _selectedStructure = "Mine";
        } else if (IsKeyPressed(KEY_B)) {
            _selectedStructure = "Grange";
        }

        _mouseScrollDelta = GetMouseWheelMoveV();
    }

    void Game::update()
    {
        const auto mouseWorldPosition = _camera.getScreenPositionAsWorldPosition(_mousePosition);
        const std::shared_ptr<Tile> hoverTile = _map.getTileAtWorldPosition(mouseWorldPosition);
        const auto structure = _factory.getStructure(_selectedStructure);

        if (structure != nullptr) {
            _map.setHoverSize(structure->getSize());
        } else {
            _map.setHoverSize(0);
        }
        if (_mouseButtonMiddleDown) {
            _camera.setOffset(_camera.getOffset() + _mouseDelta / _camera.getZoom());
        }
        if (_mouseScrollDelta != Vector2Zero()) {
            const auto oldMouseOffset = _camera.getScreenPositionAsWorldPosition(_mousePosition);

            _camera.setZoom(_camera.getZoom() + _mouseScrollDelta.y * 0.05f);

            const auto mouseOffset = _camera.getScreenPositionAsWorldPosition(_mousePosition);

            _camera.setOffset(_camera.getOffset() + (mouseOffset - oldMouseOffset));
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

        const float deltaTime = GetFrameTime();

        _resourceManager->update(deltaTime);
        _eventManager.update(deltaTime);
        _resourceManager->RessourceUpdate(_map.getTiles());
        _map.update(deltaTime);

        _ui.population = std::to_string(_resourceManager->getPopulation());
        _ui.resources = std::to_string(_resourceManager->getSweetSweet());

        int oxygenRate = _resourceManager->getOxygenPerSecond();
        _ui.oxygenRateText = (oxygenRate >= 0 ? "+" : "") + std::to_string(oxygenRate) + "/s";
        _ui.oxygenRateColor = (oxygenRate >= 0 ? raylib::Color::Green() : raylib::Color::Red());

        int sweetSweetRate = _resourceManager->getSweetSweetPerSecond();
        _ui.resourcesRateText = (sweetSweetRate >= 0 ? "+" : "") + std::to_string(sweetSweetRate) + "/s";
        _ui.resourcesRateColor = (sweetSweetRate >= 0 ? raylib::Color::Green() : raylib::Color::Red());

        _ui.woodAmountText = std::to_string(_resourceManager->getWood());
        int woodRate = _resourceManager->getWoodPerSecond();
        _ui.woodRateText = (woodRate >= 0 ? "+" : "") + std::to_string(woodRate) + "/s";
        _ui.woodRateColor = (woodRate >= 0 ? raylib::Color::Green() : raylib::Color::Red());

        _ui.stoneAmountText = std::to_string(_resourceManager->getStone());
        int stoneRate = _resourceManager->getStonePerSecond();
        _ui.stoneRateText = (stoneRate >= 0 ? "+" : "") + std::to_string(stoneRate) + "/s";
        _ui.stoneRateColor = (stoneRate >= 0 ? raylib::Color::Green() : raylib::Color::Red());
    }

    void Game::draw() const
    {
        _window.beginDraw();
        _window.clear(raylib::Color::White());
        _map.draw(_window);
        _eventManager.draw(_window);
        raylib::DrawText(
            "Idle JeuConfiture Tycoon (a Jamsoft game)",
            10,
            10,
            20,
            BLACK
        );
        _ui.draw();
        _window.getRaylibWindow().DrawFPS();
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
