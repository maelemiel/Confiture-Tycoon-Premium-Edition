//
// Created by esteban on 6/6/25.
//

#include "UI.hpp"
#include <raylib-cpp.hpp>
#include "ResourceManager.hpp"

namespace game {
    void UI::draw() const {
        float oxygenPercentage = _resourceManagerRef.getOxygenLevel() / static_cast<float>(_resourceManagerRef.getMaxOxygenLevel());
        if (_resourceManagerRef.getMaxOxygenLevel() == 0) {
            oxygenPercentage = 0;
        }
        printf("Oxygen Level: %d, Max: %d, Percentage: %f\n", _resourceManagerRef.getOxygenLevel(), _resourceManagerRef.getMaxOxygenLevel(), oxygenPercentage);
        float barWidth = 86.0f;
        float barHeight = 21.0f;

        Rectangle sourceRect = {0, 0, barWidth * oxygenPercentage, barHeight};
        Rectangle destRect = {barOxyPosition.x, barOxyPosition.y, barOxySize * barWidth * oxygenPercentage, barOxySize * barHeight};

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