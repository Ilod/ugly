#pragma once
#include <vector>
#include <cstdint>
#include "EnumHelper.h"
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

        

        Auction();
        
        void Bid(std::int32_t money);
    };
}