#include "Building.h"
#include "Serializer.h"
#include <cstdio>

namespace ugly
{
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
}