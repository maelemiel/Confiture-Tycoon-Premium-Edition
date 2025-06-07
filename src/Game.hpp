//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef GAME_HPP
    #define GAME_HPP

    #include <raylib-cpp.hpp>

    #include "Camera.hpp"
    #include "Window.hpp"
    #include "Scenes/AScene.hpp"
    #include "Scenes/Impl/Main.hpp"
#include "Scenes/Impl/Splashscreen.hpp"

namespace game
{
    class Game
    {
        Window _window;
        Camera _camera;

        // --- Input ---
        raylib::Vector2 _mousePosition;
        raylib::Vector2 _lastMousePosition;
        raylib::Vector2 _mouseDelta;
        bool _mouseButtonLeftDown;
        bool _mouseButtonMiddleDown;
        bool _mouseButtonRightDown;
        bool _mouseButtonLeftPressed;
        bool _mouseButtonMiddlePressed;
        bool _mouseButtonRightPressed;
        bool _mouseButtonLeftReleased;
        bool _mouseButtonMiddleReleased;
        bool _mouseButtonRightReleased;
        raylib::Vector2 _mouseScrollDelta;

        // --- Scenes ---
        std::map<std::string, std::shared_ptr<scene::AScene>> _scenes;
        std::shared_ptr<scene::AScene> _currentScene;

        // --- Global game data ---
        raylib::AudioDevice _audioDevice;
        raylib::Music _backgroundMusic;

    public:
        explicit Game(raylib::Vector2 windowSize);

        void handleInput();
        void update();
        void draw();

        [[nodiscard]] bool isRunning();

        [[nodiscard]] Window &getWindow();
        [[nodiscard]] Camera &getCamera();

        [[nodiscard]] raylib::Vector2 getMousePosition() const;
        [[nodiscard]] raylib::Vector2 getMouseDelta() const;

        [[nodiscard]] bool isMouseButtonLeftDown() const;
        [[nodiscard]] bool isMouseButtonMiddleDown() const;
        [[nodiscard]] bool isMouseButtonRightDown() const;

        [[nodiscard]] bool isMouseButtonLeftPressed() const;
        [[nodiscard]] bool isMouseButtonMiddlePressed() const;
        [[nodiscard]] bool isMouseButtonRightPressed() const;

        [[nodiscard]] bool isMouseButtonLeftReleased() const;
        [[nodiscard]] bool isMouseButtonMiddleReleased() const;
        [[nodiscard]] bool isMouseButtonRightReleased() const;

        [[nodiscard]] raylib::Vector2 getMouseScrollDelta() const;

        void registerScene(const std::string &name, std::shared_ptr<scene::AScene> scene);
        void setScene(const std::string &name);
    };
} // game

#endif //GAME_HPP
