#ifndef IEVENT_HPP
    #define IEVENT_HPP

    #include <memory>
    #include <string>
    #include "../Window.hpp"
    #include "../Map.hpp"

namespace game {
    class IEvent {
    protected:
        bool _isActive;
        float _duration;
        float _elapsedTime;
        std::string _name;
        std::string _description;

    public:
        IEvent(std::string name, std::string description, float duration);
        virtual ~IEvent() = default;

        virtual void start() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void draw(const Window &window) const = 0;
        virtual bool isFinished() const;

        [[nodiscard]] bool isActive() const;
        [[nodiscard]] const std::string& getName() const;
        [[nodiscard]] const std::string& getDescription() const;
    };
}

#endif //IEVENT_HPP
