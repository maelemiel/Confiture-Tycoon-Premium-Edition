//
// Created by Charles Mahoudeau on 6/6/25.
//

#include <raylib-cpp.hpp>

#include "Window.hpp"

namespace game {
    Window::Window(raylib::Vector2 size)
    {
        _window = std::make_unique<raylib::Window>(
            size.x,
            size.y,
            "Idle Jeuconfiture Tycoon",
            FLAG_WINDOW_RESIZABLE
        );
        _window->SetTargetFPS(120);
        _window->SetExitKey(KEY_NULL);
        _isOpen = true;
    }

    bool Window::isOpen()
    {
        if (!_isOpen) {
            return false;
        }
        _isOpen = !_window->ShouldClose();
        return _isOpen;
    }

    raylib::Window &Window::getRaylibWindow() const
    {
        return *_window;
    }
} // game
