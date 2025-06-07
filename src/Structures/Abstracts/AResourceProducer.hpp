#ifndef ARESOURCEPRODUCER_HPP
#define ARESOURCEPRODUCER_HPP

#include "IStructure.hpp"
#include "raylib-cpp.hpp"

namespace Structure {
class AResourceProducer : public IStructure {
public:
    virtual ~AResourceProducer() = default;

    void drawIcon();
    void drawIcon(raylib::Vector2 position);
    void drawSprite();
    void drawSprite(raylib::Vector2 position);

    // Interface getters
    string &getName() { return _name; }
    int getResourceCost() { return _resourceCost; }
    int getOxygenCost() { return _oxygenCost; }
    int getWoodCost() { return _woodCost; }
    int getStoneCost() { return _stoneCost; }
    raylib::Vector2 getSize() { return _size; }
    raylib::Texture &getIcon() { return _icon; }
    raylib::Texture &getSprite() { return _sprite; }
    int getPollutionEffect() { return _pollutionEffect; }

    // Abstract getters
    int getResourceProduction() const { return _resourceProduction; }
    int getOxygenConsumption() const { return _oxygenConsumption; }
    int getHabitantNeeded() const { return _habitantNeeded; }

protected:
    int _resourceProduction;
    int _oxygenConsumption;
    int _habitantNeeded;
};
}

#endif // ARESOURCEPRODUCER_HPP
