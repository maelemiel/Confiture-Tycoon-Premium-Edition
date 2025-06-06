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
        const auto drawOffset = m_map.getOffset();
        const auto rect = raylib::Rectangle(
            drawOffset.x + m_position.x * size,
            drawOffset.y + m_position.y * size,
            size,
            size
        );

        rect.DrawGradient(
            GREEN,
            RED,
            GREEN,
            RED
        );
    }
} // game
