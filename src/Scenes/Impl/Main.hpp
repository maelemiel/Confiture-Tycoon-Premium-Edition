//
// Created by Charles Mahoudeau on 6/7/25.
//

#ifndef MAIN_HPP
    #define MAIN_HPP

    #include "ResourceManager.hpp"
    #include "Events/EventManager.hpp"
    #include "Scenes/AScene.hpp"
#include "Structures/Factory/Factory.hpp"
#include "UI/UI.hpp"

namespace game::scene
{
    class Main final : public AScene
    {
        Map _map;
        ResourceManager _resourceManager;
        EventManager _eventManager;
        UI _ui;
        std::string _selectedStructure;
        Structures::Factory _factory;
        raylib::Texture _background;

        void _placeStructure(Game &game, std::shared_ptr<Tile> hoverTile,
        std::shared_ptr<Structure::IStructure> structure);
        void _takeResources(std::shared_ptr<Structure::IStructure> structure);
        bool _verifyResources(std::shared_ptr<Structure::IStructure> structure);

        void _updateMouse(float dt);

    public:
        explicit Main(Game &game);

        void update(float dt) override;
        void draw() const override;
    };
} // game::scene

#endif //MAIN_HPP
