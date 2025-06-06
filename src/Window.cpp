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
        _texture = std::make_unique<raylib::RenderTexture>(
            size.x,
            size.y
        );
        _window->SetTargetFPS(120);
        _window->SetExitKey(KEY_NULL);
        _isOpen = true;
    }

    void Window::beginDraw() const
    {
        _texture->BeginMode();
    }

    void Window::endDraw() const
    {
        const auto sourceRect = raylib::Rectangle(
            0,
            0,
            static_cast<float>(_texture->GetTexture().width),
            static_cast<float>(-_texture->GetTexture().height)
        );
        const auto destRect = raylib::Rectangle(
            0,
            0,
            static_cast<float>(raylib::Window::GetWidth()),
            static_cast<float>(raylib::Window::GetHeight())
        );

        _texture->EndMode();
        _window->BeginDrawing();
        _texture->GetTexture().Draw(
            sourceRect,
            destRect,
            raylib::Vector2(0, 0),
            0.0f,
            raylib::Color::White()
        );
        _window->EndDrawing();
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Window::clear(const raylib::Color color) const // NOLINT(*-convert-member-functions-to-static)
    {
        ClearBackground(color);
    }

    bool Window::isOpen()
    {
        if (!_isOpen) {
            return false;
        }
        _isOpen = !_window->ShouldClose();
        return _isOpen;
    }

    raylib::Vector2 Window::getMousePosition() const
    {
        const auto xScale =
            static_cast<float>(_texture->GetTexture().width) /
                raylib::Window::GetSize().x;
        const auto yScale =
            static_cast<float>(_texture->GetTexture().height) /
                raylib::Window::GetSize().y;

        return raylib::Vector2(
            GetMousePosition().x * xScale,
            GetMousePosition().y * yScale
        );
    }

    raylib::Window &Window::getRaylibWindow() const
    {
        return *_window;
    }
} // game
