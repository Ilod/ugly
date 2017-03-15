#pragma once
#include <vector>
#include <cstdint>
#include "Auction.h"
#include "Building.h"
#include "Map.h"
#include "Resource.h"
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
        std::int32_t mapSizeX;
        std::int32_t mapSizeY;
        std::int32_t startMoney;
        std::int32_t resourceCount;
        std::vector<BuildingType> building;
        std::vector<PlayerConfig> player;

        GameConfig();
        
    };

    struct PlayerState
    {
        std::int32_t id;
        std::int32_t team;
        std::int32_t money;
        std::vector<Building*> building;

        PlayerState();
        
    };

    struct GameState
    {
        std::int32_t turn;
        std::vector<std::vector<Cell>> map;
        std::vector<std::int32_t> resourcePrice;
        std::vector<PriceEvolution> resourceEvolution;
        std::vector<Building> building;
        std::vector<PlayerState> player;
        std::vector<Auction> auction;
        std::vector<Auction> endedAuction;

        GameState();
        
    };
}