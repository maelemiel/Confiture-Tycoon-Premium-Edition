//
// Created by esteban on 6/6/25.
//

#include "UI.hpp"

#include <raylib-cpp.hpp>

namespace game {
    void UI::draw() const {
        oxygenFrame.Draw(oxyFramePosition, 0, barOxySize);
        barOxy.Draw(barOxyPosition, 0, barOxySize);
        logoOxy.Draw(logoOxyPosition, 0, logoOxySize);

        populationFrame.Draw(populationFramePosition, 0, populationFrameSize);
        DrawText(population.c_str(), populationFramePosition.x + 35, populationFramePosition.y + 30, 70, BLACK);
        logoPopulation.Draw(logoPopulationPosition, 0, logoOxySize);

        resourcesFrame.Draw(resourcesFramePosition, 0, resourcesFrameSize);
        resourcesLogo.Draw(resourcesLogoPosition, 0, resourcesLogoSize);
        DrawText(resources.c_str(), resourcesFramePosition.x + 20, resourcesFramePosition.y + 15, 50, BLACK);
    }
}