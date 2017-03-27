#include "Building.h"
#include "Serializer.h"
#include <cstdio>

namespace ugly
{
    namespace FreeMarket
    {
        BuildingType::BuildingType()
            : id()
            , actionPoint()
            , action()
        { }
            
        BuildingCard::BuildingCard()
            : id()
            , building()
            , owner()
        { }
            
        bool BuildingCard::Build(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, Cell& position)
        {
            return false;
        }
        Building::Building()
            : id()
            , type()
            , position()
            , owner()
        { }
            
        bool Building::Execute(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, Action& action, PowerParameter& param)
        {
            return false;
        }
    }
}