#include "AOxygenProducer.hpp"
#include "Abstracts/AOxygenProducer.hpp"

namespace Structure {
class Tree final : public AOxygenProducer {
public:
    Tree()
    {
        _name = "Tree";
        _resourceCost = 10;
        _oxygenCost = 5;
        _size = {1, 1};
        _icon = raylib::Texture2D("assets/OxigenProducer/tree_icon.png");
        _sprite = raylib::Texture2D("assets/Oxigen_producer/tree_sprite.png");
        _pollutionEffect = -5;
        _oxigenProduction = 20;
        _ressourceConsomption = 0;
        _habitantNeeded = 0;
    }

    ~Tree() override = default;
};
} // namespace Structure
