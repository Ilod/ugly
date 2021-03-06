#include "Building.h"
#include "Client.h"
#include <cstdio>
namespace FreeMarket
{
    BuildingType::BuildingType()
        : id()
        , actionPointMax()
        , actionPointGain()
        , resourceCapacity()
        , action()
    { }
        
    BuildingCard::BuildingCard()
        : id()
        , building()
        , owner()
    { }
        
    void BuildingCard::Build(const Cell& position)
    {
        std::printf("1 %d %d %d\n", (*this).id, position.x, position.y);
    }
    Building::Building()
        : id()
        , type()
        , position()
        , owner()
        , actionPoint()
        , resource()
    { }
        
    void Building::Execute(const Action& action, const PowerParameter& param)
    {
        std::printf("2 %d %d %d %d %d\n", (*this).id, action.id, param.quantity, param.resource, (param.buildingTarget != nullptr) ? (param.buildingTarget->id) : -1);
    }
}