//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Particle.hpp"
#include "ParticleSystem.hpp"

namespace game::particle
{
    Particle::Particle(
        ParticleSystem &particleSystem,
        const raylib::Vector2 position,
        const raylib::Vector2 velocity,
        const float lifetime,
        const raylib::Color color,
        const float size,
        const float antiLag
    ) :
        _particleSystem(particleSystem), _position(position),
        _velocity(velocity), _lifetime(lifetime), _color(color),
        _size(size), _antiLag(antiLag)
    {}

    void Particle::update(const float dt)
    {
        _position += _velocity * dt;
        _lifetime -= dt;
    }

    void Particle::draw() const
    {
        const auto camera = _particleSystem.getCamera();

        if (camera.getZoom() < _antiLag) {
            return;
        }

        const auto rectangle = raylib::Rectangle(
            _position.x,
            _position.y,
            _size,
            _size
        );

        if (!camera.isRectangleInView(rectangle)) {
            return;
        }

        const auto screenRectangle = camera.getScaledRectangle(rectangle);

        screenRectangle.DrawRounded(5.0f, 1, _color);
    }

    float Particle::getLifetime() const
    {
        return _lifetime;
    }
} // game::particle
