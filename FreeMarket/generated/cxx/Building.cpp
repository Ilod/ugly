#include "Building.h"
#include "Client.h"
#include <cstdio>
namespace FreeMarket
{
    BuildingType::BuildingType()
        : id()
        , actionPoint()
        , action()
    { }
        
    BuildingCard::BuildingCard()
        : id()
        , building()
        , owner()
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
        
    void Building::Execute(const Action& action, const PowerParameter& param)
    {
        std::printf("2 %d %d %d %d\n", action.id, param.quantity, param.resource, (param.buildingSource != nullptr) ? (param.buildingSource->id) : -1);
    }
}