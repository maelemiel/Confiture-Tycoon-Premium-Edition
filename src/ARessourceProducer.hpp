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

    string &getName();
    int getRessourceCost();
    int getOxygenCost();
    raylib::Vector2 getSize();
    Texture2D &getIcon();
    Texture2D &getSprite();

    int getRessourceProductionRate() const { return _ressourceProductionRate; }
    int getRessourceCost() const { return _ressourceCost; }
    int getHabitantNeeded() const { return _habitantNeeded; }

protected:
    int _ressourceProductionRate;
    int _oxygenCost;
    int _habitantNeeded;
};
}

#endif // ARESSOURCEPRODUCER_HPP
