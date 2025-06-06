//
// Created by Gabriel Huet on 6/6/25.
//

#ifndef UI_HPP
    #define UI_HPP

    #include <memory>
    #include <raylib-cpp.hpp>

    #include "Ui.hpp"

namespace game
    class Ui;
{
    class Ui
    {
    private:
        Texture2D logoOxy;
        Texture2D logoPeople;
        Texture2D logoRessources;
        Texture2D logoBuild;
        Texture2D logoGrid;
        Texture2D Oxy;
        Texture2D People;
        Texture2D Ressources;
        Texture2D Build;
        Texture2D Grid;
        Texture2D barOxy;
        Texture2D barPeople;
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
        Vector2 barpeopleSize = { 50, 50 };
    
    public:
        Ui();
        Ui() {
            logoOxy = raylib::Texture2D("assets/oxygen tank.png");
            logoPeople = raylib::Texture2D("assets/population.png");
            logoRessources = raylib::Texture2D("assets/jam.png");
            logoBuild = raylib::Texture2D("assets/build.png");
            logoGrid = raylib::Texture2D("assets/grid.png");
            barOxy = raylib::Texture2D("assets/oxygen bar.png");
            barPeople = raylib::Texture2D("assets/population bar.png");

            OxyPosition = { 10, 10 };
            PeoplePosition = { 10, 50 };
            RessourcesPosition = { 10, 90 };
            BuildPosition = { 10, 130 };
            GridPosition = { 10, 170 };
            barOxyPosition = { 50, 10 };
            barPeoplePosition = { 50, 50 };
        }
    }
} // game

#endif //GAME_HPP
