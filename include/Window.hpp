//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef WINDOW_HPP
    #define WINDOW_HPP

    #include <memory>
    #include <Vector2.hpp>

namespace raylib {
    class Window;
}

namespace game
{
    class Window
    {
        std::unique_ptr<raylib::Window> m_window;
        bool m_isOpen;

    public:
        explicit Window(raylib::Vector2 size);

        [[nodiscard]] bool isOpen();

        [[nodiscard]] raylib::Window &getRaylibWindow() const;
    };
} // game

#endif //WINDOW_HPP
