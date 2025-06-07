//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Game.hpp"

#include <iostream>

#include "Scenes/Impl/DeathScreen.hpp"
#include "Structures/House.hpp"
#include "Structures/Tree.hpp"

namespace game
{
    Game::Game(const raylib::Vector2 windowSize) :
        _window(windowSize),
        _mouseButtonLeftDown(false),
        _mouseButtonMiddleDown(false),
        _mouseButtonRightDown(false),
        _mouseButtonLeftPressed(false),
        _mouseButtonMiddlePressed(false),
        _mouseButtonRightPressed(false),
        _mouseButtonLeftReleased(false),
        _mouseButtonMiddleReleased(false),
        _mouseButtonRightReleased(false),
        _currentScene(nullptr),
        _backgroundMusic("assets/musics/background.mp3")
    {
        _backgroundMusic.SetLooping(true);
        registerScene("splashscreen", std::make_shared<scene::Splashscreen>(*this));
        registerScene("main", std::make_shared<scene::Main>(*this));
        registerScene("DeathScreen", std::make_shared<scene::DeathScreen>(*this));
        setScene("splashscreen");
    }

    void Game::handleInput()
    {
        _lastMousePosition = _mousePosition;
        _mousePosition = _window.getMousePosition();
        _mouseDelta = _mousePosition - _lastMousePosition;

        _mouseButtonLeftDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        _mouseButtonMiddleDown = IsMouseButtonDown(MOUSE_BUTTON_MIDDLE);
        _mouseButtonRightDown = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

        _mouseButtonLeftPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        _mouseButtonMiddlePressed = IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE);
        _mouseButtonRightPressed = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);

        _mouseButtonLeftReleased = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
        _mouseButtonMiddleReleased = IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE);
        _mouseButtonRightReleased = IsMouseButtonReleased(MOUSE_BUTTON_RIGHT);

        _mouseScrollDelta = GetMouseWheelMoveV();
    }

    void Game::update()
    {
        const auto deltaTime = _window.getRaylibWindow().GetFrameTime();

        _backgroundMusic.Update();
        _currentScene->update(deltaTime);
    }

    void Game::draw()
    {
        _window.beginDraw();
        _currentScene->draw();
        _window.getRaylibWindow().DrawFPS();
        _window.endDraw();
    }

    bool Game::isRunning()
    {
        return _window.isOpen();
    }

    Window &Game::getWindow()
    {
        return _window;
    }

    Camera &Game::getCamera()
    {
        return _camera;
    }

    raylib::Vector2 Game::getMousePosition() const
    {
        return _mousePosition;
    }

    raylib::Vector2 Game::getMouseDelta() const
    {
        return _mouseDelta;
    }

    bool Game::isMouseButtonLeftDown() const
    {
        return _mouseButtonLeftDown;
    }

    bool Game::isMouseButtonMiddleDown() const
    {
        return _mouseButtonMiddleDown;
    }

    bool Game::isMouseButtonRightDown() const
    {
        return _mouseButtonRightDown;
    }

    bool Game::isMouseButtonLeftPressed() const
    {
        return _mouseButtonLeftPressed;
    }

    bool Game::isMouseButtonMiddlePressed() const
    {
        return _mouseButtonMiddlePressed;
    }

    bool Game::isMouseButtonRightPressed() const
    {
        return _mouseButtonRightPressed;
    }

    bool Game::isMouseButtonLeftReleased() const
    {
        return _mouseButtonLeftReleased;
    }

    bool Game::isMouseButtonMiddleReleased() const
    {
        return _mouseButtonMiddleReleased;
    }

    bool Game::isMouseButtonRightReleased() const
    {
        return _mouseButtonRightReleased;
    }

    raylib::Vector2 Game::getMouseScrollDelta() const
    {
        return _mouseScrollDelta;
    }

    void Game::registerScene(const std::string &name,
        std::shared_ptr<scene::AScene> scene)
    {
        _scenes[name] = std::move(scene);
    }

    void Game::setScene(const std::string &name)
    {
        if (_scenes.contains(name)) {
            if (name != "splashscreen") {
                _backgroundMusic.Play();
            } else {
                _backgroundMusic.Stop();
            }
            _currentScene = _scenes[name];
        } else {
            std::cerr << "Scene '" << name << "' not found!" << std::endl;
        }
    }
} // game
