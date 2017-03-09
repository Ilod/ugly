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
        , building()
        , player()
    { }
        
}