#ifndef AHABITATION_HPP
#define AHABITATION_HPP

#include "IStructures.hpp"
#include "raylib-cpp.hpp"

namespace Structures {
class AHabitation : public IStructures {
public:
    virtual ~AHabitation() = default;

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

    int getHabitationCap() const { return _habitantCap; }

protected:
    int _habitantCap;
};
}

#endif // AHABITATION_HPP
