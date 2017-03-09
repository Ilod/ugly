#pragma once
#include <vector>
#include <cstdint>

namespace ugly
{
    namespace FreeMarket
    {
        struct Building;
        
        enum class Ownership
        {        
            None = 0,        
            Preempt = 1,        
            Own = 2,
        };
        
        enum class CellType
        {        
            Road = 0,        
            House = 1,        
            Park = 2,        
            Building = 3,        
            Ruins = 4,        
            Work = 5,
        };
    
        struct Cell
        {
            std::int32_t x;
            std::int32_t y;
            std::int32_t owner;
            Ownership ownership;
            CellType type;
            Building* building;
    
            Cell();
            
        };
    }
}