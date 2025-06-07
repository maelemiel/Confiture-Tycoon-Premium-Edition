//
// Created by Charles Mahoudeau on 6/7/25.
//

#include "AScene.hpp"

namespace game::scene {
    AScene::AScene(Game &game) : _game(game)
    {}

    Game &AScene::getGame() const
    {
        return _game;
    }
} // game::scene
