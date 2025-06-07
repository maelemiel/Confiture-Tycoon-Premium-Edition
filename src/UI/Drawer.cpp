#include "Drawer.hpp"
#include <cstdio>

namespace game
{
    Drawer::Drawer()
    : _is_clicked(false),
      logoDrawer("assets/button/menu_button.png"),
      menuFrame("assets/UI/opened_menu_frame.png"),
      generatorButton("assets/button/generator_button.png"),
      treeButton("assets/button/tree_button.png"),
      houseButton("assets/button/menu_button.png"),
      priceButton("assets/UI/guitemp.png"),
      DrawerPosition{50, 885},
      logoDrawerSize(0.3f)
{}

    void Drawer::Update()
    {
        Vector2 menuPos = {225, 885};
        if (CheckCollisionPointRec(GetMousePosition(),
                {DrawerPosition.x, DrawerPosition.y,
                 static_cast<float>(logoDrawer.GetWidth() * logoDrawerSize),
                 static_cast<float>(logoDrawer.GetHeight() * logoDrawerSize)}) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            _is_clicked = !_is_clicked;
        }

        if (_is_clicked) {
            Vector2 genPos = {menuPos.x + 30, menuPos.y + 17};
            float genScale = 0.7f;
            Rectangle genRect = {
                genPos.x, genPos.y,
                static_cast<float>(generatorButton.GetWidth() * genScale),
                static_cast<float>(generatorButton.GetHeight() * genScale)
            };
            if (CheckCollisionPointRec(GetMousePosition(), genRect) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && selectedStructurePtr)
            {
                *selectedStructurePtr = "Generator";
                _is_clicked = false;
            }

            Vector2 treePos = {menuPos.x + 200, menuPos.y + 17};
            float treeScale = 0.7f;
            Rectangle treeRect = {
                treePos.x, treePos.y,
                static_cast<float>(treeButton.GetWidth() * treeScale),
                static_cast<float>(treeButton.GetHeight() * treeScale)
            };
            if (CheckCollisionPointRec(GetMousePosition(), treeRect) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && selectedStructurePtr)
            {
                *selectedStructurePtr = "Tree";
                _is_clicked = false;
            }

            Vector2 housePos = {menuPos.x + 370, menuPos.y + 17};
            float houseScale = 0.7f;
            Rectangle houseRect = {
                housePos.x, housePos.y,
                static_cast<float>(houseButton.GetWidth() * houseScale),
                static_cast<float>(houseButton.GetHeight() * houseScale)
            };
            if (CheckCollisionPointRec(GetMousePosition(), houseRect) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && selectedStructurePtr)
            {
                *selectedStructurePtr = "House";
                _is_clicked = false;
            }
        }
    }

    void Drawer::Draw() const
    {
        Vector2 menuPos = {225, 885};
        logoDrawer.Draw(DrawerPosition, 0.0f, logoDrawerSize, WHITE);
        if (_is_clicked) {
            priceButton.Draw({menuPos.x + 900, menuPos.y - 25}, 0.0f, 0.7f, WHITE);
            menuFrame.Draw(menuPos, 0.0f, 0.6f, WHITE);
            generatorButton.Draw({menuPos.x + 30, menuPos.y + 18}, 0.0f, 0.7f, WHITE);
            treeButton.Draw({menuPos.x + 200, menuPos.y + 18}, 0.0f, 0.7f, WHITE);
            houseButton.Draw({menuPos.x + 370, menuPos.y + 18}, 0.0f, 0.3f, WHITE);
        }
    }
}
