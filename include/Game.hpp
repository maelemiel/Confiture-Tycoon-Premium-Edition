//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef GAME_HPP
    #define GAME_HPP

    #include <memory>
    #include <raylib-cpp.hpp>

    #include "Map.hpp"
    #include "Ui.hpp"
    #include "Window.hpp"

namespace game
{
    class Game
    {
        std::unique_ptr<Window> _window;
        std::unique_ptr<Map> _map;

        // --- Input ---
        bool _isMouseInWindow;
        raylib::Vector2 _mousePosition;
        raylib::Vector2 _lastMousePosition;
        raylib::Vector2 _mouseDelta;
        bool _mouseButtonLeftPressed;
        bool _mouseButtonMiddlePressed;
        bool _mouseButtonRightPressed;
        raylib::Vector2 _mouseScrollDelta;
        // Classes
        UI _ui;

    public:
        explicit Game(raylib::Vector2 windowSize);

        void handleInput();
        void update();
        void draw() const;


        [[nodiscard]] bool isRunning() const;
    };
} // game

#endif //GAME_HPP
