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

    public:
        explicit Main(Game &game);

        void update(float dt) override;
        void draw() const override;
    };
} // game::scene

#endif //MAIN_HPP
