#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <functional>
#include <raylib-cpp.hpp>
#include <string>

#include "DrawerButton.hpp"

namespace game::ui
{
    class Drawer
    {
    public:
        Drawer();

        void update(float dt);
        void draw() const;

        void setOnClickCallback(std::function<void(const std::string &)> callback);
        [[nodiscard]] raylib::Rectangle getBounds() const;

    private:
        Vector2 _position;
        float _logoSize;
        bool _isOpen;
        raylib::Texture _logoDrawer;
        raylib::Texture _helpPanel;
        raylib::Texture _menuFrame;

        DrawerButton _generatorButton;
        DrawerButton _treeButton;
        DrawerButton _houseButton;

        std::function<void(const std::string &)> _onClickCallback;
    };
}

#endif // DRAWER_HPP