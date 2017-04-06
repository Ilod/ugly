#include "Map.h"
#include "Serializer.h"
#include <cstdio>
#include <cstdlib>

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
            if (ownership != Ownership::Preempt || owner != playerState.id || price > playerState.money - playerState.additionalData.reservedMoney)
                return false;
            ownership = Ownership::Own;
            playerState.money -= price;
            return true;
        }

        int CellPrivate::GetDistance(const Cell* c1, const Cell* c2)
        {
            return std::abs(c1->x - c2->x) + std::abs(c1->y - c2->y);
        }
    }
}