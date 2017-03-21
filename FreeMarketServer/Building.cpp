#include "Building.h"
#include "Serializer.h"
#include <cstdio>

namespace ugly
{
    namespace FreeMarket
    {
        BuildingType::BuildingType()
            : id()
            , action()
        { }
            
        BuildingCard::BuildingCard()
            : id()
            , building()
        { }
            
        bool BuildingCard::Build(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, const Cell& position)
        {
            return false;
        }
        Building::Building()
            : id()
            , type()
            , position()
            , owner()
        { }
            
        bool Building::Execute(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, const Action& action, const PowerParameter& param)
        {
            return false;
        }
    }
}