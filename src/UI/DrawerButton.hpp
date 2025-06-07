//
// Created by Charles Mahoudeau on 6/7/25.
//

#ifndef DRAWBUTTON_HPP
    #define DRAWBUTTON_HPP

    #include <functional>

    #include "raylib-cpp.hpp"

namespace game::ui {
    class DrawerButton {
        raylib::Vector2 _position;
        raylib::Texture _icon;

        std::function<void()> _onClickCallback;

        constexpr static float scale = 0.7f;

    public:
        DrawerButton(raylib::Vector2 position, const std::string &iconPath);

        void update(float dt);
        void draw() const;

        void setOnClickCallback(const std::function<void()> &callback);
    };
} // ui
// game

#endif //DRAWBUTTON_HPP
