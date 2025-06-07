#include "IEvent.hpp"

namespace game {
    IEvent::IEvent(std::string name, std::string description, float duration) :
        _isActive(false),
        _duration(duration),
        _elapsedTime(0.0f),
        _name(std::move(name)),
        _description(std::move(description))
    {}

    bool IEvent::isFinished() const
    {
        return _elapsedTime >= _duration;
    }

    bool IEvent::isActive() const
    {
        return _isActive;
    }

    const std::string& IEvent::getName() const
    {
        return _name;
    }

    const std::string& IEvent::getDescription() const
    {
        return _description;
    }
}
