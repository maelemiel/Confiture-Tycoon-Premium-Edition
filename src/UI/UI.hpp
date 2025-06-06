//
// Created by Gabriel Huet on 6/6/25.
//

#ifndef UI_HPP
    #define UI_HPP

    #include <memory>
    #include <raylib-cpp.hpp>

    #include "UI.hpp"

namespace game
{
    class UI
    {
    private:
        int _a;
        raylib::Texture logoOxy;
        raylib::Texture oxygenFrame;
        raylib::Texture populationFrame;
        raylib::Texture logoPopulation;
        raylib::Texture logoResources;
        raylib::Texture barOxy;
        raylib::Texture resourcesFrame;
        raylib::Texture resourcesLogo;
        //text nb people

        Vector2 oxyPosition;
        Vector2 oxyFramePosition;
        Vector2 barOxyPosition;
        Vector2 logoOxyPosition;
        float logoOxySize;
        float barOxySize;

        float populationFrameSize;
        Vector2 populationFramePosition;
        Vector2 logoPopulationPosition;

        float resourcesFrameSize;
        float resourcesLogoSize;
        Vector2 resourcesFramePosition;
        Vector2 resourcesLogoPosition;
    
    public:
        void draw() const;

        // Variables

        std::string population;
        std::string resources;
        UI() :
            logoOxy("assets/UI/oxygen_tank.png"),
            oxygenFrame("assets/UI/O2_frame.png"),
            populationFrame("assets/UI/population_frame.png"),
            logoPopulation("assets/UI/population_logo.png"),
            barOxy("assets/UI/O2_bar.png"),
            resourcesFrame("assets/UI/resources_frame.png"),
            resourcesLogo("assets/UI/resources_logo.png")
        {
            barOxySize = 5;
            barOxyPosition = {25, 20};
            oxyFramePosition = {barOxyPosition.x - 2 * barOxySize, barOxyPosition.y - 2 * barOxySize};
            oxyPosition = { 10, 10 };
            logoOxyPosition = {460, 20};
            logoOxySize = 0.2;

            population = "0";
            populationFramePosition = { 1920 - oxyFramePosition.x - 90 * barOxySize, oxyFramePosition.y};
            populationFrameSize = barOxySize;
            logoPopulationPosition = { populationFramePosition.x - 110, 20};

            resources = "0";
            resourcesFramePosition = { populationFramePosition.x + 200, 150};
            resourcesFrameSize = barOxySize;
            resourcesLogoPosition = { populationFramePosition.x + 120, 150};
            resourcesLogoSize = 0.3;
        }
    };
} // game


#endif //GAME_HPP
