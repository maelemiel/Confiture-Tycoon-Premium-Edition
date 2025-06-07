#ifndef GRANGE_HPP
#define GRANGE_HPP

#include "Abstracts/ABasicResourceProducer.hpp"

namespace Structure {
class Grange : public ABasicResourceProducer {
public:
    Grange()
    {
        _name = "Grange";
        _resourceCost = 0;
        _woodCost = 20;
        _stoneCost = 20;
        _oxygenCost = 20;
        _size = raylib::Vector2(3, 3);
        _icon = raylib::Texture("assets/Grange/grange.png");
        _sprite = raylib::Texture("assets/Grange/grange.png");
        _pollutionEffect = 0;

        _producedBasicResourceType = BasicResourceType::WOOD;
        _basicResourceProductionAmount = 2;
        _oxygenConsumption = 2;
        _habitantNeeded = 1;
    }

    ~Grange() override = default;
};
} // namespace Structure

#endif // GRANGE_HPP
