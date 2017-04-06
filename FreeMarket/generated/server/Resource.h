#pragma once
#include <vector>
#include <cstdint>
#include "EnumHelper.h"
#include "ResourcePrivate.h"

namespace ugly
{
    namespace FreeMarket
    {
        
        enum class PriceEvolution
        {        
            Unknown = 0,        
            HugeDecrease = 1,        
            SmallDecrease = 2,        
            Stable = 3,        
            SmallIncrease = 4,        
            HugeIncrease = 5,
        };
    }
}