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
        std::unique_ptr<raylib::Window> _window;
        std::unique_ptr<raylib::RenderTexture> _texture;
        bool _isOpen;

    public:
        explicit Window(raylib::Vector2 size);

        void beginDraw() const;
        void endDraw() const;

        void clear(raylib::Color color) const;

        [[nodiscard]] raylib::Vector2 getSize() const;

        [[nodiscard]] bool isOpen();

        [[nodiscard]] raylib::Vector2 getMousePosition() const;

        [[nodiscard]] raylib::Window &getRaylibWindow() const;
    };
} // game

#endif //WINDOW_HPP
