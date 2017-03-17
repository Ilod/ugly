#include "Interface.h"
#include "Serializer.h"
#include <cstdio>

namespace ugly
{
    namespace FreeMarket
    {
        PlayerConfig::PlayerConfig()
            : id()
            , team()
        { }
            
        GameConfig::GameConfig()
            : turns()
            , turnTimeLimit()
            , setupTimeLimit()
            , mapSizeX()
            , mapSizeY()
            , startMoney()
            , resourceCount()
            , building()
            , player()
        { }
            
        PlayerState::PlayerState()
            : id()
            , team()
            , money()
            , building()
        { }
            
        GameState::GameState()
            : turn()
            , map()
            , resourcePrice()
            , resourceEvolution()
            , building()
            , player()
            , auction()
            , endedAuction()
        { }
            
    
        bool GameState::KnowResourceEvolution(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, int idx0)
        {
            return true;
        }
    }
}