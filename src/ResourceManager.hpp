#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <memory>
#include <vector>
#include <raylib-cpp.hpp>
#include "Structures/Abstracts/IStructure.hpp"
#include "Map.hpp"

namespace game
{
class ResourceManager
{
private:
    int _SweetSweet;
    int _SweetSweetPerSecond;

    // 🌬️ Oxygen System
    int _oxygenLevel;
    int _maxOxygenLevel;
    int _oxygenPerSecond;

    // 👥 Population System
    int _population;

    // ⏰ Time management
    float _timeAccumulator;

public:
    ResourceManager();

    // 📊 Update system
    void update(float deltaTime);
    void updateProduction(
        const std::vector<std::shared_ptr<Structure::IStructure>> &structures);
    void RessourceUpdate(
        const std::pmr::list<std::shared_ptr<Tile>> &tiles);

    // 🍯 SweetSweet Management
    int getSweetSweet() const
    {
        return _SweetSweet;
    }
    int getSweetSweetPerSecond() const
    {
        return _SweetSweetPerSecond;
    }
    bool spendSweetSweet(int amount);
    void addSweetSweet(int amount);

    // 🌬️ Oxygen Management
    int getOxygenLevel() const
    {
        return _oxygenLevel;
    }
    int getMaxOxygenLevel() const
    {
        return _maxOxygenLevel;
    }
    int getOxygenPerSecond() const
    {
        return _oxygenPerSecond;
    }
    float getOxygenPercentage() const;
    void addOxygen(int amount);
    void consumeOxygen(int amount);

    // 👥 Population Management
    int getPopulation() const
    {
        return _population;
    }
    void resetGame();

    // Between -1.0 and 1.0, where 0.0 is neutral, -1.0 is full destruction, and 1.0 is full natural.
    float getDualityScore() const;

private:
    void calculateProduction(
        const std::vector<std::shared_ptr<Structure::IStructure>> &structures);
};
} // namespace game

#endif // RESOURCEMANAGER_HPP
