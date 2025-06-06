//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef TILE_HPP
    #define TILE_HPP

    #include <Rectangle.hpp>

    #include "Window.hpp"
#include "Structures/Abstracts/IStructure.hpp"

namespace game {
    class Map;

    class Tile {
        Map &_map;
        raylib::Vector2 _position;
        bool _hovered;
        std::unique_ptr<Structure::IStructure> _structure;

    public:
        static constexpr float size = 96.0f;

        explicit Tile(Map &map, raylib::Vector2 position);

        void draw(Window &window) const;

        [[nodiscard]] raylib::Vector2 getPosition() const;
        [[nodiscard]] raylib::Vector2 getScreenPosition() const;

        [[nodiscard]] raylib::Vector2 getSize() const;
        [[nodiscard]] raylib::Vector2 getScreenSize() const;

        [[nodiscard]] raylib::Rectangle getBounds() const;
        [[nodiscard]] raylib::Rectangle getScreenBounds() const;

        [[nodiscard]] bool isHovered() const;
        void setHovered(bool hovered);

        [[nodiscard]] bool hasStructure() const;
        [[nodiscard]] Structure::IStructure &getStructure() const;
        void setStructure(std::unique_ptr<Structure::IStructure> structure);

        float getTextureScaleFactor(const raylib::Texture &texture) const;
    };
} // game

#endif //TILE_HPP
