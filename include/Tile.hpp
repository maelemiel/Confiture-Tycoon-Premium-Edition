//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef TILE_HPP
    #define TILE_HPP

    #include "Window.hpp"

namespace game {
    class Map;

    class Tile {
        Map &m_map;
        raylib::Vector2 m_position;

    public:
        static constexpr float size = 96.0f;

        explicit Tile(Map &map, raylib::Vector2 position);

        void draw(Window &window) const;
    };
} // game

#endif //TILE_HPP
