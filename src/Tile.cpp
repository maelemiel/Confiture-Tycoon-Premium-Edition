//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Tile.hpp"

#include <iostream>
#include <Rectangle.hpp>

#include "Map.hpp"

namespace game {
    Tile::Tile(Map &map, const raylib::Vector2 position) : _map(map),
        _position(position)
    {
        _structure = nullptr;
    }

    void Tile::draw(const Window &window) const
    {
        const auto screenPosition = getScreenPosition();
        const auto screenSize = getScreenSize();
        const auto rect = raylib::Rectangle(
            screenPosition.x,
            screenPosition.y,
            screenSize.x,
            screenSize.y
        );

        _map.getGrassTexture().Draw(
            screenPosition,
            0.0f,
            getTextureScaleFactor(_map.getGrassTexture()),
            raylib::Color::White()
        );
        if (_structure != nullptr) {
            const auto &texture = _structure->getSprite();

            texture.Draw(
                screenPosition,
                0.0f,
                getTextureScaleFactor(texture),
                raylib::Color::White()
            );
        }
        if (isHovered()) {
            rect.DrawLines(WHITE, 3.0f * _map.getScale());
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

    bool Tile::hasStructure() const
    {
        return _structure != nullptr;
    }

    Structure::IStructure &Tile::getStructure() const
    {
        return *_structure;
    }

    void Tile::setStructure(std::unique_ptr<Structure::IStructure> structure)
    {
        _structure = std::move(structure);
    }

    float Tile::getTextureScaleFactor(const raylib::Texture &texture) const
    {
        return size / texture.GetSize().x * _map.getScale();
    }
} // game
