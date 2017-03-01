#include "Auction.h"
#include <cstdio>
namespace FreeMarket
{
    Auction::Auction()
        : id()
        , turn()
        , type()
        , buyer()
        , price()
    { }
        
    void Auction::Bid(std::int32_t amount)
    {        std::printf("0 %d\n", amount);
    }
}