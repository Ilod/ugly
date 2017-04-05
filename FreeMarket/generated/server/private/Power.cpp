#include "Power.h"
#include "Serializer.h"
#include <cstdio>

namespace ugly
{
    namespace FreeMarket
    {
        PowerParameter::PowerParameter()
            : quantity()
            , resource()
            , buildingSource()
        { }
            
        Power::Power()
            : type()
            , quantity()
            , quantityForced()
            , resource()
            , resourceForced()
            , buildingSource()
            , boost()
            , boostPower()
        { }
            
        Action::Action()
            : id()
            , power()
            , actionPoint()
            , priority()
        { }
            
    }
}