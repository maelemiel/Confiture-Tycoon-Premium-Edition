//
// Created by esteban on 6/6/25.
//

#include "UI.hpp"

#include <raylib-cpp.hpp>

namespace game {
    void UI::draw() const {
        OxygenFrame.Draw(OxyFramePosition, 0, barOxySize);
        barOxy.Draw(barOxyPosition, 0, barOxySize);
        logoOxy.Draw(logoOxyPosition, 0, logoOxySize);
    }
}