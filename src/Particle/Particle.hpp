//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef PARTICLE_HPP
    #define PARTICLE_HPP

    #include "raylib-cpp.hpp"

namespace game::particle
{
    class ParticleSystem;

    class Particle
    {
        ParticleSystem &_particleSystem;
        raylib::Vector2 _position;
        raylib::Vector2 _velocity;
        float _lifetime;
        raylib::Color _color;
        float _antiLag;

    public:
        Particle(
            ParticleSystem &particleSystem,
            raylib::Vector2 position,
            raylib::Vector2 velocity,
            float lifetime,
            raylib::Color color,
            float antiLag = 1.0f
        );

        void update(float dt);
        void draw() const;

        [[nodiscard]] float getLifetime() const;
    };
} // game::particle

#endif //PARTICLE_HPP
