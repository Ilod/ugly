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
    { }
        
    Action::Action()
        : id()
        , power()
        , actionPoint()
        , priority()
    { }
        
}