#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "Abstracts/AResourceProducer.hpp"

namespace Structure {
class Generator : public AResourceProducer {
public:
    Generator()
    {
        _name = "Generator";
        _resourceCost = 0;
        _woodCost = 10;
        _stoneCost = 30;
        _oxygenCost = 30;
        _size = raylib::Vector2(2, 2);
        _icon = raylib::Texture2D("assets/RessourceProducer/generator_icon.png");
        _sprite = raylib::Texture2D("assets/RessourceProducer/generator_sprite.png");
        _pollutionEffect = 10;
        _resourceProduction = 1;
        _oxygenConsumption = 10;
        _habitantNeeded = 5;
    }

    ~Generator() override = default;
};
} // namespace Structure

#endif // GENERATOR_HPP
