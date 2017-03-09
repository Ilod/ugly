#pragma once
#include <vector>
#include <cstdint>
namespace FreeMarket
{
    struct Cell;

    struct BuildingType
    {
        std::int32_t id;

        BuildingType();
        
    };

    struct BuildingCard
    {
        std::int32_t id;
        BuildingType* building;

        BuildingCard();
        
        void Build(const Cell& position);
    };

    struct Building
    {
        std::int32_t id;
        BuildingType* type;
        Cell* position;
        std::int32_t owner;

        Building();
        
    };
}