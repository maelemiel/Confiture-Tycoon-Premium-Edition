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
    raylib::Vector2 getSize() { return _size; }
    Texture2D &getIcon() { return _icon; }
    Texture2D &getSprite() { return _sprite; }
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
