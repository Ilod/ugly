#pragma once
#include <vector>
#include "Resource.h"

namespace ugly
{
    namespace FreeMarket
    {
        struct PriceEvolutionRange
        {
            int min;
            int max;
            PriceEvolution type;
            int probability;
        };

        struct PlayerConfigPrivate
        {
        };

        struct GameConfigPrivate
        {
            std::vector<PriceEvolutionRange> resourcePriceEvolution;
            int resourceStartPrice;
            int preemptPrice;
        };

        struct PlayerStatePrivate
        {
        };

        struct GameStatePrivate
        {
            std::vector<int> resourceEvolution;
        };
    }
}