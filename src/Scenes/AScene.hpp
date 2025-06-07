//
// Created by Charles Mahoudeau on 6/7/25.
//

#ifndef ASCENE_HPP
    #define ASCENE_HPP

namespace game
{
    class Game;
}

namespace game::scene
{

    class AScene {
        Game &_game;

    public:
        explicit AScene(Game &game);
        virtual ~AScene() = default;

        virtual void update(float dt) = 0;
        virtual void draw() const = 0;

        [[nodiscard]] Game &getGame() const;
    };
} // game::scene

#endif //ASCENE_HPP
