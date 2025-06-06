//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Map.hpp"

namespace game {
    Map::Map(const raylib::Vector2 size) : m_size(size)
    {
        createTiles();
    }

    void Map::createTiles()
    {
        for (int x = 0; x < static_cast<int>(m_size.x); x++) {
            for (int y = 0; y < static_cast<int>(m_size.y); y++) {
                m_tiles.push_back(
                    std::make_unique<Tile>(
                        *this,
                        raylib::Vector2(
                            static_cast<float>(x),
                            static_cast<float>(y)
                        )
                    )
                );
            }
        }
    }

    void Map::draw(Window &window) const
    {
        for (const auto &tile : m_tiles) {
            tile->draw(window);
        }
    }
} // game
