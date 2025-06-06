#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "AResourceProducer.hpp"

namespace Structure {
class Generator : public AResourceProducer {
public:
    Generator()
    {
        _name = "Generator";
        _resourceCost = 40;
        _oxygenCost = 20;
        _size = raylib::Vector2(2, 2);
        _icon = raylib::Texture2D("assets/RessourceProducer/generator_icon.png");
        _sprite = raylib::Texture2D("assets/RessourceProducer/generator_sprite.png");
        _pollutionEffect = 10;
        _resourceProduction = 10;
        _oxygenConsumption = 10;
        _habitantNeeded = 5;
    }

    ~Generator() override = default;
};
} // namespace Structure

#endif // GENERATOR_HPP
