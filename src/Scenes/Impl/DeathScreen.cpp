//
// Created by esteban on 6/7/25.
//

#include "DeathScreen.hpp"

#include "Game.hpp"
#include "Rectangle.hpp"

namespace game::scene {
    float DeathScreen::_mapRange(const float value, const float inMin,
        const float inMax, const float outMin, const float outMax)
    {
        return (value - inMin) / (inMax - inMin) * (outMax - outMin) + outMin;
    }

    DeathScreen::DeathScreen(Game &game) :
        AScene(game),
        _deathTexture("assets/death_screen.png"),
        _seconds(0.0f)
    {}

    void DeathScreen::update(const float dt)
    {
        _seconds += dt;
        if (_seconds >= 10.0f) {
            printf("jsp");
        }
    }

    float DeathScreen::_getScale() const
    {
        return _mapRange(_seconds, 0.0f, 2.7f, 0.93f, 1.0f);
    }

    void DeathScreen::draw() const
    {
        auto &game = getGame();
        auto &window = game.getWindow();
        const auto windowSize = window.getSize();
        const raylib::Rectangle background = {
            200,
            0,
            windowSize.x,
            windowSize.y
        };
        const auto gradientBeginColor = raylib::Color(255, 189, 223);
        const auto gradientEndColor = raylib::Color(255, 200, 230);
        const auto position = raylib::Vector2(
            0, 0);
        background.DrawGradientV(gradientBeginColor, gradientEndColor);
        _deathTexture.Draw(
            position,
            0.0f,
            1.8
        );
    }
}
