//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Map.hpp"

#include <algorithm>
#include <iostream>
#include <ostream>

namespace game {
    Map::Map(Camera &camera, const raylib::Vector2 size) :
        _camera(camera), _size(size)
    {
        _createTiles();
        setOffsetToCenter();

        _grassTexture = raylib::Texture(
            "assets/textures/grass.png"
        );
    }

    void Map::update(const float dt) const
    {
        for (const auto &tile : _tiles) {
            tile->update(dt);
        }
    }

    void Map::draw(const Window &window) const
    {
        for (const auto &tile : _tiles) {
            tile->drawBackground(window);
        }
        for (const auto &tile : _tiles) {
            tile->drawForeground(window);
        }
        if (_hoveredTile != nullptr && _hoverSize.x > 0 && _hoverSize.y > 0) {
            if (_hoveredTile->isEmpty() && !areAllHoveredTilesEmpty()) {
                return;
            }
            _highlightTiles();
        }
    }

    void Map::_createTiles()
    {
        for (int x = 0; x < static_cast<int>(_size.x); x++) {
            for (int y = 0; y < static_cast<int>(_size.y); y++) {
                _tiles.push_back(
                    std::make_shared<Tile>(
                        *this,
                        raylib::Vector2(
                            static_cast<float>(x),
                            static_cast<float>(y)
                        )
                    )
                );
            }
        }
    }

    void Map::_highlightTiles() const
    {
        const auto targetTile =
            _hoveredTile->getLinkedTile() != nullptr
            ? _hoveredTile->getLinkedTile()
            : _hoveredTile;
        const auto hoverPosition = targetTile->getScreenPosition();
        const auto hoverBounds = raylib::Rectangle(
            hoverPosition.x,
            hoverPosition.y,
            _camera.getScaledValue(_hoverSize.x * Tile::size),
            _camera.getScaledValue(_hoverSize.y * Tile::size)
        );

        hoverBounds.DrawLines(
            areAllHoveredTilesEmpty() ?
                raylib::Color::White() : raylib::Color::SkyBlue(),
            _camera.getScaledValue(5.0f)
        );
    }

    std::shared_ptr<Tile> Map::getTile(const raylib::Vector2 index) const
    {
        for (auto &tile : _tiles) {
            if (tile->getPosition() == index) {
                return tile;
            }
        }
        return nullptr;
    }

    std::shared_ptr<Tile> Map::getTileAtWorldPosition(
        const raylib::Vector2 worldPosition) const
    {
        for (auto &tile : _tiles) {
            if (tile->getBounds().CheckCollision(worldPosition)) {
                return tile;
            }
        }
        return nullptr;
    }

    void Map::setHoveredTile(const std::shared_ptr<Tile> &tile)
    {
        _hoveredTile = tile;
    }

    std::list<std::shared_ptr<Tile>> Map::getHoveredTiles() const
    {
        std::list<std::shared_ptr<Tile>> list;

        for (int x = 0; x < static_cast<int>(_hoverSize.x); x++) {
            for (int y = 0; y < static_cast<int>(_hoverSize.y); y++) {
                const auto tile = getTile(
                    raylib::Vector2(
                        _hoveredTile->getPosition().x + static_cast<float>(x),
                        _hoveredTile->getPosition().y + static_cast<float>(y)
                    )
                );

                list.push_back(tile);
            }
        }
        return list;
    }

    bool Map::areAllHoveredTilesEmpty() const
    {
        return ranges::all_of(getHoveredTiles(), [](const std::shared_ptr<Tile> &tile) {
            if (tile == nullptr) {
                return false;
            }
            return tile->isEmpty();
        });
    }

    void Map::setHoverSize(const raylib::Vector2 size)
    {
        _hoverSize = size;
    }

    const raylib::Texture &Map::getGrassTexture() const
    {
        return _grassTexture;
    }

    void Map::setOffsetToCenter()
    {
        _camera.setOffset(raylib::Vector2(
            1920.0f * 0.5f - _size.x * Tile::size * 0.5f,
            1080.0f * 0.5f - _size.y * Tile::size * 0.5f
        ));
    }

    Camera &Map::getCamera()
    {
        return _camera;
    }
} // game
