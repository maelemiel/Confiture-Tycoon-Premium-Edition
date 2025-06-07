//
// Created by Charles Mahoudeau on 6/6/25.
//

#include <raylib-cpp.hpp>

#include "Window.hpp"

namespace game {
    Window::Window(const raylib::Vector2 size) :
        _window(
            static_cast<int>(size.x),
            static_cast<int>(size.y),
            "./Idle Jeuconfiture Tycoon (Premium Edition"
            " (Trial (Free))) Ultra HD (480p) Deluxe Edition (Remastered)"
            " Demo 2 - Uwunity - v69.420",
            FLAG_WINDOW_RESIZABLE
        ),
        _texture(static_cast<int>(size.x), static_cast<int>(size.y)),
        _windowIcon("assets/window_icon.png")
    {
        _window.SetTargetFPS(120);
        _window.SetExitKey(KEY_NULL);
        _window.SetIcon(_windowIcon);
        _isOpen = true;
    }

    void Window::beginDraw()
    {
        _texture.BeginMode();
    }

    void Window::endDraw()
    {
        const auto sourceRect = raylib::Rectangle(
            0,
            0,
            static_cast<float>(_texture.GetTexture().width),
            static_cast<float>(-_texture.GetTexture().height)
        );
        const auto destRect = raylib::Rectangle(
            0,
            0,
            static_cast<float>(_window.GetWidth()),
            static_cast<float>(_window.GetHeight())
        );

        _texture.EndMode();
        _window.BeginDrawing();
        _texture.GetTexture().Draw(
            sourceRect,
            destRect,
            raylib::Vector2(0, 0),
            0.0f,
            raylib::Color::White()
        );
        _window.EndDrawing();
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Window::clear(const raylib::Color color) const // NOLINT(*-convert-member-functions-to-static)
    {
        ClearBackground(color);
    }

    raylib::Vector2 Window::getSize()
    {
        const auto texture = _texture.GetTexture();

        return {
            static_cast<float>(texture.width),
            static_cast<float>(texture.height)
        };
    }

    bool Window::isOpen()
    {
        if (!_isOpen) {
            return false;
        }
        _isOpen = !_window.ShouldClose();
        return _isOpen;
    }

    raylib::Vector2 Window::getMousePosition()
    {
        const auto xScale =
            static_cast<float>(_texture.GetTexture().width) /
                _window.GetSize().x;
        const auto yScale =
            static_cast<float>(_texture.GetTexture().height) /
                _window.GetSize().y;

        const auto [x, y] = GetMousePosition();
        return {
            x * xScale,
            y * yScale
        };
    }

    raylib::Window &Window::getRaylibWindow()
    {
        return _window;
    }
} // game
