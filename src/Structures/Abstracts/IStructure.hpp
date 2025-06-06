#ifndef ISTRUCTURE_HPP
#define ISTRUCTURE_HPP

#include <string>
#include "raylib-cpp.hpp"

using namespace std;

namespace Structure {
class IStructure {
public:
    virtual ~IStructure() = default;

    virtual void drawIcon() = 0;
    virtual void drawIcon(raylib::Vector2) = 0;
    virtual void drawSprite() = 0;
    virtual void drawSprite(raylib::Vector2) = 0;

    virtual string &getName() = 0;
    virtual int getRessourceCost() = 0;
    virtual int getOxygenCost() = 0;
    virtual raylib::Vector2 getSize() = 0;
    virtual Texture2D &getIcon() = 0;
    virtual Texture2D &getSprite() = 0;
    virtual int getPollutionEffect() = 0;

protected:
    string _name;
    int _ressourceCost;
    int _oxygenCost;
    raylib::Vector2 _size;
    Texture2D _icon;
    Texture2D _sprite;
    int _pollutionEffect;
};
}

#endif // ISTRUCTURE_HPP
