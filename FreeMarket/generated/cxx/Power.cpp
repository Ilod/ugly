#include "Power.h"
#include "Client.h"
#include <cstdio>
namespace FreeMarket
{
    PowerParameter::PowerParameter()
        : quantity()
        , resource()
        , buildingTarget()
    { }
        
    Power::Power()
        : type()
        , quantity()
        , quantityForced()
        , resource()
        , resourceForced()
        , buildingTarget()
        , buildingTargetOwner()
        , boost()
        , boostPower()
        , range()
    { }
        
    Action::Action()
        : id()
        , power()
        , actionPoint()
        , priority()
    { }
        
}