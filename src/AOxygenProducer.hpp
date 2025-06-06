#ifndef AOXYGENPRODUCER_HPP
#define AOXYGENPRODUCER_HPP

#include "IStructures.hpp"
#include "raylib-cpp.hpp"

namespace Structures {
class AOxygenProducer : public IStructures {
public:
    virtual ~AOxygenProducer() = default;

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

    int getOxygenProductionRate() const { return _oxigenProductionRate; }
    int getRessourceCost() const { return _ressourceCost; }
    int getHabitantNeeded() const { return _habitantNeeded; }

protected:
    int _oxigenProductionRate;
    int _ressourceCost;
    int _habitantNeeded;
};
}

#endif // AOXYGENPRODUCER_HPP
