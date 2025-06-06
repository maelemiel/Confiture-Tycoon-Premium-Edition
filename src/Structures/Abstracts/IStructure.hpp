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
    virtual int getResourceCost() = 0;
    virtual int getOxygenCost() = 0;
    virtual raylib::Vector2 getSize() = 0;
    virtual raylib::Texture &getIcon() = 0;
    virtual raylib::Texture &getSprite() = 0;
    virtual int getPollutionEffect() = 0;

protected:
    string _name;
    int _resourceCost;
    int _oxygenCost;
    raylib::Vector2 _size;
    raylib::Texture _icon;
    raylib::Texture _sprite;
    int _pollutionEffect;
};
}

#endif // ISTRUCTURE_HPP
