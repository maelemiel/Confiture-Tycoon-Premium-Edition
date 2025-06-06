//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef TILE_HPP
    #define TILE_HPP

    #include <Rectangle.hpp>

    #include "Window.hpp"

namespace game {
    class Map;

    class Tile {
        Map &_map;
        raylib::Vector2 _position;
        bool _hovered;

    public:
        static constexpr float size = 96.0f;

        explicit Tile(Map &map, raylib::Vector2 position);

        void draw(const Window &window) const;

        [[nodiscard]] raylib::Vector2 getPosition() const;
        [[nodiscard]] raylib::Vector2 getScreenPosition() const;

        [[nodiscard]] raylib::Vector2 getSize() const;
        [[nodiscard]] raylib::Vector2 getScreenSize() const;

        [[nodiscard]] raylib::Rectangle getBounds() const;
        [[nodiscard]] raylib::Rectangle getScreenBounds() const;

        [[nodiscard]] bool isHovered() const;
        void setHovered(bool hovered);
    };
} // game

#endif //TILE_HPP
