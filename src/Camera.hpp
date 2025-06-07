//
// Created by Charles Mahoudeau on 6/6/25.
//

#ifndef CAMERA_HPP
    #define CAMERA_HPP

    #include "Rectangle.hpp"
    #include "Vector2.hpp"

namespace raylib {
class Rectangle;
}

namespace game {
    class Camera {
        raylib::Vector2 _offset;
        float _zoom;
        const float _minZoom = 0.1f;
        const float _maxZoom = 10.0f;
        raylib::Rectangle _screenRectangle;

    public:
        Camera();

        [[nodiscard]] raylib::Vector2 getWorldPositionAsScreenPosition(
            raylib::Vector2 position) const;
        [[nodiscard]] raylib::Vector2 getScreenPositionAsWorldPosition(
            raylib::Vector2 position) const;

        [[nodiscard]] float getScaledValue(float value) const;
        [[nodiscard]] raylib::Vector2 getScaledVector2(raylib::Vector2 vector) const;
        [[nodiscard]] raylib::Rectangle getScaledRectangle(
            const raylib::Rectangle &rectangle) const;

        [[nodiscard]] raylib::Vector2 getOffset() const;
        void setOffset(raylib::Vector2 offset);

        [[nodiscard]] float getZoom() const;
        void setZoom(float zoom);

        [[nodiscard]] float getMinZoom() const;
        [[nodiscard]] float getMaxZoom() const;

        [[nodiscard]] bool isRectangleInView(
            const raylib::Rectangle &rectangle) const;
    };
} // game

#endif //CAMERA_HPP
