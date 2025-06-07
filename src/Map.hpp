//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef MAP_HPP
    #define MAP_HPP

    #include <list>
    #include <raylib-cpp.hpp>

    #include "Camera.hpp"
    #include "Tile.hpp"

// Forward declaration
namespace Structure {
    class IStructure;
    class AOxygenProducer;
}

namespace game {
    class Map {
        Camera &_camera;
        raylib::Vector2 _size;
        std::pmr::list<std::shared_ptr<Tile>> _tiles;
        std::shared_ptr<Tile> _hoveredTile;
        raylib::Vector2 _hoverSize;
        std::shared_ptr<Structure::IStructure> _currentStructure;

        std::shared_ptr<raylib::Texture> _grassTexture;
        std::shared_ptr<raylib::Texture> _dirtTexture;
        std::shared_ptr<raylib::Texture> _concreteTexture;

        void _createTiles();
        void _highlightTiles() const;

    public:
        explicit Map(Camera &camera, raylib::Vector2 size);

        void update(float dt) const;
        void draw(const Window &window) const;

        [[nodiscard]] raylib::Vector2 getSize() const;

        [[nodiscard]] std::pmr::list<std::shared_ptr<Tile>> getTiles() const {
            return _tiles;
        }
        [[nodiscard]] std::shared_ptr<Tile> getTile(raylib::Vector2 index) const;
        [[nodiscard]] std::shared_ptr<Tile> getTileAtWorldPosition(
            raylib::Vector2 worldPosition) const;

        void setHoveredTile(const std::shared_ptr<Tile> &tile);
        void setHoverSize(raylib::Vector2 size);
        void setCurrentStructure(const std::shared_ptr<Structure::IStructure>& structure);
        [[nodiscard]] std::list<std::shared_ptr<Tile>> getHoveredTiles() const;
        [[nodiscard]] bool areAllHoveredTilesEmpty() const;
        [[nodiscard]] bool canPlaceStructureOnHoveredTiles(const std::shared_ptr<Structure::IStructure>& structure) const;

        [[nodiscard]] std::shared_ptr<raylib::Texture> getGrassTexture() const;
        [[nodiscard]] std::shared_ptr<raylib::Texture> getDirtTexture() const;
        [[nodiscard]] std::shared_ptr<raylib::Texture> getConcreteTexture() const;

        void setOffsetToCenter();

        Camera &getCamera();
    };
} // game

#endif //MAP_HPP
