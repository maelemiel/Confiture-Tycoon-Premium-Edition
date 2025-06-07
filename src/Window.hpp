//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef WINDOW_HPP
    #define WINDOW_HPP

    #include <raylib-cpp.hpp>

    #include <memory>
    #include <Vector2.hpp>

namespace raylib {
    class Window;
}

namespace game
{
    class Window
    {
        raylib::Window _window;
        raylib::RenderTexture _texture;
        raylib::Image _windowIcon;
        bool _isOpen;

    public:
        explicit Window(raylib::Vector2 size);

        void beginDraw();
        void endDraw();

        void clear(raylib::Color color) const;

        [[nodiscard]] raylib::Vector2 getSize();

        [[nodiscard]] bool isOpen();

        [[nodiscard]] raylib::Vector2 getMousePosition();

        [[nodiscard]] raylib::Window &getRaylibWindow();
    };
} // game

#endif //WINDOW_HPP
