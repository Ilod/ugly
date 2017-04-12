#include "Map.h"
#include "Client.h"
#include <cstdio>
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
        
    void Cell::Buy()
    {
        std::printf("0 %d %d\n", (*this).x, (*this).y);
    }
}