//
// Created by Charles Mahoudeau on 6/7/25.
//

#include "DualityBar.hpp"

#include <algorithm>

namespace game::ui {
    DualityBar::DualityBar() :
        // I fucking hate this "UI" naming convention, but it's what the original code used.
        _texture("assets/UI/duality_bar.png"), _level(0.0f) {}

    void DualityBar::update(float dt)
    {}

    void DualityBar::draw() const
    {
        constexpr auto scale = 0.3f;
        const auto xPosition = 1920.0f * 0.5f -
            static_cast<float>(_texture.width) * 0.5f * scale;
        const auto bar = raylib::Rectangle(
            1920.0f * 0.5f,
            0.0f,
            static_cast<float>(_texture.width) * 0.5f * scale,
            10.0f
        );

        _texture.Draw(raylib::Vector2(xPosition, 0.0f), 0.0f, scale);
        bar.Draw(raylib::Vector2(0.0f, 0.0f), 90.0f + 75.0f * _level, raylib::Color::Red());
    }

    void DualityBar::setLevel(const float level)
    {
        _level = std::clamp(level, -1.0f, 1.0f);
    }
} // game::ui
