//
// Created by esteban on 6/6/25.
//

#include "UI.hpp"

#include <raylib-cpp.hpp>

namespace game {
    void UI::draw() const {
        float oxygenPercentage = 0.5f;
        Rectangle sourceRect = {0, -1, 86 * oxygenPercentage, 21};
        Rectangle destRect = {barOxyPosition.x, barOxyPosition.y, barOxySize * 86 * oxygenPercentage, barOxySize * 19};

        oxygenFrame.Draw(oxyFramePosition, 0, barOxySize);
        DrawTexturePro(barOxy, sourceRect, destRect, {0, 0}, 0, WHITE);
        logoOxy.Draw(logoOxyPosition, 0, logoOxySize);

        populationFrame.Draw(populationFramePosition, 0, populationFrameSize);
        DrawText(population.c_str(), populationFramePosition.x + 35, populationFramePosition.y + 30, 70, BLACK);
        logoPopulation.Draw(logoPopulationPosition, 0, logoOxySize);

        resourcesFrame.Draw(resourcesFramePosition, 0, resourcesFrameSize);
        resourcesLogo.Draw(resourcesLogoPosition, 0, resourcesLogoSize);
        DrawText(resources.c_str(), resourcesFramePosition.x + 20, resourcesFramePosition.y + 15, 50, BLACK);
    }
}