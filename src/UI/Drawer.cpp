#include "Drawer.hpp"

#include "Game.hpp"

namespace game::ui
{
    Drawer::Drawer(Game &game) :
        _game(game),
        _position{50, 885},
        _logoSize(0.3f),
        _isOpen(false),
        _logoDrawer("assets/button/menu_button.png"),
        _helpPanel("assets/UI/guitemp.png"),
        _menuFrame("assets/UI/opened_menu_frame.png"),
        _generatorButton(_game, {
            225 + 30, 885
        }, "assets/button/generator_button.png"),
        _treeButton(_game, {
            225 + 200, 885
        }, "assets/button/tree_button.png"),
        _houseButton(_game, {
            225 + 370, 885
        }, "assets/button/house_button.png")
    {
        _generatorButton.setOnClickCallback([this] {
            _onClickCallback("Generator");
        });
        _treeButton.setOnClickCallback([this] {
            _onClickCallback("Tree");
        });
        _houseButton.setOnClickCallback([this] {
            _onClickCallback("House");
        });
    }

    void Drawer::update(const float dt)
    {
        if (CheckCollisionPointRec(
            _game.getMousePosition(),
            {
                _position.x,
                _position.y,
                (static_cast<float>(_logoDrawer.GetWidth()) * _logoSize),
                (static_cast<float>(_logoDrawer.GetHeight()) * _logoSize)
            }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            _isOpen = !_isOpen;
        }

        if (_isOpen) {
            _generatorButton.update(dt);
            _treeButton.update(dt);
            _houseButton.update(dt);
        }
    }

    void Drawer::draw() const
    {
        _logoDrawer.Draw(_position, 0.0f, _logoSize, WHITE);
        if (_isOpen) {
            constexpr Vector2 menuPos = {225.0f, 868.0f};

            _menuFrame.Draw(menuPos, 0.0f, 0.6f, WHITE);
            _helpPanel.Draw(
                {menuPos.x + 1170.0f, menuPos.y - 20.0f},
                0.0f,
                0.7f,
                WHITE
            );

            _generatorButton.draw();
            _treeButton.draw();
            _houseButton.draw();
        }
    }

    void Drawer::setOnClickCallback(
        std::function<void(const std::string &)> callback)
    {
        _onClickCallback = std::move(callback);
    }

    raylib::Rectangle Drawer::getBounds() const
    {
        return {
            0.0f,
            850.0f,
            _isOpen ? 1920.0f : 275.0f,
            230.0f
        };
    }
}
