//
// Created by esteban on 6/7/25.
//

#ifndef DEATHSCREEN_HPP
#define DEATHSCREEN_HPP
#include "Texture.hpp"
#include "Scenes/AScene.hpp"

namespace game::scene {
    class DeathScreen final : public AScene {
        raylib::Texture _deathTexture;
        float _seconds;

        [[nodiscard]] static float _mapRange(float value, float inMin, float inMax, float outMin, float outMax) ;

    public:
        explicit DeathScreen(Game &game);

        void update(float dt) override;
        void draw() const override;
        float _getScale() const;
    };
}
#endif //DEATHSCREEN_HPP
