#include "AHabitation.hpp"

namespace Structures {

void AHabitation::drawIcon()
{
    DrawTexture(_icon, 0, 0, WHITE);
}

void AHabitation::drawIcon(raylib::Vector2 position)
{
    DrawTexture(_icon, position.x, position.y, WHITE);
}

void AHabitation::drawSprite()
{
    DrawTexture(_sprite, 0, 0, WHITE);
}

void AHabitation::drawSprite(raylib::Vector2 position)
{
    DrawTexture(_sprite, position.x, position.y, WHITE);
}

string &AHabitation::getName()
{
    return _name;
}

int AHabitation::getRessourceCost()
{
    return _ressourceCost;
}

int AHabitation::getOxygenCost()
{
    return _oxygenCost;
}

raylib::Vector2 AHabitation::getSize()
{
    return _size;
}

Texture2D &AHabitation::getIcon()
{
    return _icon;
}

Texture2D &AHabitation::getSprite()
{
    return _sprite;
}

} // namespace Structures
