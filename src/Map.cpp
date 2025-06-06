//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Map.hpp"
#include "PerlinNoise.hpp"

#define NOISE_DONTKNOW 0.1f

#include <algorithm>
#include <iostream>
#include <ostream>
#include <chrono>

namespace game {
    Map::Map(const raylib::Vector2 size) : _size(size), _offset(0, 0),
        _scale(1.0f)
    {
        _grassTexture = std::make_shared<raylib::Texture>(
            "assets/textures/grass.png"
        );
        _dirtTexture = std::make_shared<raylib::Texture>(
            "assets/textures/dirt.png"
        );
        _concreteTexture = std::make_shared<raylib::Texture>(
            "assets/textures/concrete.png"
        );

        createTiles();
        setOffsetToCenter();
    }

    void Map::createTiles()
    {
        const siv::PerlinNoise::seed_type seed =
            std::chrono::system_clock::now().time_since_epoch().count();
        const siv::PerlinNoise perlin{ seed };

        for (int x = 0; x < static_cast<int>(_size.x); x++) {
            for (int y = 0; y < static_cast<int>(_size.y); y++) {
                _tiles.push_back(
                    std::make_shared<Tile>(
                        *this,
                        raylib::Vector2(
                            static_cast<float>(x),
                            static_cast<float>(y)
                        ),
                        perlin.noise2D(x*NOISE_DONTKNOW, y*NOISE_DONTKNOW)
                    )
                );
            }
        }
    }

    void Map::highlightTiles() const
    {
        const auto targetTile =
            _hoveredTile->getLinkedTile() != nullptr
            ? _hoveredTile->getLinkedTile()
            : _hoveredTile;
        const auto hoverPosition = targetTile->getScreenPosition();
        const auto hoverBounds = raylib::Rectangle(
            hoverPosition.x,
            hoverPosition.y,
            _hoverSize.x * Tile::size * _scale,
            _hoverSize.y * Tile::size * _scale
        );

        hoverBounds.DrawLines(
            areAllHoveredTilesEmpty() ?
                raylib::Color::White() : raylib::Color::SkyBlue(),
            5.0f * _scale
        );
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
            highlightTiles();
        }
    }

    raylib::Vector2 Map::getOffset() const
    {
        return _offset;
    }

    void Map::setOffset(const raylib::Vector2 offset)
    {
        _offset = offset;
    }

    float Map::getScale() const
    {
        return _scale;
    }

    void Map::setScale(const float scale)
    {
        _scale = std::ranges::clamp(scale, 0.05f, 10.0f);
    }

    raylib::Vector2 Map::getScreenPositionAsWorldPosition(
        const raylib::Vector2 mousePosition) const
    {
        return {
            mousePosition.x / _scale - _offset.x,
            mousePosition.y / _scale - _offset.y
        };
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

    std::shared_ptr<raylib::Texture> Map::getGrassTexture() const
    {
        return _grassTexture;
    }

    std::shared_ptr<raylib::Texture> Map::getDirtTexture() const
    {
        return _dirtTexture;
    }

    std::shared_ptr<raylib::Texture> Map::getConcreteTexture() const
    {
        return _concreteTexture;
    }

    void Map::setOffsetToCenter()
    {
        setOffset(raylib::Vector2(
            1920.0f * 0.5f - _size.x * Tile::size * 0.5f,
            1080.0f * 0.5f - _size.y * Tile::size * 0.5f
        ));
    }

    raylib::Vector2 Map::getSize() const
    {
        return _size;
    }
} // game
