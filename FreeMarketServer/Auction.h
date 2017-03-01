#pragma once
#include <vector>
#include <cstdint>

namespace ugly
{
    namespace FreeMarket
    {
        
        enum class AuctionType
        {        
            Building = 0,        
            Unit = 1,        
            Location = 2,
        };
    
        struct Auction
        {
            std::int32_t id;
            std::int32_t turn;
            AuctionType type;
            std::int32_t buyer;
            std::int32_t price;
    
            Auction();
            
            bool Bid(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct Game& gameState, struct Player& playerState, std::int32_t amount);
    
            bool CanSee(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct Game& gameState, struct Player& playerState);
        };
    }
}