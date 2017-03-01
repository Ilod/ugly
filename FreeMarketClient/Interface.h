#pragma once
#include <vector>
#include <cstdint>
#include "Auction.h"
namespace FreeMarket
{

    struct PlayerConfig
    {
        std::int32_t id;
        std::int32_t team;

        PlayerConfig();
        
    };

    struct GameConfig
    {
        std::int32_t turns;
        std::int32_t turnTimeLimit;
        std::int32_t setupTimeLimit;
        std::vector<PlayerConfig> player;

        GameConfig();
        
    };

    struct Player
    {
        std::int32_t id;
        std::int32_t team;
        std::int32_t money;

        Player();
        
    };

    struct Game
    {
        std::int32_t turn;
        std::vector<Player> player;
        std::vector<Auction> activeAuction;
        std::vector<Auction> endedAuction;
        std::vector<Auction> futureAuction;

        Game();
        
    };
}