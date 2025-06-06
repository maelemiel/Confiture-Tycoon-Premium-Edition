#ifndef HOUSE_HPP
#define HOUSE_HPP

#include "AHabitation.hpp"

namespace Structure {
class House : public AHabitation {
public:
    House()
    {
        _name = "House";
        _resourceCost = 10;
        _oxygenCost = 5;
        _size = raylib::Vector2(1, 1);
        _icon = raylib::Texture2D("assets/Habitation/house_icon.png");
        _sprite = raylib::Texture2D("assets/Habitation/house_sprite.png");
        _pollutionEffect = 0;
        _habitantCap = 4;
    }

    ~House() override = default;
};
} // namespace Structure

#endif // HOUSE_HPP
