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
        , building()
        , player()
        , auction()
        , endedAuction()
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
        , building()
        , player()
    { }
        
}