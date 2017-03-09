#include "Building.h"
#include "Client.h"
#include <cstdio>
namespace FreeMarket
{
    BuildingType::BuildingType()
        : id()
    { }
        
    Building::Building()
        : id()
        , type()
        , x()
        , y()
        , owner()
    { }
        
}