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
        raylib::Texture OxygenFrame;
        raylib::Texture logoPeople;
        raylib::Texture logoRessources;
        raylib::Texture logoBuild;
        raylib::Texture logoGrid;
        raylib::Texture barOxy;
        raylib::Texture barPeople;
        raylib::Texture Oxy;
        raylib::Texture People;
        raylib::Texture Ressources;
        raylib::Texture Build;
        raylib::Texture Grid;
        //text nb people

        Vector2 OxyPosition;
        Vector2 OxyFramePosition;
        Vector2 barOxyPosition;
        Vector2 PeoplePosition;
        Vector2 RessourcesPosition;
        Vector2 BuildPosition;
        Vector2 GridPosition;
        Vector2 logoOxySize;
        Vector2 logoPeopleSize;
        Vector2 logoRessourcesSize;
        Vector2 logoBuildSize;
        Vector2 logoGridSize;
        float barOxySize;
        Vector2 barPeopleSize;
    
    public:
        void draw() const;

        // Variables
        UI() :
            logoOxy("assets/oxygen_tank.png"),
            OxygenFrame("assets/UI/O2_frame.png"),
            logoPeople("assets/population.png"),
            logoRessources("assets/jam.png"),
            logoBuild("assets/build.png"),
           // logoGrid("assets/grid.png"),
            barOxy("assets/UI/O2_bar.png")
           // barPeople("assets/population bar.png")
        {
            barOxySize = 5;
            barOxyPosition = {25, 20};
            OxyFramePosition = {barOxyPosition.x - 2 * barOxySize, barOxyPosition.y - 2 * barOxySize};
            OxyPosition = { 10, 10 };
            PeoplePosition = { 10, 50 };
            RessourcesPosition = { 10, 90 };
            BuildPosition = { 10, 130 };
            GridPosition = { 10, 170 };
        }
    };
} // game


#endif //GAME_HPP
