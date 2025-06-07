#include "ResourceManager.hpp"
#include "Structures/Abstracts/AHabitation.hpp"
#include "Structures/Abstracts/AOxygenProducer.hpp"
#include "Structures/Abstracts/AResourceProducer.hpp"
#include <iostream>
#include <cmath> // For std::round

namespace game
{

ResourceManager::ResourceManager()
    : _SweetSweet(100),
      _SweetSweetPerSecond(0), _oxygenLevel(10000),
      _maxOxygenLevel(100000), _oxygenPerSecond(0),
      _population(0),
      _timeAccumulator(0.0f)
{
}

void ResourceManager::update(float deltaTime)
{

    _timeAccumulator += deltaTime;

    if (_timeAccumulator >= 1.0f) {
        _timeAccumulator -= 1.0f;

        _SweetSweet += _SweetSweetPerSecond;

        _oxygenLevel += _oxygenPerSecond;

        if (_oxygenLevel > _maxOxygenLevel) {
            _oxygenLevel = _maxOxygenLevel;
        }
        if (_oxygenLevel < 0) {
            _oxygenLevel = 0; // Clamp oxygen at 0
            std::cout << "Oxygen level critical! People are starting to die or it's depleted." << std::endl;
        }
    }
}

void ResourceManager::updateProduction(
    const std::vector<std::shared_ptr<Structure::IStructure>> &structures)
{
    calculateProduction(structures);
}

bool ResourceManager::spendSweetSweet(int amount)
{
    if (_SweetSweet >= amount) {
        _SweetSweet -= amount;
        return true;
    }
    return false;
}

void ResourceManager::addSweetSweet(int amount)
{
    _SweetSweet += amount;
}

float ResourceManager::getOxygenPercentage() const
{
    if (_maxOxygenLevel == 0) return 0.0f;
    return static_cast<float>(_oxygenLevel) /
        static_cast<float>(_maxOxygenLevel);
}

void ResourceManager::addOxygen(int amount)
{
    _oxygenLevel += amount * GetFrameTime() * GetFrameTime();
    if (_oxygenLevel > _maxOxygenLevel) {
        _oxygenLevel = _maxOxygenLevel;
    }
}

void ResourceManager::consumeOxygen(int amount)
{
    _oxygenLevel -= amount * GetFrameTime();
    if (_oxygenLevel < 0) {
        std::cout << "Oxygen level critical! People are starting to die" << std::endl;
    }
}

void ResourceManager::resetGame()
{
    _SweetSweet = 100;
    _SweetSweetPerSecond = 0;
    _oxygenLevel = 10000;
    _maxOxygenLevel = 100000;
    _oxygenPerSecond = 0;
    _population = 0;
    _timeAccumulator = 0.0f;

}

float ResourceManager::getDualityScore() const
{
    return std::clamp(
        static_cast<float>(_oxygenPerSecond) / static_cast<float>(_maxOxygenLevel),
        -1.0f,
        1.0f
    );
}

void ResourceManager::RessourceUpdate(
    const std::pmr::list<std::shared_ptr<Tile>> &tiles)
{
    std::vector<std::shared_ptr<Structure::IStructure>> structures;

    for (const auto &tile : tiles) {
        if (tile->isEmpty())
            continue;
        if (tile->getLinkedTile() != nullptr) {
            continue;
        }
        auto structure = tile->getStructureSharedPtr();
        if (structure) {
            structures.push_back(structure);
        }
    }
    if (!structures.empty()) {
        calculateProduction(structures);
    }
}

void ResourceManager::calculateProduction(
    const std::vector<std::shared_ptr<Structure::IStructure>> &structures)
{
    _SweetSweetPerSecond = 0;
    int netOxygenChangeFromStructuresPerSecond = 0;
    _population = 0;

    for (const auto &structure : structures) {
        if (!structure)
            continue;

        if (auto habitation =
                std::dynamic_pointer_cast<Structure::AHabitation>(structure)) {
            _population += habitation->getHabitationCap();
            _SweetSweetPerSecond -= habitation->getResourceCost();
            netOxygenChangeFromStructuresPerSecond -= habitation->getOxygenCost();
        }

        if (auto oxygenProducer =
                std::dynamic_pointer_cast<Structure::AOxygenProducer>(
                    structure)) {
            netOxygenChangeFromStructuresPerSecond += oxygenProducer->getOxygenProduction();
            _SweetSweetPerSecond -= oxygenProducer->getRessourceConsumption();
        }

        if (auto resourceProducer =
                std::dynamic_pointer_cast<Structure::AResourceProducer>(
                    structure)) {
            _SweetSweetPerSecond += resourceProducer->getResourceProduction();
            netOxygenChangeFromStructuresPerSecond -= resourceProducer->getOxygenConsumption();
        }
    }

    float populationOxygenConsumptionPerSecond = static_cast<float>(_population) * 0.05f;

    _oxygenPerSecond = netOxygenChangeFromStructuresPerSecond - static_cast<int>(std::round(populationOxygenConsumptionPerSecond));


    std::cout << "Production Update:" << std::endl;
    std::cout << "  SweetSweet/s: " << _SweetSweetPerSecond << std::endl;
    std::cout << "  Oxygen/s (from structures): " << netOxygenChangeFromStructuresPerSecond << std::endl;
    std::cout << "  Population Oxygen Consumption/s: " << populationOxygenConsumptionPerSecond << std::endl;
    std::cout << "  Net Total Oxygen/s: " << _oxygenPerSecond << std::endl;
    std::cout << "  Current Oxygen Level: " << _oxygenLevel << std::endl;
    std::cout << "  Population: " << _population << std::endl;
}
} // namespace game
