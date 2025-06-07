//
// Created by Charles Mahoudeau on 6/7/25.
//

#ifndef SPLASHSCREEN_HPP
    #define SPLASHSCREEN_HPP
#include "raylib-cpp.hpp"
#include "Scenes/AScene.hpp"

namespace game::scene
{
    class Splashscreen final : public AScene {
        raylib::Texture _splashTexture;
        float _seconds;

        [[nodiscard]] static float _mapRange(float value, float inMin, float inMax, float outMin, float outMax) ;
        [[nodiscard]] unsigned char _getOpacity() const;
        [[nodiscard]] float _getScale() const;

    public:
        explicit Splashscreen(Game &game);

        void update(float dt) override;
        void draw() const override;
    };
} // game::scene

#endif //SPLASHSCREEN_HPP
