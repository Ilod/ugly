#pragma once
#include <vector>
#include <cstdint>
#include "Power.h"

namespace ugly
{
    namespace FreeMarket
    {
        struct Cell;
    
        struct BuildingType
        {
            std::int32_t id;
            std::vector<Action> action;
    
            BuildingType();
            
        };
    
        struct BuildingCard
        {
            std::int32_t id;
            BuildingType* building;
    
            BuildingCard();
            
            bool Build(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, const Cell& position);
        };
    
        struct Building
        {
            std::int32_t id;
            BuildingType* type;
            Cell* position;
            std::int32_t owner;
    
            Building();
            
            bool Execute(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, const Action& action, const PowerParameter& param);
        };
    }
}