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