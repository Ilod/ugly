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
            std::vector<int> auctionProbability;
        };

        struct PlayerStatePrivate
        {
            int reservedMoney;
        };

        struct GameStatePrivate
        {
            std::vector<int> resourceEvolution;
            int nextBuildingId = 0;
            int nextBuildingCardId = 0;
            bool executeDelayed = false;
            std::map<int, std::vector<std::tuple<std::string, int>>> delayedOrders;
        };
    }
}