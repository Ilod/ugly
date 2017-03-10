#include "Power.h"
#include "Client.h"
#include <cstdio>
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