//
// Created by Charles Mahoudeau on 6/6/25.
//

#include "Camera.hpp"

#include <algorithm>

#include "Rectangle.hpp"

namespace game {
    Camera::Camera() : _offset(0.0f, 0.0f), _zoom(1.0f),
        _screenRectangle(0.0f, 0.0f, 1920.0f, 1080.0f)
    {}

    raylib::Vector2 Camera::getWorldPositionAsScreenPosition(
        const raylib::Vector2 position) const
    {
        return {
            (position.x + _offset.x) * _zoom,
            (position.y + _offset.y) * _zoom
        };
    }

    raylib::Vector2 Camera::getScreenPositionAsWorldPosition(
        const raylib::Vector2 position) const
    {
        return {
            position.x / _zoom - _offset.x,
            position.y / _zoom - _offset.y
        };
    }

    float Camera::getScaledValue(const float value) const
    {
        return value * _zoom;
    }

    raylib::Vector2 Camera::getScaledVector2(const raylib::Vector2 vector) const
    {
        return {
            vector.x * _zoom,
            vector.y * _zoom
        };
    }

    raylib::Rectangle Camera::getScaledRectangle(
        const raylib::Rectangle &rectangle) const
    {
        auto screenPosition = getWorldPositionAsScreenPosition(
            raylib::Vector2(rectangle.x, rectangle.y)
        );
        auto screenSize = getScaledVector2(raylib::Vector2(
            rectangle.width,
            rectangle.height
        ));

        return {
            screenPosition.x,
            screenPosition.y,
            screenSize.x,
            screenSize.y
        };
    }

    raylib::Vector2 Camera::getOffset() const
    {
        return _offset;
    }

    void Camera::setOffset(const raylib::Vector2 offset)
    {
        _offset = offset;
    }

    float Camera::getZoom() const
    {
        return _zoom;
    }

    void Camera::setZoom(const float zoom)
    {
        _zoom = std::clamp(zoom, _minZoom, _maxZoom);
    }

    float Camera::getMinZoom() const
    {
        return _minZoom;
    }

    float Camera::getMaxZoom() const
    {
        return _maxZoom;
    }

    bool Camera::isRectangleInView(const raylib::Rectangle &rectangle) const
    {
        if (rectangle.width <= 0 || rectangle.height <= 0) {
            return false;
        }
        if (rectangle.x >= _screenRectangle.width ||
            rectangle.y >= _screenRectangle.height) {
            return false;
        }
        const auto screenPosition = getWorldPositionAsScreenPosition(
            raylib::Vector2(rectangle.x, rectangle.y)
        );
        const auto screenSize = getScaledVector2(raylib::Vector2(
            rectangle.width,
            rectangle.height
        ));
        const auto rectangleScreen = raylib::Rectangle(
            screenPosition.x,
            screenPosition.y,
            screenSize.x,
            screenSize.y
        );

        return _screenRectangle.CheckCollision(rectangleScreen);
    }
} // game
