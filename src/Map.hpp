//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef MAP_HPP
    #define MAP_HPP

    #include <list>
#include <optional>
    #include <raylib-cpp.hpp>

    #include "Camera.hpp"
    #include "Tile.hpp"

namespace game {
    class Map {
        Camera &_camera;
        raylib::Vector2 _size;
        std::pmr::list<std::shared_ptr<Tile>> _tiles;
        std::shared_ptr<Tile> _hoveredTile;
        raylib::Vector2 _hoverSize;

        raylib::Texture _grassTexture;

        void createTiles();
        void highlightTiles() const;

    public:
        explicit Map(Camera &camera, raylib::Vector2 size);

        void draw(const Window &window) const;

        [[nodiscard]] std::shared_ptr<Tile> getTile(raylib::Vector2 index) const;
        [[nodiscard]] std::shared_ptr<Tile> getTileAtWorldPosition(
            raylib::Vector2 worldPosition) const;

        void setHoveredTile(const std::shared_ptr<Tile> &tile);
        void setHoverSize(raylib::Vector2 size);
        [[nodiscard]] std::list<std::shared_ptr<Tile>> getHoveredTiles() const;
        [[nodiscard]] bool areAllHoveredTilesEmpty() const;

        [[nodiscard]] const raylib::Texture &getGrassTexture() const;

        void setOffsetToCenter();

        Camera &getCamera();
    };
} // game

#endif //MAP_HPP
