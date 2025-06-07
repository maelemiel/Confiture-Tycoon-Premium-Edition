//
// Created by Charles Mahoudeau on 6/7/25.
//

#include "Main.hpp"
#include "Game.hpp"

namespace game::scene {
    Main::Main(Game &game) :
        AScene(game),
        _map(game.getCamera(), raylib::Vector2(50, 50)),
        _resourceManager(game),
        _eventManager(_map),
        _ui(game, _resourceManager),
        _selectedStructure("House"),
        _background("assets/background.png")
    {
        _ui.setDrawerClickCallback([this](const std::string &structureName) {
            _selectedStructure = structureName;
        });
    }

    bool Main::_verifyResources(std::shared_ptr<Structure::IStructure> structure) {
        if (structure->getResourceCost() > _resourceManager.getSweetSweet() ||
            structure->getStoneCost() > _resourceManager.getStone() ||
            structure->getWoodCost() > _resourceManager.getWood())
            return false;
        return true;
    }

    void Main::_updateMouse([[maybe_unused]] float dt)
    {
        auto &game = getGame();
        auto &camera = game.getCamera();
        const auto mouseWorldPosition = camera.getScreenPositionAsWorldPosition(game.getMousePosition());
        const std::shared_ptr<Tile> hoverTile = _map.getTileAtWorldPosition(mouseWorldPosition);
        const auto structure = _factory.getStructure(_selectedStructure);

        if (_ui.isInBounds(game.getMousePosition())) {
            return;
        }
        if (structure != nullptr) {
            _map.setHoverSize(structure->getSize());
            _map.setCurrentStructure(structure);
        } else {
            _map.setHoverSize(0);
            _map.setCurrentStructure(nullptr);
        }
        _map.setHoveredTile(hoverTile);
        if (game.isMouseButtonMiddleDown()) {
            camera.setOffset(camera.getOffset() + game.getMouseDelta() / camera.getZoom());
        }
        if (game.getMouseScrollDelta() != Vector2Zero()) {
            const auto oldMouseOffset = camera.getScreenPositionAsWorldPosition(game.getMousePosition());

            camera.setZoom(camera.getZoom() + game.getMouseScrollDelta().y * 0.05f);

            const auto mouseOffset = camera.getScreenPositionAsWorldPosition(game.getMousePosition());

            camera.setOffset(camera.getOffset() + (mouseOffset - oldMouseOffset));
        }
        _placeStructure(game, hoverTile, structure);
        if (game.isMouseButtonRightDown()) {
            if (hoverTile != nullptr && hoverTile->hasStructure()) {
                hoverTile->setStructure(nullptr);
            }
        }
    }

    void Main::_takeResources(std::shared_ptr<Structure::IStructure> structure) {
        _resourceManager.addSweetSweet(-structure->getResourceCost());
        _resourceManager.addWood(-structure->getWoodCost());
        _resourceManager.addStone(-structure->getStoneCost());
    }

    void Main::_placeStructure(Game &game, std::shared_ptr<Tile> hoverTile,
        std::shared_ptr<Structure::IStructure> structure) {
        if (game.isMouseButtonLeftDown() && _verifyResources(structure)) {
            if (hoverTile != nullptr && _map.canPlaceStructureOnHoveredTiles(structure)) {
                _takeResources(structure);
                hoverTile->setStructure(structure);
            }
        }
    }

    void Main::update(const float dt)
    {
        auto &game = getGame();
        auto &camera = game.getCamera();
        const auto mouseWorldPosition = camera.getScreenPositionAsWorldPosition(game.getMousePosition());
        const std::shared_ptr<Tile> hoverTile = _map.getTileAtWorldPosition(mouseWorldPosition);
        const auto structure = _factory.getStructure(_selectedStructure);

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

        _updateMouse(dt);

        _resourceManager.update(dt);
        _eventManager.update(dt);
        _ui.update();
        _resourceManager.RessourceUpdate(_map.getTiles());
        _map.update(dt);

        _ui.population = std::to_string(_resourceManager.getPopulation());
        _ui.resources = std::to_string(_resourceManager.getSweetSweet());

        int oxygenRate = _resourceManager.getOxygenPerSecond();
        _ui.oxygenRateText = (oxygenRate >= 0 ? "+" : "") + std::to_string(oxygenRate) + "/s";
        _ui.oxygenRateColor = (oxygenRate >= 0 ? raylib::Color::Green() : raylib::Color::Red());

        int sweetSweetRate = _resourceManager.getSweetSweetPerSecond();
        _ui.resourcesRateText = (sweetSweetRate >= 0 ? "+" : "") + std::to_string(sweetSweetRate) + "/s";
        _ui.resourcesRateColor = (sweetSweetRate >= 0 ? raylib::Color::Green() : raylib::Color::Red());

        _ui.woodAmountText = std::to_string(_resourceManager.getWood());
        int woodRate = _resourceManager.getWoodPerSecond();
        _ui.woodRateText = (woodRate >= 0 ? "+" : "") + std::to_string(woodRate) + "/s";
        _ui.woodRateColor = (woodRate >= 0 ? raylib::Color::Green() : raylib::Color::Red());

        _ui.stoneAmountText = std::to_string(_resourceManager.getStone());
        int stoneRate = _resourceManager.getStonePerSecond();
        _ui.stoneRateText = (stoneRate >= 0 ? "+" : "") + std::to_string(stoneRate) + "/s";
        _ui.stoneRateColor = (stoneRate >= 0 ? raylib::Color::Green() : raylib::Color::Red());

        _ui.getDualityBar().setLevel(_resourceManager.getDualityScore());
    }

    void Main::draw() const
    {
        auto &game = getGame();
        const auto &window = game.getWindow();

        _background.Draw();
        _map.draw(window);
        _eventManager.draw(window);
        _ui.draw();
    }
} // game::scene
