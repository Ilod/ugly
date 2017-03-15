using System;
using System.Collections.Generic;

namespace FreeMarket
{
    
    public enum PriceEvolution
    {
        Unknown = 0,
        HugeDecrease = 1,
        SmallDecrease = 2,
        Stable = 3,
        SmallIncrease = 4,
        HugeIncrease = 5,
    }
}