//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Tile.hpp"

#include <cassert>
#include <iostream>
#include <Rectangle.hpp>

#include "Map.hpp"

namespace game {
    Tile::Tile(Map &map, const raylib::Vector2 position) : _map(map),
        _position(position)
    {
        _structure = nullptr;
        _linkedTile = nullptr;
    }

    void Tile::drawBackground(const Window &window) const
    {
        const auto screenPosition = getScreenPosition();
        const float textureScale = size / 512.0f * _map.getScale();
        auto tint = raylib::Color::White();

        if (hasStructure()) {
            if (Structure::IStructure &structure = getStructure();
                structure.getPollutionEffect() < 0) {
                tint = raylib::Color::Green();
            } else if (structure.getPollutionEffect() > 0) {
                tint = raylib::Color::Red();
            }
        }
        _map.getGrassTexture().Draw(
            screenPosition,
            0.0f,
            textureScale,
            tint
        );
    }

    void Tile::drawForeground([[maybe_unused]] const Window &window) const
    {
        const auto screenPosition = getScreenPosition();
        const auto screenSize = getScreenSize();
        const auto rect = raylib::Rectangle(
            screenPosition.x,
            screenPosition.y,
            screenSize.x,
            screenSize.y
        );
        const float textureScale = size / 512.0f * _map.getScale();

        if (_structure != nullptr) {
            const auto &texture = _structure->getSprite();

            texture.Draw(
                screenPosition,
                0.0f,
                textureScale,
                raylib::Color::White()
            );
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

    bool Tile::hasStructure() const
    {
        if (_linkedTile != nullptr) {
            return _linkedTile->hasStructure();
        }
        return _structure != nullptr;
    }

    Structure::IStructure &Tile::getStructure() const
    {
        if (_linkedTile != nullptr) {
            return _linkedTile->getStructure();
        }
        return *_structure;
    }

    void Tile::setStructure(const std::shared_ptr<Structure::IStructure> &structure)
    {
        if (_linkedTile != nullptr) {
            _linkedTile->setStructure(structure);
            return;
        }

        const auto self = _map.getTile(_position);

        _structure = structure;

        if (_structure == nullptr) {
            return;
        }
        for (int x = 0; x < static_cast<int>(_structure->getSize().x); x++) {
            for (int y = 0; y < static_cast<int>(_structure->getSize().y); y++) {
                const auto neighborTile = _map.getTile(
                    raylib::Vector2(
                        _position.x + static_cast<float>(x),
                        _position.y + static_cast<float>(y)
                    )
                );

                if (neighborTile == self) {
                    continue;
                }
                neighborTile->setLinkedTile(self);
            }
        }
    }

    bool Tile::isEmpty() // NOLINT(*-no-recursion)
    {
        if (_linkedTile != nullptr) {
            if (_linkedTile->isEmpty()) {
                _linkedTile = nullptr;
                return true;
            }
            return false;
        }
        return _structure == nullptr;
    }

    std::shared_ptr<Tile> Tile::getLinkedTile() const
    {
        return _linkedTile;
    }

    void Tile::setLinkedTile(const std::shared_ptr<Tile> &linkedTile)
    {
        assert(linkedTile.get() != this);
        _linkedTile = linkedTile;
    }
} // game
