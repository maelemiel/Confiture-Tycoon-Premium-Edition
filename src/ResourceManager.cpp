#include "ResourceManager.hpp"
#include "Structures/Abstracts/AHabitation.hpp"
#include "Structures/Abstracts/AOxygenProducer.hpp"
#include "Structures/Abstracts/AResourceProducer.hpp"
#include <iostream>

namespace game
{

ResourceManager::ResourceManager()
    : _SweetSweet(100),
      _SweetSweetPerSecond(0), _oxygenLevel(1000),
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
    _oxygenLevel = 1000;
    _maxOxygenLevel = 100000;
    _oxygenPerSecond = 0;
    _population = 0;
    _timeAccumulator = 0.0f;

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
    _oxygenPerSecond = 0;
    _population = 0;

    for (const auto &structure : structures) {
        if (!structure)
            continue;

        if (auto habitation =
                std::dynamic_pointer_cast<Structure::AHabitation>(structure)) {
            _population += habitation->getHabitationCap();
            _SweetSweetPerSecond -= habitation->getResourceCost();
            _oxygenPerSecond -= habitation->getOxygenCost();
        }

        if (auto oxygenProducer =
                std::dynamic_pointer_cast<Structure::AOxygenProducer>(
                    structure)) {
            _oxygenPerSecond += oxygenProducer->getOxygenProduction();
            _SweetSweetPerSecond -= oxygenProducer->getRessourceConsumption();
            _population -= oxygenProducer->getHabitantNeeded();
        }

        if (auto resourceProducer =
                std::dynamic_pointer_cast<Structure::AResourceProducer>(
                    structure)) {
            _SweetSweetPerSecond += resourceProducer->getResourceProduction();
            _oxygenPerSecond -= resourceProducer->getOxygenConsumption();
            _population -= resourceProducer->getHabitantNeeded();
        }
    }

    addOxygen(_oxygenPerSecond);
    consumeOxygen(_population * 0.01);
    std::cout << "Production Update:" << std::endl;
    std::cout << "  SweetSweet/s: " << _SweetSweetPerSecond << std::endl;
    std::cout << "  Oxygen/s: " << _oxygenPerSecond << std::endl;
    std::cout << "  Oxygen: " << _oxygenLevel << std::endl;
    std::cout << "  Population: " << _population << std::endl;
}
} // namespace game
