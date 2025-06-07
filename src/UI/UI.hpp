//
// Created by Gabriel Huet on 6/6/25.
//

#ifndef UI_HPP
    #define UI_HPP

    #include <memory>
    #include <raylib-cpp.hpp>

    #include "DualityBar.hpp"
    #include "ResourceManager.hpp"
    #include "Drawer.hpp"

namespace game
{
    class Game;

    class UI
    {
        Game &_game;

        ui::Drawer _drawer;
        std::string selectedStructure = "House";
        ResourceManager& _resourceManagerRef;
        raylib::Texture logoOxy;
        raylib::Texture oxygenFrame;
        raylib::Texture populationFrame;
        raylib::Texture logoPopulation;
        raylib::Texture logoResources;
        raylib::Texture barOxy;
        raylib::Texture resourcesFrame;
        raylib::Texture resourcesLogo;

        raylib::Texture frameWood;
        raylib::Texture logoWood;

        raylib::Texture frameStone;
        raylib::Texture logoStone;

        Vector2 oxyPosition;
        Vector2 oxyFramePosition;
        Vector2 barOxyPosition;
        Vector2 logoOxyPosition;
        float logoOxySize;
        float barOxySize;

        float populationFrameSize;
        Vector2 populationFramePosition;
        Vector2 logoPopulationPosition;
        float logoPopulationSize;

        float resourcesFrameSize;
        float resourcesLogoSize;
        Vector2 resourcesFramePosition;
        Vector2 resourcesLogoPosition;

        float woodFrameSize;
        float logoWoodSize;
        Vector2 woodFramePosition;
        Vector2 logoWoodPosition;

        float stoneFrameSize;
        float logoStoneSize;
        Vector2 stoneFramePosition;
        Vector2 logoStonePosition;

        ui::DualityBar _dualityBar;

        raylib::Texture _guiTempTexture;
        raylib::Vector2 _guiTempPosition;
        float _guiTempScale;

    public:
        explicit UI(Game &game, ResourceManager& rm) :
            _game(game),
            _drawer(game),
            _resourceManagerRef(rm),
            logoOxy("assets/UI/oxygen_tank.png"),
            oxygenFrame("assets/UI/O2_frame.png"),
            populationFrame("assets/UI/population_frame.png"),
            logoPopulation("assets/UI/population_logo.png"),
            barOxy("assets/UI/O2_bar.png"),
            resourcesFrame("assets/UI/resources_frame.png"),
            resourcesLogo("assets/UI/resources_logo.png"),
            frameWood("assets/UI/resources_frame.png"),
            logoWood("assets/UI/wood.png"),
            frameStone("assets/UI/resources_frame.png"),
            logoStone("assets/UI/stone.png"),
            _guiTempTexture("assets/UI/guitemp.png"),
            _guiTempScale(0.7f),
            oxygenRateColor(BLACK),
            resourcesRateColor(BLACK),
            woodAmountText("0"),
            woodRateColor(BLACK),
            stoneAmountText("0"),
            stoneRateColor(BLACK)
        {
            barOxySize = 5;
            barOxyPosition = {25, 20};
            oxyFramePosition = {barOxyPosition.x - 2 * barOxySize,
                                barOxyPosition.y - 2 * barOxySize};
            oxyPosition = {10, 10};
            logoOxyPosition = {460, 20};
            logoOxySize = 0.2f;

            population = "0";
            populationFramePosition = {
                1920 - oxyFramePosition.x - 90 * barOxySize,
                oxyFramePosition.y};
            populationFrameSize = barOxySize;
            logoPopulationPosition = {populationFramePosition.x - 110, 20};
            logoPopulationSize = 0.2f;

            resources = "0";
            resourcesFramePosition = {populationFramePosition.x + 200, 150};
            resourcesFrameSize = barOxySize;
            resourcesLogoPosition = {populationFramePosition.x + 120, 150};
            resourcesLogoSize = 0.3f;

            float y_spacing = 120.0f;

            woodFramePosition = {resourcesFramePosition.x,
                                 resourcesFramePosition.y + y_spacing};
            woodFrameSize = resourcesFrameSize;
            logoWoodPosition = {resourcesLogoPosition.x,
                                resourcesLogoPosition.y + y_spacing};
            logoWoodSize = resourcesLogoSize / 2.0f;

            stoneFramePosition = {woodFramePosition.x,
                                  woodFramePosition.y + y_spacing};
            stoneFrameSize = resourcesFrameSize;
            logoStonePosition = {logoWoodPosition.x,
                                 logoWoodPosition.y + y_spacing};
            logoStoneSize = resourcesLogoSize / 2.0f;

            _guiTempPosition = raylib::Vector2(0.0f,
                static_cast<float>(GetScreenHeight()) - (_guiTempTexture.height
                    * _guiTempScale));
        }

        void draw() const;
        void update();
        ui::DualityBar &getDualityBar() const;

        ui::DualityBar &getDualityBar();

        [[nodiscard]] bool isInBounds(const raylib::Vector2 &point) const;

        void setDrawerClickCallback(const std::function<void(const std::string &)> &callback);

        std::string population;
        std::string resources;
        std::string oxygenRateText;
        raylib::Color oxygenRateColor;
        std::string resourcesRateText;
        raylib::Color resourcesRateColor;

        std::string woodAmountText;
        std::string woodRateText;
        raylib::Color woodRateColor;

        std::string stoneAmountText;
        std::string stoneRateText;
        raylib::Color stoneRateColor;
    };
} // game


#endif //UI_HPP
