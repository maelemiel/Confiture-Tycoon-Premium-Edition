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

        // --- Input ---
        bool m_isMouseInWindow;
        raylib::Vector2 m_mousePosition;
        raylib::Vector2 m_lastMousePosition;
        raylib::Vector2 m_mouseDelta;
        bool m_mouseButtonLeftPressed;
        bool m_mouseButtonMiddlePressed;
        bool m_mouseButtonRightPressed;
        raylib::Vector2 m_mouseScrollDelta;

    public:
        explicit Game(raylib::Vector2 windowSize);

        void handleInput();
        void update();
        void draw() const;

        [[nodiscard]] bool isRunning() const;
    };
} // game

#endif //GAME_HPP
