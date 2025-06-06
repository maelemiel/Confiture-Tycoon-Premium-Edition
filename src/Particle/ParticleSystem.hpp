//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef PARTICLESYSTEM_HPP
    #define PARTICLESYSTEM_HPP

    #include <list>
#include <random>

    #include "Camera.hpp"
    #include "Particle.hpp"
    #include "raylib-cpp.hpp"

namespace game::particle
{
    class ParticleSystem
    {
        const Camera &_camera;
        raylib::Vector2 _position;
        std::pmr::list<Particle> _particles;
        raylib::Vector2 _minVelocity;
        raylib::Vector2 _maxVelocity;
        long long _minLifetime;
        long long _maxLifetime;
        raylib::Color _minColor;
        raylib::Color _maxColor;

        // --- Random ---
        std::default_random_engine _randomGenerator;
        std::uniform_real_distribution<float> _xVelocityDistribution;
        std::uniform_real_distribution<float> _yVelocityDistribution;
        std::uniform_int_distribution<long long> _lifetimeDistribution;
        std::uniform_real_distribution<float> _colorDistribution;
        std::uniform_real_distribution<float> _renderDistanceDistribution;

        void _computeDistributions();

        [[nodiscard]] raylib::Vector2 _getRandomVelocity();
        [[nodiscard]] long long _getRandomLifetime();
        [[nodiscard]] raylib::Color _getRandomColor();
        [[nodiscard]] float _getRandomRenderDistance();

    public:
        explicit ParticleSystem(const Camera &camera);
        ParticleSystem(const Camera &camera, raylib::Vector2 position);

        void update(float dt);
        void draw() const;

        [[nodiscard]] raylib::Vector2 getPosition() const;
        void setPosition(raylib::Vector2 position);

        void setVelocity(raylib::Vector2 minVelocity,
            raylib::Vector2 maxVelocity);
        void setMinVelocity(raylib::Vector2 minVelocity);
        void setMaxVelocity(raylib::Vector2 maxVelocity);

        void setLifetime(long long minLifetime, long long maxLifetime);
        void setMinLifetime(long long minLifetime);
        void setMaxLifetime(long long maxLifetime);

        void setColor(raylib::Color color);
        void setColor(raylib::Color minColor, raylib::Color maxColor);
        void setMinColor(raylib::Color minColor);
        void setMaxColor(raylib::Color maxColor);

        [[nodiscard]] const Camera &getCamera() const;
    };
} // game::particle

#endif //PARTICLESYSTEM_HPP
