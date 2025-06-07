//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Tile.hpp"

#include <cassert>
#include <iostream>
#include <Rectangle.hpp>

#include "PerlinNoise.hpp"
#include "Map.hpp"

namespace game {
    std::unique_ptr<particle::ParticleSystem>
        Tile::_getBadParticleSystem() const
    {
        auto particleSystem = std::make_unique<particle::ParticleSystem>(
            _map.getCamera(),
            _position * getSize() + getSize() * 0.5f
        );
        particleSystem->setVelocity(
            raylib::Vector2(-10.0f, -80.0f),
            raylib::Vector2(10.0f, -10.0f)
        );
        particleSystem->setLifetime(1.0f, 3.0f);
        particleSystem->setColor(
            raylib::Color::LightGray(),
            raylib::Color::DarkGray()
        );
        particleSystem->setSize(32.0f, 64.0f);

        return particleSystem;
    }

    std::unique_ptr<particle::ParticleSystem>
        Tile::_getGoodParticleSystem() const
    {
        auto particleSystem = std::make_unique<particle::ParticleSystem>(
            _map.getCamera(),
            _position * getSize() + getSize() * 0.5f
        );
        particleSystem->setVelocity(
            raylib::Vector2(-30.0f, -30.0f),
            raylib::Vector2(30.0f, 30.0f)
        );
        particleSystem->setLifetime(1.0f, 3.0f);
        particleSystem->setColor(
            raylib::Color::Yellow(),
            raylib::Color::Orange()
        );
        particleSystem->setSize(8.0f, 12.0f);

        return particleSystem;
    }

    void Tile::_onStructureChange()
    {
        if (_structure != nullptr && _structure->getPollutionEffect() != 0) {
            if (_structure->getPollutionEffect() > 0) {
                _particleSystem = _getBadParticleSystem();
            } else {
                _particleSystem = _getGoodParticleSystem();
            }
            _particleSystem->setSpawning(true);
            _shouldRemoveParticleSystem = false;
            return;
        }
        _shouldRemoveParticleSystem = true;
        if (_particleSystem != nullptr) {
            _particleSystem->setSpawning(false);
        }
    }

    Tile::Tile(Map &map, const raylib::Vector2 position, siv::PerlinNoise::value_type noise) : _map(map),
        _position(position), _pollutionLevel(0), _tileColor(raylib::Color::White())
    {
        if (noise > 0.5f) {
            _backgroundTexture = _map.getGrassTexture();
        } else {
            _backgroundTexture = _map.getDirtTexture();
        }

        _structure = nullptr;
        _linkedTile = nullptr;
        updateTileColor();
    }

    void Tile::update(const float dt)
    {
        if (_particleSystem != nullptr) {
            _particleSystem->update(dt);
            if (_shouldRemoveParticleSystem) {
                if (_particleSystem->getParticlesCount() == 0) {
                    _particleSystem = nullptr;
                    _shouldRemoveParticleSystem = false;
                }
            }
        }
    }

    void Tile::drawBackground([[maybe_unused]] const Window &window) const
    {
        const auto screenPosition = getScreenPosition();
        const float textureScale = _map.getCamera().getScaledValue(size / 512.0f);

        // Utiliser la couleur de pollution de cette tuile (déjà propagée correctement)
        raylib::Color colorToUse = _tileColor;

        if (_backgroundTexture != nullptr) {
            _backgroundTexture->Draw(
                screenPosition,
                0.0f,
                textureScale,
                colorToUse  // Appliquer la couleur de pollution de cette tuile
            );
        } else {
            raylib::Rectangle(
                screenPosition.x,
                screenPosition.y,
                getScreenSize().x,
                getScreenSize().y
            ).Draw(colorToUse);  // Appliquer la couleur de pollution de cette tuile
        }
    }

    void Tile::drawForeground([[maybe_unused]] const Window &window) const
    {
        const auto screenPosition = getScreenPosition();
        const float textureScale = _map.getCamera().getScaledValue(size / 512.0f);

        if (_particleSystem != nullptr) {
            _particleSystem->draw();
        }
        if (_structure != nullptr) {
            const auto &texture = _structure->getSprite();

            texture.Draw(
                screenPosition,
                0.0f,
                textureScale,
                raylib::Color::White()  // Garder la couleur normale du bâtiment
            );
        }
    }

    raylib::Vector2 Tile::getPosition() const
    {
        return _position;
    }

    raylib::Vector2 Tile::getScreenPosition() const
    {
        return _map.getCamera().getWorldPositionAsScreenPosition(raylib::Vector2(
            _position.x * size,
            _position.y * size
        ));
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
            _map.getCamera().getScaledValue(size),
            _map.getCamera().getScaledValue(size)
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

    std::shared_ptr<Structure::IStructure> Tile::getStructureSharedPtr() const
    {
        if (_linkedTile != nullptr) {
            return _linkedTile->getStructureSharedPtr();
        }
        return _structure;
    }

    void Tile::setStructure(const std::shared_ptr<Structure::IStructure> &structure)
    {
        if (_linkedTile != nullptr) {
            _linkedTile->setStructure(structure);
            return;
        }

        const auto self = _map.getTile(_position);

        _structure = structure;
        _onStructureChange();

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
                neighborTile->_onStructureChange();
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

    int Tile::getPollutionLevel() const
    {
        return _pollutionLevel;
    }

    void Tile::setPollutionLevel(int level)
    {
        _pollutionLevel = std::max(0, level);
        updateTileColor();
        
        // Si cette tuile a une structure, propager la pollution aux tuiles liées
        if (_structure != nullptr) {
            const auto self = _map.getTile(_position);
            for (int x = 0; x < static_cast<int>(_structure->getSize().x); x++) {
                for (int y = 0; y < static_cast<int>(_structure->getSize().y); y++) {
                    const auto neighborTile = _map.getTile(
                        raylib::Vector2(
                            _position.x + static_cast<float>(x),
                            _position.y + static_cast<float>(y)
                        )
                    );

                    if (neighborTile != nullptr && neighborTile != self) {
                        neighborTile->_pollutionLevel = _pollutionLevel;
                        neighborTile->updateTileColor();
                    }
                }
            }
        }
        
        // Propager la pollution aux tuiles voisines
        propagatePollutionToNeighbors();
    }

    void Tile::addPollution(int amount)
    {
        _pollutionLevel += amount;
        if (_pollutionLevel < 0) {
            _pollutionLevel = 0;
        }
        updateTileColor();
        
        // Si cette tuile a une structure, propager la pollution aux tuiles liées
        if (_structure != nullptr) {
            const auto self = _map.getTile(_position);
            for (int x = 0; x < static_cast<int>(_structure->getSize().x); x++) {
                for (int y = 0; y < static_cast<int>(_structure->getSize().y); y++) {
                    const auto neighborTile = _map.getTile(
                        raylib::Vector2(
                            _position.x + static_cast<float>(x),
                            _position.y + static_cast<float>(y)
                        )
                    );

                    if (neighborTile != nullptr && neighborTile != self) {
                        neighborTile->_pollutionLevel = _pollutionLevel;
                        neighborTile->updateTileColor();
                    }
                }
            }
        }
        
        // Propager la pollution aux tuiles voisines
        propagatePollutionToNeighbors();
    }

    bool Tile::isPolluted() const
    {
        return _pollutionLevel > 10; // Seuil de pollution critique
    }

    bool Tile::canPlaceOxygenProducer() const
    {
        // Cannot place trees on polluted soil (marron clair et plus)
        if (_pollutionLevel > 5) {
            return false;
        }
        // Check if tile is empty without modifying state
        if (_linkedTile != nullptr) {
            return _linkedTile->canPlaceOxygenProducer();
        }
        return _structure == nullptr;
    }

    void Tile::updateTileColor()
    {
        if (_pollutionLevel <= 0) {
            _tileColor = raylib::Color::White(); // Normal
        } else if (_pollutionLevel <= 5) {
            _tileColor = raylib::Color(255, 250, 200, 255); // Légèrement jaune
        } else if (_pollutionLevel <= 10) {
            _tileColor = raylib::Color(255, 200, 150, 255); // Orange clair
        } else if (_pollutionLevel <= 20) {
            _tileColor = raylib::Color(200, 150, 100, 255); // Marron clair
        } else {
            _tileColor = raylib::Color(150, 100, 50, 255); // Marron foncé - très pollué
        }
    }

    void Tile::propagatePollutionToNeighbors()
    {
        if (_pollutionLevel <= 5) {
            return; // Pas assez de pollution pour se propager
        }

        // Propager la pollution aux 8 tuiles voisines
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) {
                    continue; // Skip la tuile actuelle
                }

                const auto neighborTile = _map.getTile(
                    raylib::Vector2(
                        _position.x + static_cast<float>(dx),
                        _position.y + static_cast<float>(dy)
                    )
                );

                if (neighborTile == nullptr) {
                    continue; // Tuile hors limites
                }

                // Calculer le niveau de pollution à propager (diminué)
                int propagatedPollution = _pollutionLevel - 5;
                if (propagatedPollution > 0) {
                    // Appliquer seulement si la pollution propagée est plus élevée
                    if (neighborTile->_pollutionLevel < propagatedPollution) {
                        neighborTile->_pollutionLevel = propagatedPollution;
                        neighborTile->updateTileColor();
                    }
                }
            }
        }
    }
} // game
