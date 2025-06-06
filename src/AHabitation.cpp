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

} // namespace Structures
