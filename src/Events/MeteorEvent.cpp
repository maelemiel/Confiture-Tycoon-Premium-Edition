#include "MeteorEvent.hpp"
#include <vector>
#include <iostream>
#include "../Structures/Abstracts/IStructure.hpp"

namespace game {

    MeteorEvent::MeteorEvent(Map& map) :
        IEvent("Meteor Strike", "A meteor is heading towards the colony!", 5.0f),
        _map(map),
        _targetTile(nullptr),
        _meteorTexture("assets/events/meteor.png"),
        _meteorWorldPos(0, 0),
        _meteorSpeed(200.0f),
        _initialYOffset(-300.0f)
    {
        if (_meteorTexture.id <= 0) {
            std::cerr << "Failed to load meteor texture: assets/events/meteor.png" << std::endl;
        }
    }

    MeteorEvent::~MeteorEvent()
    {
    }

    void MeteorEvent::start()
    {
        std::vector<std::shared_ptr<Tile>> potentialTargets;
        raylib::Vector2 mapSize = _map.getSize();
        for (int x = 0; x < static_cast<int>(mapSize.x); ++x) {
            for (int y = 0; y < static_cast<int>(mapSize.y); ++y) {
                auto tile = _map.getTile({static_cast<float>(x), static_cast<float>(y)});
                if (tile && tile->hasStructure() && tile->getLinkedTile() == nullptr) {
                    potentialTargets.push_back(tile);
                }
            }
        }

        if (potentialTargets.empty()) {
            std::cout << "MeteorEvent: No valid structures to target. Event will not run." << std::endl;
            _isActive = false;
            _elapsedTime = _duration;
            return;
        }

        _targetTile = potentialTargets[GetRandomValue(0, static_cast<int>(potentialTargets.size()) - 1)];
        
        if (!_targetTile || !_targetTile->hasStructure()) {
            std::cerr << "MeteorEvent: Selected target tile is invalid or has no structure. Event will not run." << std::endl;
            _isActive = false;
            _elapsedTime = _duration;
            return;
        }

        _isActive = true;
        _elapsedTime = 0.0f;

        Structure::IStructure& structureRef = _targetTile->getStructure();
        raylib::Vector2 structureTileSize = structureRef.getSize();
        float structureWorldWidth = structureTileSize.x * Tile::size;
        float structureWorldHeight = structureTileSize.y * Tile::size;

        raylib::Vector2 structureOriginWorldPos = {
            _targetTile->getPosition().x * Tile::size,
            _targetTile->getPosition().y * Tile::size
        };

        float targetImpactCenterX = structureOriginWorldPos.x + structureWorldWidth / 2.0f;
        float targetImpactCenterY = structureOriginWorldPos.y + structureWorldHeight / 2.0f;

        _meteorWorldPos.x = targetImpactCenterX;
        _meteorWorldPos.y = targetImpactCenterY + _initialYOffset;

    }

    void MeteorEvent::update(float deltaTime)
    {
        if (!_isActive || !_targetTile) {
            return;
        }

        _elapsedTime += deltaTime;

        float targetImpactCenterY;
        if (_targetTile->hasStructure()) {
            Structure::IStructure& structureRef = _targetTile->getStructure();
            raylib::Vector2 structureTileSize = structureRef.getSize();
            float structureWorldHeight = structureTileSize.y * Tile::size;
            targetImpactCenterY = _targetTile->getPosition().y * Tile::size + structureWorldHeight / 2.0f;
        } else {
            targetImpactCenterY = _targetTile->getPosition().y * Tile::size + (Tile::size / 2.0f);
        }
        
        _meteorWorldPos.y += _meteorSpeed * deltaTime;

        if (_meteorWorldPos.y >= targetImpactCenterY) {
            _meteorWorldPos.y = targetImpactCenterY;
            std::cout << "Meteor impacted tile (" << _targetTile->getPosition().x << ", " << _targetTile->getPosition().y << ")!" << std::endl;
            if (_targetTile->hasStructure()) {
                std::cout << "Destroying structure on impacted tile." << std::endl;
                _targetTile->setStructure(nullptr);
            } else {
                std::cout << "No structure to destroy on impacted tile." << std::endl;
            }
            _isActive = false;
            _elapsedTime = _duration;
            return;
        }

        if (_elapsedTime >= _duration) {
            _isActive = false;
            std::cout << "Meteor event timed out." << std::endl;
            if (_targetTile && _targetTile->hasStructure()) {
                std::cout << "Destroying structure at (" << _targetTile->getPosition().x << ", " << _targetTile->getPosition().y << ") due to timeout (e.g., meteor missed but caused damage)." << std::endl;
                _targetTile->setStructure(nullptr);
            }
        }
    }

    void MeteorEvent::draw([[maybe_unused]] const Window &window) const
    {
        if (!_isActive || _meteorTexture.id <= 0) {
            return;
        }

        float desiredMeteorScreenWidth = Tile::size * _map.getScale() * 2.0f;
        float textureDrawScale = desiredMeteorScreenWidth / static_cast<float>(_meteorTexture.width);

        raylib::Vector2 meteorCenterScreenPos = {
            (_map.getOffset().x + _meteorWorldPos.x) * _map.getScale(),
            (_map.getOffset().y + _meteorWorldPos.y) * _map.getScale()
        };

        float actualMeteorTextureScaledWidth = static_cast<float>(_meteorTexture.width) * textureDrawScale;
        float actualMeteorTextureScaledHeight = static_cast<float>(_meteorTexture.height) * textureDrawScale;

        raylib::Vector2 meteorTopLeftScreenPos = {
            meteorCenterScreenPos.x - actualMeteorTextureScaledWidth / 2.0f,
            meteorCenterScreenPos.y - actualMeteorTextureScaledHeight / 2.0f
        };
        
        _meteorTexture.Draw(meteorTopLeftScreenPos, 0.0f, textureDrawScale, WHITE);
    }
}
