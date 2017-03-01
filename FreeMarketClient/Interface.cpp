#include "Interface.h"
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
        , player()
    { }
        
    Player::Player()
        : id()
        , team()
        , money()
    { }
        
    Game::Game()
        : turn()
        , player()
        , activeAuction()
        , endedAuction()
        , futureAuction()
    { }
        
}