//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Map.hpp"

#include <algorithm>

namespace game {
    Map::Map(const raylib::Vector2 size) : m_size(size), m_scale(1.0f)
    {
        createTiles();
    }

    void Map::createTiles()
    {
        for (int x = 0; x < static_cast<int>(m_size.x); x++) {
            for (int y = 0; y < static_cast<int>(m_size.y); y++) {
                m_tiles.push_back(
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

    void Map::draw(Window &window) const
    {
        for (const auto &tile : m_tiles) {
            tile->draw(window);
        }
    }

    raylib::Vector2 Map::getOffset() const
    {
        return m_offset;
    }

    void Map::setOffset(const raylib::Vector2 offset)
    {
        m_offset = offset;
    }

    float Map::getScale() const
    {
        return m_scale;
    }

    void Map::setScale(const float scale)
    {
        m_scale = std::ranges::clamp(scale, 0.05f, 10.0f);
    }

    raylib::Vector2 Map::getScreenPositionAsWorldPosition(
        const raylib::Vector2 mousePosition) const
    {
        return {
            mousePosition.x / m_scale - m_offset.x,
            mousePosition.y / m_scale - m_offset.y
        };
    }

    std::optional<std::shared_ptr<Tile>> Map::getTileAtWorldPosition(
        const raylib::Vector2 worldPosition) const
    {
        for (auto &tile : m_tiles) {
            if (tile->getBounds().CheckCollision(worldPosition)) {
                return tile;
            }
        }
        return std::nullopt;
    }

    void Map::setHoveredTile(const std::shared_ptr<Tile> &tile) const
    {
        for (auto &itTile : m_tiles) {
            itTile->setHovered(itTile == tile);
        }
    }
} // game
