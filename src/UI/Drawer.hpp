#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <raylib-cpp.hpp>
#include <string>

namespace game
{
    class Drawer
    {
    public:
        Drawer();

        void Update();
        void Draw() const;

        std::string* selectedStructurePtr = nullptr;

    private:
        bool _is_clicked;
        raylib::Texture logoDrawer;
        raylib::Texture priceButton;
        raylib::Texture menuFrame;
        raylib::Texture generatorButton;
        raylib::Texture treeButton;
        raylib::Texture houseButton;
        Vector2 DrawerPosition;
        float logoDrawerSize;
    };
}

#endif // DRAWER_HPP