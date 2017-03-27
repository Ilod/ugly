#pragma once
#include <vector>
#include <cstdint>
#include "Power.h"
namespace FreeMarket
{
    struct Cell;

    struct BuildingType
    {
        std::int32_t id;
        std::int32_t actionPoint;
        std::vector<Action> action;        

        

        BuildingType();
        
    };

    struct BuildingCard
    {
        std::int32_t id;
        BuildingType* building;
        std::int32_t owner;        

        

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
        
        void Execute(const Action& action, const PowerParameter& param);
    };
}