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
        raylib::Vector2 m_offset;
        float m_scale;

        void createTiles();

    public:
        explicit Map(raylib::Vector2 size);

        void draw(Window &window) const;

        [[nodiscard]] raylib::Vector2 getOffset() const;
        void setOffset(raylib::Vector2 offset);

        [[nodiscard]] float getScale() const;
        void setScale(float scale);
    };
} // game

#endif //MAP_HPP
