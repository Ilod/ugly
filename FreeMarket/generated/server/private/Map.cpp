#include "Map.h"
#include "Serializer.h"
#include <cstdio>

namespace ugly
{
    namespace FreeMarket
    {
        Cell::Cell()
            : x()
            , y()
            , owner()
            , ownership()
            , type()
            , building()
            , price()
        { }
            
        bool Cell::Buy(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, const std::string& orderStr)
        {
            return false;
        }
    }
}