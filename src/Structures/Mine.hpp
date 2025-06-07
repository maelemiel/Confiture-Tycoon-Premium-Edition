#ifndef MINE_HPP
#define MINE_HPP

#include "Abstracts/ABasicResourceProducer.hpp"

namespace Structure {
class Mine : public ABasicResourceProducer {
public:
    Mine()
    {
        _name = "Mine";
        _resourceCost = 30;
        _oxygenCost = 20;
        _size = raylib::Vector2(2, 2);
        _icon = raylib::Texture("assets/Mine/mine.png");
        _sprite = raylib::Texture("assets/Mine/mine.png");
        _pollutionEffect = 0;

        _producedBasicResourceType = BasicResourceType::STONE;
        _basicResourceProductionAmount = 1;
        _oxygenConsumption = 5;
        _habitantNeeded = 2;
    }

    ~Mine() override = default;
};
} // namespace Structure

#endif // MINE_HPP
