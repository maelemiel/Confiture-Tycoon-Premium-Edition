#include "AOxygenProducer.hpp"

namespace Structure {

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

} // namespace Structure
