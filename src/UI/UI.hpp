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
        Vector2 PeoplePosition;
        Vector2 RessourcesPosition;
        Vector2 BuildPosition;
        Vector2 GridPosition;
        Vector2 logoOxySize = { 32, 32 };
        Vector2 logoPeopleSize = { 32, 32 };
        Vector2 logoRessourcesSize = { 32, 32 };
        Vector2 logoBuildSize = { 32, 32 };
        Vector2 logoGridSize = { 32, 32 };
        Vector2 barOxySize = { 50, 10 };
        Vector2 barPeopleSize = { 50, 50 };
    
    public:
        void draw() const;

        // Variables
        UI() :
            logoOxy("assets/oxygen_tank.png"),
            logoPeople("assets/people_tank.png"),
            logoRessources("assets/jam.png"),
            logoBuild("assets/build.png"),
            logoGrid("assets/grid.png"),
            barOxy("assets/oxygen bar.png"),
            barPeople("assets/population bar.png")
        {
            OxyPosition = { 10, 10 };
            PeoplePosition = { 10, 50 };
            RessourcesPosition = { 10, 90 };
            BuildPosition = { 10, 130 };
            GridPosition = { 10, 170 };
        }
    };
} // game


#endif //GAME_HPP
