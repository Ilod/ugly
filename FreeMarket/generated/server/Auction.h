#pragma once
#include <vector>
#include <cstdint>
#include "AuctionPrivate.h"

namespace ugly
{
    namespace FreeMarket
    {
        struct BuildingType;
        
        enum class AuctionType
        {        
            Building = 0,
        };
    
        struct Auction
        {
            std::int32_t id;
            AuctionType type;
            std::int32_t price;
            std::int32_t seller;
            std::int32_t buyer;
            std::int32_t turn;
            BuildingType* building;
            AuctionPrivate additionalData;
    
            Auction();
            
            bool Bid(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, std::int32_t money);
        };
    }
}