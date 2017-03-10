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
            , resourceForce()
            , buildingSource()
        { }
            
        Action::Action()
            : id()
            , power()
            , actionPoint()
            , cooldown()
            , turnLimit()
        { }
            
    }
}