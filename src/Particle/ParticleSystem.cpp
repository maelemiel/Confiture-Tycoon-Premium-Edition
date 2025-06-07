//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "ParticleSystem.hpp"

#include <iostream>

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
        _camera(camera), _position(position), _isSpawning(true),
        _minLifetime(), _maxLifetime(), _minSize(), _maxSize(),
        _randomGenerator(getRandomSeed())
    {
        _renderDistanceDistribution = std::uniform_real_distribution(
            _camera.getMinZoom(),
            _camera.getMaxZoom()
        );

        setVelocity(
            raylib::Vector2::Zero(),
            raylib::Vector2::One()
        );
        setLifetime(
            0.0f,
            1.0f
        );
        setColor(
            raylib::Color::Black(),
            raylib::Color::White()
        );
        setSize(
            0.0f,
            1.0f
        );
    }

    raylib::Vector2 ParticleSystem::_getRandomVelocity()
    {
        return {
            _xVelocityDistribution(_randomGenerator),
            _yVelocityDistribution(_randomGenerator)
        };
    }

    float ParticleSystem::_getRandomLifetime()
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

    float ParticleSystem::_getRandomSize()
    {
        return _sizeDistribution(_randomGenerator);
    }

    float ParticleSystem::_getRandomRenderDistance()
    {
        return _renderDistanceDistribution(_randomGenerator);
    }

    void ParticleSystem::update(const float dt)
    {
        if (_isSpawning) {
            _particles.emplace_front(
                *this,
                _position,
                _getRandomVelocity(),
                _getRandomLifetime(),
                _getRandomColor(),
                _getRandomSize(),
                _getRandomRenderDistance()
            );
        }
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

    size_t ParticleSystem::getParticlesCount() const
    {
        return _particles.size();
    }

    bool ParticleSystem::isSpawning() const
    {
        return _isSpawning;
    }

    void ParticleSystem::setSpawning(const bool spawning)
    {
        _isSpawning = spawning;
    }

    void ParticleSystem::setVelocity(const raylib::Vector2 minVelocity,
        const raylib::Vector2 maxVelocity)
    {
        _minVelocity = minVelocity;
        _maxVelocity = maxVelocity;
        _xVelocityDistribution = std::uniform_real_distribution(
            _minVelocity.x,
            _maxVelocity.x
        );
        _yVelocityDistribution = std::uniform_real_distribution(
            _minVelocity.y,
            _maxVelocity.y
        );
    }

    void ParticleSystem::setMinVelocity(const raylib::Vector2 minVelocity)
    {
        setVelocity(minVelocity, _maxVelocity);
    }

    void ParticleSystem::setMaxVelocity(const raylib::Vector2 maxVelocity)
    {
        setVelocity(_minVelocity, maxVelocity);
    }

    void ParticleSystem::setLifetime(const float minLifetime,
        const float maxLifetime)
    {
        _minLifetime = minLifetime;
        _maxLifetime = maxLifetime;
        _lifetimeDistribution = std::uniform_real_distribution(
            _minLifetime,
            _maxLifetime
        );
    }

    void ParticleSystem::setMinLifetime(const float minLifetime)
    {
        setLifetime(minLifetime, _maxLifetime);
    }

    void ParticleSystem::setMaxLifetime(const float maxLifetime)
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
        _colorDistribution = std::uniform_real_distribution(0.0f, 1.0f);
    }

    void ParticleSystem::setMinColor(const raylib::Color minColor)
    {
        setColor(minColor, _maxColor);
    }

    void ParticleSystem::setMaxColor(const raylib::Color maxColor)
    {
        setColor(_minColor, maxColor);
    }

    void ParticleSystem::setSize(const float size)
    {
        setSize(size, size);
    }

    void ParticleSystem::setSize(const float minSize, const float maxSize)
    {
        _minSize = minSize;
        _maxSize = maxSize;
        _sizeDistribution = std::uniform_real_distribution(
            minSize,
            maxSize
        );
    }

    void ParticleSystem::setMinSize(const float minSize)
    {
        setSize(minSize, _maxSize);
    }

    void ParticleSystem::setMaxSize(const float maxSize)
    {
        setSize(_minSize, maxSize);
    }
} // game::particle
