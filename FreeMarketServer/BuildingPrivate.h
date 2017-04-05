#pragma once
#include "PowerPrivate.h"

namespace ugly
{
    namespace FreeMarket
    {
        struct Building;

        struct BuildingTypePrivate
        {
            int probability = 0;
        };

        struct BuildingCardPrivate
        {
        };

        struct BuildingPrivate
        {
        };

        struct BuildingActionSource : ActionSource
        {
            BuildingActionSource(Building& building);
            Building& building;

            bool TryConsumeActionPoints(int actionPoints);
            Cell* GetCell();
        };
    }
}