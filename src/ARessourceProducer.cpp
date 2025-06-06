#include "ARessourceProducer.hpp"

namespace Structures {

void ARessourceProducer::drawIcon()
{
    DrawTexture(_icon, 0, 0, WHITE);
}

void ARessourceProducer::drawIcon(raylib::Vector2 position)
{
    DrawTexture(_icon, position.x, position.y, WHITE);
}

void ARessourceProducer::drawSprite()
{
    DrawTexture(_sprite, 0, 0, WHITE);
}

void ARessourceProducer::drawSprite(raylib::Vector2 position)
{
    DrawTexture(_sprite, position.x, position.y, WHITE);
}

string &ARessourceProducer::getName()
{
    return _name;
}

int ARessourceProducer::getRessourceCost()
{
    return _ressourceCost;
}

int ARessourceProducer::getOxygenCost()
{
    return _oxygenCost;
}

raylib::Vector2 ARessourceProducer::getSize()
{
    return _size;
}

Texture2D &ARessourceProducer::getIcon()
{
    return _icon;
}

Texture2D &ARessourceProducer::getSprite()
{
    return _sprite;
}

} // namespace Structures
