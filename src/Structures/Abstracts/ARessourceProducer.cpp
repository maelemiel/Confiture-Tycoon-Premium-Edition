#include "ARessourceProducer.hpp"

namespace Structure {

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

} // namespace Structure
