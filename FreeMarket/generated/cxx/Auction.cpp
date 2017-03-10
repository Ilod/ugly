#include "Auction.h"
#include "Client.h"
#include <cstdio>
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
        
    void Auction::Bid(std::int32_t money)
    {
        std::printf("3 %d\n", money);
    }
}