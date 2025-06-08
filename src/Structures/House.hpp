#ifndef HOUSE_HPP
#define HOUSE_HPP

#include "Abstracts/AHabitation.hpp"

namespace Structure {
class House : public AHabitation {
public:
    House()
    {
        _name = "House";
        _resourceCost = 5;
        _woodCost = 5;
        _stoneCost = 0;
        _oxygenCost = 5;
        _size = raylib::Vector2(2, 2);
        _icon = raylib::Texture2D("assets/Habitation/house_icon.png");
        _sprite = raylib::Texture2D("assets/Habitation/house_sprite.png");
        _pollutionEffect = 0;
        _habitantCap = 5;
        _habitantNeeded = 0;
    }

    ~House() override = default;
};
} // namespace Structure

#endif // HOUSE_HPP
