//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef TILE_HPP
    #define TILE_HPP

    #include <Rectangle.hpp>

    #include "PerlinNoise.hpp"
    #include "Window.hpp"
    #include "Particle/ParticleSystem.hpp"
    #include "Structures/Abstracts/IStructure.hpp"

namespace game {
    class Map;

    class Tile {
        Map &_map;
        raylib::Vector2 _position;
        std::shared_ptr<Structure::IStructure> _structure;
        std::shared_ptr<Tile> _linkedTile;
        std::shared_ptr<raylib::Texture> _backgroundTexture;
        std::unique_ptr<particle::ParticleSystem> _particleSystem;
        bool _shouldRemoveParticleSystem;
        
        // Pollution system
        int _pollutionLevel;
        raylib::Color _tileColor;

        [[nodiscard]] std::unique_ptr<particle::ParticleSystem>
            _getBadParticleSystem() const;
        [[nodiscard]] std::unique_ptr<particle::ParticleSystem>
            _getGoodParticleSystem() const;

        void _onStructureChange();

    public:
        static constexpr float size = 64.0f;

        explicit Tile(Map &map, raylib::Vector2 position, siv::PerlinNoise::value_type noise);

        void update(float dt);
        void drawBackground(const Window &window) const;
        void drawForeground(const Window &window) const;

        [[nodiscard]] raylib::Vector2 getPosition() const;
        [[nodiscard]] raylib::Vector2 getScreenPosition() const;

        [[nodiscard]] raylib::Vector2 getSize() const;
        [[nodiscard]] raylib::Vector2 getScreenSize() const;

        [[nodiscard]] raylib::Rectangle getBounds() const;
        [[nodiscard]] raylib::Rectangle getScreenBounds() const;

        [[nodiscard]] bool hasStructure() const;
        [[nodiscard]] Structure::IStructure &getStructure() const;
        [[nodiscard]] std::shared_ptr<Structure::IStructure> getStructureSharedPtr() const;

        void setStructure(const std::shared_ptr<Structure::IStructure> &structure);

        [[nodiscard]] bool isEmpty();

        [[nodiscard]] std::shared_ptr<Tile> getLinkedTile() const;
        void setLinkedTile(const std::shared_ptr<Tile> &linkedTile);
        
        // Pollution management
        [[nodiscard]] int getPollutionLevel() const;
        void setPollutionLevel(int level);
        void addPollution(int amount);
        [[nodiscard]] bool isPolluted() const;
        [[nodiscard]] bool canPlaceOxygenProducer() const;
        void updateTileColor();
        void propagatePollutionToNeighbors();
    };
} // game

#endif //TILE_HPP
