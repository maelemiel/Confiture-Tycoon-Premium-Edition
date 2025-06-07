//
// Created by Charles Mahoudeau on 6/7/25.
//

#include "DrawerButton.hpp"

namespace game::ui {
    DrawerButton::DrawerButton(const raylib::Vector2 position, const std::string &iconPath) :
        _position(position),
        _icon(iconPath)
    {}

    void DrawerButton::update(float dt)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return;
        }

        const Rectangle rect = {
            _position.x,
            _position.y,
            static_cast<float>(_icon.GetWidth()) * scale,
            static_cast<float>(_icon.GetHeight()) * scale
        };

        if (CheckCollisionPointRec(GetMousePosition(), rect)) {
            _onClickCallback();
        }
    }

    void DrawerButton::draw() const
    {
        _icon.Draw(_position, 0.0f, 0.7f, WHITE);
    }

    void DrawerButton::setOnClickCallback(const std::function<void()> &callback)
    {
        _onClickCallback = callback;
    }
} // game::ui
