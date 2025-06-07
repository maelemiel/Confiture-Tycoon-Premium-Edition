#ifndef ABASICRESOURCEPRODUCER_HPP
#define ABASICRESOURCEPRODUCER_HPP

#include "IStructure.hpp"
#include "raylib-cpp.hpp"

namespace Structure {

enum class BasicResourceType {
    WOOD,
    STONE
};

class ABasicResourceProducer : public IStructure {
public:
    virtual ~ABasicResourceProducer() = default;

    void drawIcon() override {
        if (_icon.id > 0) DrawTexture(_icon, 0, 0, WHITE);
    }
    void drawIcon(raylib::Vector2 position) override {
        if (_icon.id > 0) DrawTexture(_icon, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
    }
    void drawSprite() override {
        if (_sprite.id > 0) DrawTextureEx(_sprite, {0,0}, 0.0f, 5.0f, WHITE);
    }
    void drawSprite(raylib::Vector2 position) override {
        DrawTexture(_sprite, position.x, position.y, WHITE);
    }

    string &getName() override { return _name; }
    int getResourceCost() override { return _resourceCost; }
    int getOxygenCost() override { return _oxygenCost; }
    raylib::Vector2 getSize() override { return _size; }
    raylib::Texture &getIcon() override { return _icon; }
    raylib::Texture &getSprite() override { return _sprite; }
    int getPollutionEffect() override { return _pollutionEffect; }

    BasicResourceType getProducedBasicResourceType() const { return _producedBasicResourceType; }
    int getBasicResourceProductionAmount() const { return _basicResourceProductionAmount; }
    int getOxygenConsumption() const { return _oxygenConsumption; }
    int getHabitantNeeded() const { return _habitantNeeded; }

protected:
    BasicResourceType _producedBasicResourceType;
    int _basicResourceProductionAmount;
    int _oxygenConsumption;
    int _habitantNeeded;
};

} // namespace Structure

#endif // ABASICRESOURCEPRODUCER_HPP
