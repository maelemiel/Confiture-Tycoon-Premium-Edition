#ifndef METEOREVENT_HPP
    #define METEOREVENT_HPP

    #include "IEvent.hpp"
    #include "../Map.hpp"
    #include "../Tile.hpp"
    #include <raylib-cpp.hpp>

namespace game {
    class MeteorEvent : public IEvent {
    private:
        Map& _map;
        std::shared_ptr<Tile> _targetTile;
        raylib::Texture _meteorTexture;
        raylib::Vector2 _meteorWorldPos;
        float _meteorSpeed;
        float _initialYOffset;

    public:
        explicit MeteorEvent(Map& map);
        ~MeteorEvent() override;

        void start() override;
        void update(float deltaTime) override;
        void draw(const Window &window) const override;
    };
}

#endif //METEOREVENT_HPP
