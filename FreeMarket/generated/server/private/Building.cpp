#include "Building.h"
#include "Serializer.h"
#include <cstdio>

namespace ugly
{
    namespace FreeMarket
    {
        BuildingType::BuildingType()
            : id()
            , actionPointMax()
            , actionPointGain()
            , action()
        { }
            
        BuildingCard::BuildingCard()
            : id()
            , building()
            , owner()
        { }
            
        bool BuildingCard::Build(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, Cell& position, const std::string& orderStr)
        {
            return false;
        }
        Building::Building()
            : id()
            , type()
            , position()
            , owner()
            , actionPoint()
        { }
            
        bool Building::Execute(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, Action& action, PowerParameter& param, const std::string& orderStr)
        {
            return false;
        }
    }
}