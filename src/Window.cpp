//
// Created by Charles Mahoudeau on 6/6/25.
//

#include <raylib-cpp.hpp>

#include "Window.hpp"

namespace game {
    Window::Window(raylib::Vector2 size)
    {
        m_window = std::make_unique<raylib::Window>(
            size.x,
            size.y
        );
        m_window->SetTargetFPS(120);
        raylib::Window::SetExitKey(KEY_NULL);
        m_isOpen = true;
    }

    bool Window::isOpen()
    {
        if (!m_isOpen) {
            return false;
        }
        m_isOpen = !raylib::Window::ShouldClose();
        return m_isOpen;
    }

    raylib::Window &Window::getRaylibWindow() const
    {
        return *m_window;
    }
} // game
