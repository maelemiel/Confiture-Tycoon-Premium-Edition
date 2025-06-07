#include "Factory.hpp"
#include "Structures/Tree.hpp"
#include "Structures/Generator.hpp"
#include "Structures/House.hpp"
#include "Structures/Mine.hpp"
#include "Structures/Grange.hpp"

namespace Structures {

Factory::Factory()
{
    registerStructure("Tree", std::make_shared<Structure::Tree>());
    registerStructure("Generator", std::make_shared<Structure::Generator>());
    registerStructure("House", std::make_shared<Structure::House>());
    registerStructure("Mine", std::make_shared<Structure::Mine>());
    registerStructure("Grange", std::make_shared<Structure::Grange>());
}

}
