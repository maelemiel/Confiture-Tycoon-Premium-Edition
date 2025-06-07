#ifndef AOXYGENPRODUCER_HPP
#define AOXYGENPRODUCER_HPP

#include "IStructure.hpp"
#include "raylib-cpp.hpp"

namespace Structure {
class AOxygenProducer : public IStructure {
public:
    virtual ~AOxygenProducer() = default;

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
    int getOxygenProduction() const { return _oxigenProduction; }
    int getRessourceConsumption() const { return _ressourceConsomption; }
    int getHabitantNeeded() const { return _habitantNeeded; }

protected:
    int _oxigenProduction;
    int _ressourceConsomption;
    int _habitantNeeded;
};
}

#endif // AOXYGENPRODUCER_HPP
