#ifndef EVENT_MANAGER_HPP
    #define EVENT_MANAGER_HPP

    #include <vector>
    #include <memory>
    #include "IEvent.hpp"

namespace game {
    class EventManager {
    private:
        std::vector<std::shared_ptr<IEvent>> _activeEvents;
        Map& _map;
        float _eventTimer;
        float _timeBetweenEvents;
    public:
        explicit EventManager(Map& map);
        void update(float deltaTime);
        void draw(const Window& window) const;
        void triggerRandomEvent();
        void addEvent(const std::shared_ptr<IEvent>& event);
    };
}

#endif //EVENT_MANAGER_HPP
