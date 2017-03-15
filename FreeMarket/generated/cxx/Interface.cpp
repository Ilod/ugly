#include "Interface.h"
#include "Client.h"
#include <cstdio>
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
        
}