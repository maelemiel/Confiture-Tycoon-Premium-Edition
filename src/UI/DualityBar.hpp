//
// Created by Charles Mahoudeau on 6/7/25.
//

#ifndef DUALITYBAR_HPP
    #define DUALITYBAR_HPP

    #include "raylib-cpp.hpp"

namespace game::ui {
    class DualityBar {
        raylib::Texture _texture;
        float _level;

    public:
        DualityBar();

        void update(float dt);
        void draw() const;

        void setLevel(float level);
    };
} // game::ui

#endif //DUALITYBAR_HPP
