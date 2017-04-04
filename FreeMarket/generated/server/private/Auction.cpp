#include "Auction.h"
#include "Serializer.h"
#include <cstdio>

namespace ugly
{
    namespace FreeMarket
    {
        Auction::Auction()
            : id()
            , type()
            , price()
            , seller()
            , buyer()
            , turn()
            , building()
        { }
            
        bool Auction::Bid(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, std::int32_t money, const std::string& orderStr)
        {
            return false;
        }
    }
}