#pragma once

namespace ugly
{
    namespace FreeMarket
    {
        struct CellPrivate
        {
            static int GetDistance(const struct Cell* c1, const struct Cell* c2);
        };
    }
}