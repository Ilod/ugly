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

            bool TryConsumeActionPoints(int actionPoints) override;
            Cell* GetCell() override;
            int GetResourceCapacity() override;
            int GetResource(int resource) override;
            void SetResource(int resource, int quantity) override;
        };
    }
}