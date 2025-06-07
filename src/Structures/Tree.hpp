#ifndef STRUCTURE_TREE_HPP
#define STRUCTURE_TREE_HPP

#include "Abstracts/AOxygenProducer.hpp"

namespace Structure {
class Tree final : public AOxygenProducer {
public:
    Tree()
    {
        _name = "Tree";
        _resourceCost = 0;
        _woodCost = 10;
        _stoneCost = 0;
        _oxygenCost = 0;
        _size = raylib::Vector2(1, 1);
        _icon = raylib::Texture("assets/OxygenProducer/tree_icon.png");
        _sprite = raylib::Texture("assets/OxygenProducer/tree_sprite.png");
        _pollutionEffect = -5;
        _oxigenProduction = 5;
        _ressourceConsomption = 0;
        _habitantNeeded = 0;
    }

    ~Tree() override = default;
};
} // namespace Structure

#endif // STRUCTURE_TREE_HPP
