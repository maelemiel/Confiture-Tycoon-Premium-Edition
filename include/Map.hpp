//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef MAP_HPP
    #define MAP_HPP

    #include <list>
#include <optional>
    #include <raylib-cpp.hpp>

    #include "Tile.hpp"

namespace game {
    class Map {
        raylib::Vector2 m_size;
        std::pmr::list<std::shared_ptr<Tile>> m_tiles;
        raylib::Vector2 m_offset;
        float m_scale;
        std::optional<std::shared_ptr<Tile>> m_hoveredTile;

        void createTiles();

    public:
        explicit Map(raylib::Vector2 size);

        void draw(Window &window) const;

        [[nodiscard]] raylib::Vector2 getOffset() const;
        void setOffset(raylib::Vector2 offset);

        [[nodiscard]] float getScale() const;
        void setScale(float scale);

        [[nodiscard]] raylib::Vector2 getScreenPositionAsWorldPosition(
            raylib::Vector2 mousePosition) const;

        [[nodiscard]] std::optional<std::shared_ptr<Tile>>
            getTileAtWorldPosition(raylib::Vector2 worldPosition) const;

        void setHoveredTile(const std::shared_ptr<Tile> &tile) const;
    };
} // game

#endif //MAP_HPP
