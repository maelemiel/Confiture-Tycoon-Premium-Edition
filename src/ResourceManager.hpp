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

    int _oxygenLevel;
    int _maxOxygenLevel;
    int _oxygenPerSecond;

    int _population;

    int _wood;
    int _woodPerSecond;

    int _stone;
    int _stonePerSecond;

    float _timeAccumulator;

public:
    ResourceManager();

    void update(float deltaTime);
    void updateProduction(
        const std::vector<std::shared_ptr<Structure::IStructure>> &structures);
    void RessourceUpdate(
        const std::pmr::list<std::shared_ptr<Tile>> &tiles);

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
    void addStone(int amount);
    void addWood(int amount);

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

    int getPopulation() const
    {
        return _population;
    }

    int getWood() const
    {
        return _wood;
    }
    int getWoodPerSecond() const
    {
        return _woodPerSecond;
    }

    int getStone() const
    {
        return _stone;
    }
    int getStonePerSecond() const
    {
        return _stonePerSecond;
    }

    void resetGame();

    // Between -1.0 and 1.0, where 0.0 is neutral, -1.0 is full destruction, and 1.0 is full natural.
    [[nodiscard]] float getDualityScore() const;

private:
    void calculateProduction(
        const std::vector<std::shared_ptr<Structure::IStructure>> &structures);
};
} // namespace game

#endif // RESOURCEMANAGER_HPP
