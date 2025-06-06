#ifndef AHABITATION_HPP
#define AHABITATION_HPP

#include "IStructure.hpp"
#include "raylib-cpp.hpp"

namespace Structure {
class AHabitation : public IStructure {
public:
    virtual ~AHabitation() = default;

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
    int getHabitationCap() const { return _habitantCap; }

protected:
    int _habitantCap;
};
}

#endif // AHABITATION_HPP
