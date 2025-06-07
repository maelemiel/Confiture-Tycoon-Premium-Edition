//
// Created by esteban on 6/6/25.
//

#include "UI.hpp"
#include <raylib-cpp.hpp>
#include "ResourceManager.hpp"
#include "Drawer.hpp"

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

        // Wood UI
        frameWood.Draw(woodFramePosition, 0, woodFrameSize);
        logoWood.Draw(logoWoodPosition, 0, logoWoodSize);
        DrawText(woodAmountText.c_str(), woodFramePosition.x + 20, woodFramePosition.y + 15, resourcesValueFontSize, BLACK);

        if (!woodRateText.empty()) {
            int textWidth = MeasureText(woodRateText.c_str(), rateFontSize);
            float logoWoodScaledHeight = logoWood.height * logoWoodSize;
            raylib::Vector2 woodRateTextPos = {
                logoWoodPosition.x - textWidth - 10,
                logoWoodPosition.y + (logoWoodScaledHeight / 2) - (rateFontSize / 2.0f)
            };
            ::DrawText(woodRateText.c_str(), static_cast<int>(woodRateTextPos.x), static_cast<int>(woodRateTextPos.y), rateFontSize, woodRateColor);
        }

        frameStone.Draw(stoneFramePosition, 0, stoneFrameSize);
        logoStone.Draw(logoStonePosition, 0, logoStoneSize);
        DrawText(stoneAmountText.c_str(), stoneFramePosition.x + 20, stoneFramePosition.y + 15, resourcesValueFontSize, BLACK);

        if (!stoneRateText.empty()) {
            int textWidth = MeasureText(stoneRateText.c_str(), rateFontSize);
            float logoStoneScaledHeight = logoStone.height * logoStoneSize;
            raylib::Vector2 stoneRateTextPos = {
                logoStonePosition.x - textWidth - 10,
                logoStonePosition.y + (logoStoneScaledHeight / 2) - (rateFontSize / 2.0f)
            };
            ::DrawText(stoneRateText.c_str(), static_cast<int>(stoneRateTextPos.x), static_cast<int>(stoneRateTextPos.y), rateFontSize, stoneRateColor);
        }

        _dualityBar.draw();
        _drawer.draw();
    }

    void UI::update() {
        _drawer.update(0.0f);
    }

    ui::DualityBar & UI::getDualityBar()
    {
        return _dualityBar;
    }

    bool UI::isInBounds(const raylib::Vector2 &point) const
    {
        if (_drawer.getBounds().CheckCollision(point)) {
            return true;
        }
        return false;
    }

    void UI::setDrawerClickCallback(
        const std::function<void(const std::string &)> &callback)
    {
        _drawer.setOnClickCallback(callback);
    }
}
