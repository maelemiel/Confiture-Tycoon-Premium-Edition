#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Structures/Abstracts/IStructure.hpp"
#include <memory>
#include <map>
#include <string>

namespace Structures {
class Factory {
public:
    Factory();
    ~Factory() = default;

    std::shared_ptr<Structure::IStructure> getStructure(const std::string& type)
    {
        if (_structureMap.find(type) == _structureMap.end()) {
            throw std::runtime_error("Structure type not found: " + type);
        }
        return _structureMap.at(type);
    }

    void registerStructure(const std::string& type, std::shared_ptr<Structure::IStructure> structure)
    {
        _structureMap[type] = structure;
    }

private:
    std::map<std::string, std::shared_ptr<Structure::IStructure>> _structureMap;
};
}

#endif // FACTORY_HPP
