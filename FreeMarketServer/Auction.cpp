#include "Auction.h"
#include <cstdio>

namespace ugly
{
    namespace FreeMarket
    {
        Auction::Auction()
            : id()
            , turn()
            , type()
            , buyer()
            , price()
        { }
            
        bool Auction::Bid(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct Game& gameState, struct Player& playerState, std::int32_t amount)
        {
            return false;
        }
    
        bool Auction::CanSee(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct Game& gameState, struct Player& playerState)
        {
            return true;
        }
    }
}