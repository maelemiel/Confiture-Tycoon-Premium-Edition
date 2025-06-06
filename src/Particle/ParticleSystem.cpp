//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "ParticleSystem.hpp"

namespace game::particle
{
    static long long getRandomSeed()
    {
        auto randomDevice = std::random_device();
        auto distribution = std::uniform_int_distribution<long long>();

        return distribution(randomDevice);
    }

    ParticleSystem::ParticleSystem(const Camera &camera) :
        ParticleSystem(camera, raylib::Vector2(0, 0))
    {}

    ParticleSystem::ParticleSystem(const Camera &camera,
        const raylib::Vector2 position) :
        _camera(camera), _position(position), _minLifetime(0),
        _maxLifetime(100), _randomGenerator(getRandomSeed())
    {}

    void ParticleSystem::_computeDistributions()
    {
        _xVelocityDistribution = std::uniform_real_distribution(
            _minVelocity.x,
            _maxVelocity.x
        );
        _yVelocityDistribution = std::uniform_real_distribution(
            _minVelocity.y,
            _maxVelocity.y
        );
        _lifetimeDistribution = std::uniform_int_distribution(
            _minLifetime,
            _maxLifetime
        );
        _colorDistribution = std::uniform_real_distribution(0.0f, 1.0f);
        _renderDistanceDistribution = std::uniform_real_distribution(
            _camera.getMinZoom(),
            _camera.getMaxZoom()
        );
    }

    raylib::Vector2 ParticleSystem::_getRandomVelocity()
    {
        return {
            _xVelocityDistribution(_randomGenerator),
            _yVelocityDistribution(_randomGenerator)
        };
    }

    long long ParticleSystem::_getRandomLifetime()
    {
        return _lifetimeDistribution(_randomGenerator);
    }

    raylib::Color ParticleSystem::_getRandomColor()
    {
        const auto ratio = _colorDistribution(_randomGenerator);
        const auto rDelta = static_cast<unsigned char>(static_cast<float>(
            _maxColor.r - _minColor.r) * ratio);
        const auto gDelta = static_cast<unsigned char>(static_cast<float>(
            _maxColor.g - _minColor.g) * ratio);
        const auto bDelta = static_cast<unsigned char>(static_cast<float>(
            _maxColor.b - _minColor.b) * ratio);
        const auto aDelta = static_cast<unsigned char>(static_cast<float>(
            _maxColor.a - _minColor.a) * ratio);

        return {
            static_cast<unsigned char>(_minColor.r + rDelta),
            static_cast<unsigned char>(_minColor.g + gDelta),
            static_cast<unsigned char>(_minColor.b + bDelta),
            static_cast<unsigned char>(_minColor.a + aDelta)
        };
    }

    float ParticleSystem::_getRandomRenderDistance()
    {
        return _renderDistanceDistribution(_randomGenerator);
    }

    void ParticleSystem::update(const float dt)
    {
        _particles.emplace_front(
            *this,
            _position,
            _getRandomVelocity(),
            _getRandomLifetime(),
            _getRandomColor(),
            _getRandomRenderDistance()
        );
        for (auto &particle : _particles) {
            particle.update(dt);
        }
        _particles.remove_if([](const Particle &particle) {
            return particle.getLifetime() < 0;
        });
    }

    void ParticleSystem::draw() const
    {
        for (auto &particle : _particles) {
            particle.draw();
        }
    }

    raylib::Vector2 ParticleSystem::getPosition() const
    {
        return _position;
    }

    void ParticleSystem::setPosition(const raylib::Vector2 position)
    {
        _position = position;
    }

    void ParticleSystem::setVelocity(const raylib::Vector2 minVelocity,
        const raylib::Vector2 maxVelocity)
    {
        _minVelocity = minVelocity;
        _maxVelocity = maxVelocity;
        _computeDistributions();
    }

    void ParticleSystem::setMinVelocity(const raylib::Vector2 minVelocity)
    {
        setVelocity(minVelocity, _maxVelocity);
    }

    void ParticleSystem::setMaxVelocity(const raylib::Vector2 maxVelocity)
    {
        setVelocity(_minVelocity, maxVelocity);
    }

    void ParticleSystem::setLifetime(long long minLifetime, long long maxLifetime)
    {
        _minLifetime = minLifetime;
        _maxLifetime = maxLifetime;
        _computeDistributions();
    }

    void ParticleSystem::setMinLifetime(const long long minLifetime)
    {
        setLifetime(minLifetime, _maxLifetime);
    }

    void ParticleSystem::setMaxLifetime(const long long maxLifetime)
    {
        setLifetime(_minLifetime, maxLifetime);
    }

    const Camera &ParticleSystem::getCamera() const
    {
        return _camera;
    }

    void ParticleSystem::setColor(const raylib::Color color)
    {
        setColor(color, color);
    }

    void ParticleSystem::setColor(const raylib::Color minColor,
        const raylib::Color maxColor)
    {
        _minColor = minColor;
        _maxColor = maxColor;
        _computeDistributions();
    }

    void ParticleSystem::setMinColor(const raylib::Color minColor)
    {
        setColor(minColor, _maxColor);
    }

    void ParticleSystem::setMaxColor(const raylib::Color maxColor)
    {
        setColor(_minColor, maxColor);
    }
} // game::particle
