//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef GAME_HPP
    #define GAME_HPP

    #include <memory>
    #include <raylib-cpp.hpp>

    #include "Map.hpp"
    #include "Window.hpp"
    #include "ResourceManager.hpp"

namespace game
{
    class Game
    {
        std::unique_ptr<Window> _window;
        std::unique_ptr<Map> _map;
        std::unique_ptr<ResourceManager> _resourceManager;

        // --- Input ---
        bool _isMouseInWindow;
        raylib::Vector2 _mousePosition;
        raylib::Vector2 _lastMousePosition;
        raylib::Vector2 _mouseDelta;
        bool _mouseButtonLeftPressed;
        bool _mouseButtonMiddlePressed;
        bool _mouseButtonRightPressed;
        raylib::Vector2 _mouseScrollDelta;

    public:
        explicit Game(raylib::Vector2 windowSize);

        void handleInput();
        void update();
        void draw() const;

        [[nodiscard]] bool isRunning() const;
    };
} // game

#endif //GAME_HPP
