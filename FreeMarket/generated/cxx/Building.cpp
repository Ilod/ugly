#include "Building.h"
#include "Client.h"
#include <cstdio>
namespace FreeMarket
{
    BuildingType::BuildingType()
        : id()
    { }
        
    BuildingCard::BuildingCard()
        : id()
        , building()
    { }
        
    void BuildingCard::Build(const Cell& position)
    {
        std::printf("1 %d %d\n", position.x, position.y);
    }
    Building::Building()
        : id()
        , type()
        , position()
        , owner()
    { }
        
}