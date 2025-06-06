//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef GAME_HPP
    #define GAME_HPP

    #include <raylib-cpp.hpp>

    #include "Map.hpp"
    #include "Window.hpp"
    #include "UI/UI.hpp"

namespace game
{
    class Game
    {
        Window _window;
        Map _map;

        // --- Input ---
        bool _isMouseInWindow;
        raylib::Vector2 _mousePosition;
        raylib::Vector2 _lastMousePosition;
        raylib::Vector2 _mouseDelta;
        bool _mouseButtonLeftDown;
        bool _mouseButtonMiddleDown;
        bool _mouseButtonRightDown;
        bool _mouseButtonLeftPressed;
        bool _mouseButtonMiddlePressed;
        bool _mouseButtonRightPressed;
        bool _mouseButtonLeftReleased;
        bool _mouseButtonMiddleReleased;
        bool _mouseButtonRightReleased;
        raylib::Vector2 _mouseScrollDelta;
        // Classes
        UI _ui;

    public:
        explicit Game(raylib::Vector2 windowSize);

        void handleInput();
        void update();
        void draw() const;


        [[nodiscard]] bool isRunning();
    };
} // game

#endif //GAME_HPP
