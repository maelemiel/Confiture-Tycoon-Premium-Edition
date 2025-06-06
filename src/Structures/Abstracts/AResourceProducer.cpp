#include "AResourceProducer.hpp"

namespace Structure {

void AResourceProducer::drawIcon()
{
    DrawTexture(_icon, 0, 0, WHITE);
}

void AResourceProducer::drawIcon(raylib::Vector2 position)
{
    DrawTexture(_icon, position.x, position.y, WHITE);
}

void AResourceProducer::drawSprite()
{
    DrawTexture(_sprite, 0, 0, WHITE);
}

void AResourceProducer::drawSprite(raylib::Vector2 position)
{
    DrawTexture(_sprite, position.x, position.y, WHITE);
}

} // namespace Structure
