#ifndef ARESSOURCEPRODUCER_HPP
#define ARESSOURCEPRODUCER_HPP

#include "IStructures.hpp"
#include "raylib-cpp.hpp"

namespace Structures {
class ARessourceProducer : public IStructures {
public:
    virtual ~ARessourceProducer() = default;

    void drawIcon();
    void drawIcon(raylib::Vector2 position);
    void drawSprite();
    void drawSprite(raylib::Vector2 position);

    // Interface getters
    string &getName() { return _name; }
    int getRessourceCost() { return _ressourceCost; }
    int getOxygenCost() { return _oxygenCost; }
    raylib::Vector2 getSize() { return _size; }
    Texture2D &getIcon() { return _icon; }
    Texture2D &getSprite() { return _sprite; }
    int getPollutionEffect() { return _pollutionEffect; }

    // Abstract getters
    int getRessourceProduction() const { return _ressourceProduction; }
    int getOxygenConsumption() const { return _oxygenConsumption; }
    int getHabitantNeeded() const { return _habitantNeeded; }

protected:
    int _ressourceProduction;
    int _oxygenConsumption;
    int _habitantNeeded;
};
}

#endif // ARESSOURCEPRODUCER_HPP
