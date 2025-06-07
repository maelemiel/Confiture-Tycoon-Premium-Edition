//
// Created by esteban on 6/6/25.
//

#include "UI.hpp"
#include <raylib-cpp.hpp>
#include "ResourceManager.hpp"

namespace game {
    void UI::draw() const {
        float oxygenPercentage = _resourceManagerRef.getOxygenPercentage();
        if (oxygenPercentage < 0.0f) oxygenPercentage = 0.0f;
        if (oxygenPercentage > 1.0f) oxygenPercentage = 1.0f;

        Rectangle sourceRect = {0, 0, barOxy.width * oxygenPercentage, (float)barOxy.height};
        Rectangle destRect = {
            barOxyPosition.x,
            barOxyPosition.y,
            barOxySize * barOxy.width * oxygenPercentage,
            barOxySize * barOxy.height
        };

        oxygenFrame.Draw(oxyFramePosition, 0, barOxySize);
        if (destRect.width > 0) {
            DrawTexturePro(barOxy, sourceRect, destRect, {0, 0}, 0, WHITE);
        }
        logoOxy.Draw(logoOxyPosition, 0, logoOxySize);

        int rateFontSize = 40;
        if (!oxygenRateText.empty()) {
            float logoOxyScaledWidth = logoOxy.width * logoOxySize;
            raylib::Vector2 oxygenRateTextPos = {
                logoOxyPosition.x + logoOxyScaledWidth + 10,
                logoOxyPosition.y + (logoOxy.height * logoOxySize / 2) - (rateFontSize / 2.0f)
            };
            ::DrawText(oxygenRateText.c_str(), static_cast<int>(oxygenRateTextPos.x), static_cast<int>(oxygenRateTextPos.y), rateFontSize, oxygenRateColor);
        }

        populationFrame.Draw(populationFramePosition, 0, populationFrameSize);
        DrawText(population.c_str(), populationFramePosition.x + 35, populationFramePosition.y + 30, 70, BLACK);
        logoPopulation.Draw(logoPopulationPosition, 0, logoOxySize);

        resourcesFrame.Draw(resourcesFramePosition, 0, resourcesFrameSize);
        resourcesLogo.Draw(resourcesLogoPosition, 0, resourcesLogoSize);
        int resourcesValueFontSize = 50;
        DrawText(resources.c_str(), resourcesFramePosition.x + 20, resourcesFramePosition.y + 15, resourcesValueFontSize, BLACK);

        if (!resourcesRateText.empty()) {
            int textWidth = MeasureText(resourcesRateText.c_str(), rateFontSize);
            float logoResourcesScaledHeight = resourcesLogo.height * resourcesLogoSize;
            raylib::Vector2 resourcesRateTextPos = {
                resourcesLogoPosition.x - textWidth - 10,
                resourcesLogoPosition.y + (logoResourcesScaledHeight / 2) - (rateFontSize / 2.0f)
            };
            ::DrawText(resourcesRateText.c_str(), static_cast<int>(resourcesRateTextPos.x), static_cast<int>(resourcesRateTextPos.y), rateFontSize, resourcesRateColor);
        }
    }
}