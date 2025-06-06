//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Tile.hpp"

#include <Rectangle.hpp>

#include "Map.hpp"

namespace game {
    Tile::Tile(Map &map, const raylib::Vector2 position) : _map(map),
        _position(position)
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
            rect.DrawLines(WHITE, 5.0f * _map.getScale());
        }
    }

    raylib::Vector2 Tile::getPosition() const
    {
        return _position;
    }

    raylib::Vector2 Tile::getScreenPosition() const
    {
        const auto drawOffset = _map.getOffset();

        return {
            (drawOffset.x + _position.x * size) * _map.getScale(),
            (drawOffset.y + _position.y * size) * _map.getScale()
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
            size * _map.getScale(),
            size * _map.getScale()
        };
    }

    raylib::Rectangle Tile::getBounds() const
    {
        return {
            _position.x * size,
            _position.y * size,
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
        return _hovered;
    }

    void Tile::setHovered(const bool hovered)
    {
        _hovered = hovered;
    }
} // game
