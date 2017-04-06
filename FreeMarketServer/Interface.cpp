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
        { }
            
        PlayerState::PlayerState()
            : id()
            , team()
            , money()
        { }
            
        GameState::GameState()
            : turn()
        { }
            
    
        bool GameState::KnowResourceEvolution(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, int idx0)
        {
            return true;
        }
    }
}