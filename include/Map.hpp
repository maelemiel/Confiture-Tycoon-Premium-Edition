//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef MAP_HPP
    #define MAP_HPP

    #include <list>
    #include <raylib-cpp.hpp>

    #include "Tile.hpp"

namespace game {
    class Map {
        raylib::Vector2 m_size;
        std::pmr::list<std::unique_ptr<Tile>> m_tiles;

        void createTiles();

    public:
        explicit Map(raylib::Vector2 size);

        void draw(Window &window) const;
    };
} // game

#endif //MAP_HPP
