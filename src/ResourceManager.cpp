#include "ResourceManager.hpp"
#include "Structures/Abstracts/AHabitation.hpp"
#include "Structures/Abstracts/AOxygenProducer.hpp"
#include "Structures/Abstracts/AResourceProducer.hpp"
#include "Structures/Abstracts/ABasicResourceProducer.hpp"
#include <iostream>
#include <cmath>

#include "Game.hpp"

namespace game
{

ResourceManager::ResourceManager(Game &game)
    : _SweetSweet(10),
      _SweetSweetPerSecond(0), _oxygenLevel(5000),
      _maxOxygenLevel(10000), _oxygenPerSecond(0),
      _population(0),
      _wood(100),
      _woodPerSecond(0),
      _stone(100),
      _stonePerSecond(0),
      _timeAccumulator(0.0f), _game(game) {
}

void ResourceManager::update(float deltaTime)
{

    _timeAccumulator += deltaTime;

    if (_timeAccumulator >= 1.0f) {
        _timeAccumulator -= 1.0f;

        _SweetSweet += _SweetSweetPerSecond;
        if (_SweetSweet < 0) {
            _SweetSweet = 0;
        }

        _wood += _woodPerSecond;
        if (_wood < 0) {
            _wood = 0;
        }

        _stone += _stonePerSecond;
        if (_stone < 0) {
            _stone = 0;
        }

        _oxygenLevel += _oxygenPerSecond;

        if (_oxygenLevel > _maxOxygenLevel) {
            _oxygenLevel = _maxOxygenLevel;
        }
        if (_oxygenLevel < 0) {
            _oxygenLevel = 0;
            _game.setScene("DeathScreen");
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

void ResourceManager::addWood(int amount)
{
    _wood += amount;
}

void ResourceManager::addStone(int amount)
{
    _stone += amount;
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
        _game.setScene("DeathScreen");
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
    _wood = 0;
    _woodPerSecond = 0;
    _stone = 0;
    _stonePerSecond = 0;
    _timeAccumulator = 0.0f;

}

float ResourceManager::getDualityScore() const
{
    return (std::clamp(
        static_cast<float>(_oxygenPerSecond) / static_cast<float>(_maxOxygenLevel),
        -1.0f,
        1.0f
    )*35);
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
        updatePollution(tiles);
    }
}

void ResourceManager::calculateProduction(
    const std::vector<std::shared_ptr<Structure::IStructure>> &structures)
{
    _SweetSweetPerSecond = 0;
    _woodPerSecond = 0;
    _stonePerSecond = 0;
    int netOxygenChangeFromStructuresPerSecond = 0;
    _population = 0;

    for (const auto &structure : structures) {
        if (!structure)
            continue;

        if (auto habitation =
                std::dynamic_pointer_cast<Structure::AHabitation>(structure)) {
            _population += habitation->getHabitationCap();
            _SweetSweetPerSecond -= habitation->getResourceCost();
            _woodPerSecond -= 1;
            _stonePerSecond -= 1;
            netOxygenChangeFromStructuresPerSecond -= habitation->getOxygenCost();
        }

        if (auto oxygenProducer =
                std::dynamic_pointer_cast<Structure::AOxygenProducer>(
                    structure)) {
            netOxygenChangeFromStructuresPerSecond += oxygenProducer->getOxygenProduction();
            _SweetSweetPerSecond -= oxygenProducer->getRessourceConsumption();
        }

        if (auto sweetSweetProducer =
                std::dynamic_pointer_cast<Structure::AResourceProducer>(structure)) {
            if (!std::dynamic_pointer_cast<Structure::ABasicResourceProducer>(structure)) {
                 _SweetSweetPerSecond += sweetSweetProducer->getResourceProduction();
                 netOxygenChangeFromStructuresPerSecond -= sweetSweetProducer->getOxygenConsumption();
            }
        }
        if (auto basicProducer =
                std::dynamic_pointer_cast<Structure::ABasicResourceProducer>(structure)) {
            if (basicProducer->getProducedBasicResourceType() == Structure::BasicResourceType::WOOD) {
                _woodPerSecond += basicProducer->getBasicResourceProductionAmount();
            } else if (basicProducer->getProducedBasicResourceType() == Structure::BasicResourceType::STONE) {
                _stonePerSecond += basicProducer->getBasicResourceProductionAmount();
            }
            netOxygenChangeFromStructuresPerSecond -= basicProducer->getOxygenConsumption();
        }
    }

    float populationOxygenConsumptionPerSecond = static_cast<float>(_population) * 0.05f;

    _oxygenPerSecond = netOxygenChangeFromStructuresPerSecond - static_cast<int>(std::round(populationOxygenConsumptionPerSecond));

    // std::cout << "Production Update:" << std::endl;
    // std::cout << "  SweetSweet/s: " << _SweetSweetPerSecond << std::endl;
    // std::cout << "  Wood/s: " << _woodPerSecond << std::endl;
    // std::cout << "  Stone/s: " << _stonePerSecond << std::endl;
    // std::cout << "  Oxygen/s (from structures): " << netOxygenChangeFromStructuresPerSecond << std::endl;
    // std::cout << "  Population Oxygen Consumption/s: " << populationOxygenConsumptionPerSecond << std::endl;
    // std::cout << "  Net Total Oxygen/s: " << _oxygenPerSecond << std::endl;
    // std::cout << "  Current Oxygen Level: " << _oxygenLevel << std::endl;
    // std::cout << "  Current Wood: " << _wood << std::endl;
    // std::cout << "  Current Stone: " << _stone << std::endl;
    // std::cout << "  Population: " << _population << std::endl;
}

void ResourceManager::updatePollution(const std::pmr::list<std::shared_ptr<Tile>>& tiles)
{
    // Reset pollution levels first
    for (const auto& tile : tiles) {
        tile->setPollutionLevel(0);
    }
    
    // Apply pollution from structures
    for (const auto& tile : tiles) {
        if (tile->isEmpty() || tile->getLinkedTile() != nullptr) {
            continue;
        }
        
        auto structure = tile->getStructureSharedPtr();
        if (!structure) continue;
        
        int pollutionEffect = structure->getPollutionEffect();
        if (pollutionEffect > 0) { // Structure pollue
            // Polluer la tuile elle-même
            tile->addPollution(pollutionEffect * 2);
            
            // Polluer toutes les tuiles occupées par le bâtiment (tuiles liées)
            raylib::Vector2 structureSize = structure->getSize();
            raylib::Vector2 structurePos = tile->getPosition();
            
            // Appliquer la pollution à toutes les tuiles du bâtiment
            for (int x = 0; x < static_cast<int>(structureSize.x); x++) {
                for (int y = 0; y < static_cast<int>(structureSize.y); y++) {
                    raylib::Vector2 linkedTilePos = raylib::Vector2(
                        structurePos.x + static_cast<float>(x),
                        structurePos.y + static_cast<float>(y)
                    );
                    
                    // Trouver la tuile à cette position
                    for (const auto& linkedTile : tiles) {
                        if (linkedTile->getPosition().x == linkedTilePos.x && 
                            linkedTile->getPosition().y == linkedTilePos.y) {
                            linkedTile->addPollution(pollutionEffect * 2);
                            break;
                        }
                    }
                }
            }
            
            // Polluer les tuiles voisines (rayon de 3 tuiles)
            int pollutionRadius = 3;
            
            for (const auto& targetTile : tiles) {
                raylib::Vector2 targetPos = targetTile->getPosition();
                float distance = sqrt(pow(targetPos.x - structurePos.x, 2) + 
                                    pow(targetPos.y - structurePos.y, 2));
                
                if (distance <= pollutionRadius && distance > 0) {
                    // Pollution diminue avec la distance
                    int pollutionAmount = static_cast<int>(pollutionEffect * (1.0f - distance / pollutionRadius));
                    if (pollutionAmount > 0) {
                        targetTile->addPollution(pollutionAmount);
                    }
                }
            }
        }
    }
}
} // namespace game
