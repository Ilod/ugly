#pragma once
#include <vector>
#include <cstdint>

namespace ugly
{
    namespace FreeMarket
    {
    
        struct BuildingType
        {
            std::int32_t id;
    
            BuildingType();
            
        };
    
        struct Building
        {
            std::int32_t id;
            BuildingType* type;
            std::int32_t x;
            std::int32_t y;
            std::int32_t owner;
    
            Building();
            
        };
    }
}