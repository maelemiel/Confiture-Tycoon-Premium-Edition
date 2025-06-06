//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef GAME_HPP
    #define GAME_HPP

    #include <memory>
    #include <raylib-cpp.hpp>

    #include "Map.hpp"
    #include "Window.hpp"

namespace game
{
    class Game
    {
        std::unique_ptr<Window> m_window;
        std::unique_ptr<Map> m_map;

    public:
        explicit Game(raylib::Vector2 windowSize);

        void update() const;

        [[nodiscard]] bool isRunning() const;
    };
} // game

#endif //GAME_HPP
