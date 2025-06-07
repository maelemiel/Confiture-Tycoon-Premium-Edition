//
// Created by Charles Mahoudeau on 6/7/25.
//

#include "Splashscreen.hpp"

#include "Game.hpp"

namespace game::scene {
    float Splashscreen::_mapRange(const float value, const float inMin,
        const float inMax, const float outMin, const float outMax)
    {
        return (value - inMin) / (inMax - inMin) * (outMax - outMin) + outMin;
    }

    unsigned char Splashscreen::_getOpacity() const
    {
        if (_seconds < 1.0f) {
            return static_cast<unsigned char>(255.0f * _seconds);
        }
        return static_cast<unsigned char>(255.0f * std::clamp(2.3f - _seconds, 0.0f, 1.0f));
    }

    float Splashscreen::_getScale() const
    {
        return _mapRange(_seconds, 0.0f, 2.7f, 0.93f, 1.0f);
    }

    Splashscreen::Splashscreen(Game &game) :
        AScene(game),
        _splashTexture("assets/splashscreen.png"),
        _seconds(0.0f)
    {}

    void Splashscreen::update(const float dt)
    {
        _seconds += dt;
        if (_seconds >= 2.7f) {
            auto &game = getGame();

            game.setScene("main");
        }
    }

    void Splashscreen::draw() const
    {
        auto &game = getGame();
        auto &window = game.getWindow();
        const auto windowSize = window.getSize();
        const raylib::Rectangle background = {
            0,
            0,
            windowSize.x,
            windowSize.y
        };
        const auto gradientBeginColor = raylib::Color(255, 189, 223);
        const auto gradientEndColor = raylib::Color(255, 200, 230);
        auto scale = _getScale();
        const auto position = raylib::Vector2(
            windowSize.x * 0.5f - static_cast<float>(_splashTexture.width) * 0.5f * scale,
            windowSize.y * 0.5f - static_cast<float>(_splashTexture.height) * 0.5f * scale
        );
        const auto tintColor = raylib::Color(255, 255, 255, _getOpacity());

        background.DrawGradientV(gradientBeginColor, gradientEndColor);
        _splashTexture.Draw(
            position,
            0.0f,
            scale,
            tintColor
        );
    }
} // game::scene
