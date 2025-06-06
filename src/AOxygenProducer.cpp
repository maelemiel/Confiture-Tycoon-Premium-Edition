#include "AOxygenProducer.hpp"

namespace Structures {

void AOxygenProducer::drawIcon()
{
    DrawTexture(_icon, 0, 0, WHITE);
}

void AOxygenProducer::drawIcon(raylib::Vector2 position)
{
    DrawTexture(_icon, position.x, position.y, WHITE);
}

void AOxygenProducer::drawSprite()
{
    DrawTexture(_sprite, 0, 0, WHITE);
}

void AOxygenProducer::drawSprite(raylib::Vector2 position)
{
    DrawTexture(_sprite, position.x, position.y, WHITE);
}

string &AOxygenProducer::getName()
{
    return _name;
}

int AOxygenProducer::getRessourceCost()
{
    return _ressourceCost;
}

int AOxygenProducer::getOxygenCost()
{
    return _oxygenCost;
}

raylib::Vector2 AOxygenProducer::getSize()
{
    return _size;
}

Texture2D &AOxygenProducer::getIcon()
{
    return _icon;
}

Texture2D &AOxygenProducer::getSprite()
{
    return _sprite;
}

} // namespace Structures
