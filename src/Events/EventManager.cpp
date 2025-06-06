#include "EventManager.hpp"
#include <iostream>
#include "MeteorEvent.hpp"

namespace game {
    EventManager::EventManager(Map& map) :
        _map(map),
        _eventTimer(0.0f),
        _timeBetweenEvents(20.0f)
    {
    }
    void EventManager::update(float deltaTime)
    {
        _eventTimer += deltaTime;
        if (_eventTimer >= _timeBetweenEvents) {
            triggerRandomEvent();
            _eventTimer = 0.0f;
            _timeBetweenEvents = 20.0f + static_cast<float>(GetRandomValue(0, 20));
        }
        for (auto it = _activeEvents.begin(); it != _activeEvents.end();) {
            auto& event = *it;
            event->update(deltaTime);
            if (!event->isActive() || event->isFinished()) {
                it = _activeEvents.erase(it);
            } else {
                ++it;
            }
        }
    }
    void EventManager::draw(const Window& window) const
    {
        for (const auto& event : _activeEvents) {
            event->draw(window);
        }
    }
    void EventManager::triggerRandomEvent()
    {
        bool hasStructures = false;
        for (int x = 0; x < static_cast<int>(_map.getSize().x); ++x) {
            for (int y = 0; y < static_cast<int>(_map.getSize().y); ++y) {
                auto tile = _map.getTile({(float)x, (float)y});
                if (tile && tile->hasStructure()) {
                    hasStructures = true;
                    break;
                }
            }
            if (hasStructures) break;
        }
        int eventType = 0;

        std::shared_ptr<IEvent> newEvent = nullptr;

        switch (eventType) {
            case 0:
                if (hasStructures) {
                    newEvent = std::make_shared<MeteorEvent>(_map);
                } else {
                     std::cout << "EventManager: Skipping MeteorEvent creation, no structures on map." << std::endl;
                }
                break;
            default:
                std::cout << "EventManager: Unknown event type." << std::endl;
                break;
        }

        if (newEvent) {
            addEvent(newEvent);
        } else {
            std::cout << "EventManager: Failed to create new event or conditions not met." << std::endl;
        }
    }
    void EventManager::addEvent(const std::shared_ptr<IEvent>& event)
    {
        if (event) {
            event->start();
            _activeEvents.push_back(event);
            std::cout << "New event: " << event->getName() << " - " << event->getDescription() << std::endl;
        }
    }
}
