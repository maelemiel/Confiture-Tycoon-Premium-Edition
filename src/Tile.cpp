//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Tile.hpp"

#include <Rectangle.hpp>

#include "Map.hpp"

namespace game {
    Tile::Tile(Map &map, const raylib::Vector2 position) : m_map(map),
        m_position(position)
    {

    }

    void Tile::draw(Window &window) const
    {
        const auto screenPosition = getScreenPosition();
        const auto screenSize = getScreenSize();
        const auto rect = raylib::Rectangle(
            screenPosition.x,
            screenPosition.y,
            screenSize.x,
            screenSize.y
        );

        rect.DrawGradient(
            GREEN,
            RED,
            GREEN,
            RED
        );
        if (isHovered()) {
            rect.DrawLines(WHITE, 5.0f * m_map.getScale());
        }
    }

    raylib::Vector2 Tile::getPosition() const
    {
        return m_position;
    }

    raylib::Vector2 Tile::getScreenPosition() const
    {
        const auto drawOffset = m_map.getOffset();

        return {
            (drawOffset.x + m_position.x * size) * m_map.getScale(),
            (drawOffset.y + m_position.y * size) * m_map.getScale()
        };
    }

    raylib::Vector2 Tile::getSize() const
    {
        return {
            size,
            size
        };
    }

    raylib::Vector2 Tile::getScreenSize() const
    {
        return {
            size * m_map.getScale(),
            size * m_map.getScale()
        };
    }

    raylib::Rectangle Tile::getBounds() const
    {
        return {
            m_position.x * size,
            m_position.y * size,
            size,
            size
        };
    }

    raylib::Rectangle Tile::getScreenBounds() const
    {
        const auto screenPosition = getScreenPosition();
        const auto screenSize = getScreenSize();

        return {
            screenPosition.x,
            screenPosition.y,
            screenSize.x,
            screenSize.y
        };
    }

    bool Tile::isHovered() const
    {
        return m_hovered;
    }

    void Tile::setHovered(const bool hovered)
    {
        m_hovered = hovered;
    }
} // game
