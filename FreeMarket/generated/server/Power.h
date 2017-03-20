#pragma once
#include <vector>
#include <cstdint>
#include "PowerPrivate.h"

namespace ugly
{
    namespace FreeMarket
    {
        struct Building;
        
        enum class ParameterType
        {        
            None = 0,        
            Choice = 1,        
            Forced = 2,        
            Random = 3,        
            Self = 4,        
            All = 5,
        };
        
        enum class PowerType
        {        
            ProduceResource = 0,        
            SellResource = 1,
        };
    
        struct PowerParameter
        {
            std::int32_t quantity;
            std::int32_t resource;
            Building* buildingSource;
            PowerParameterPrivate additionalData;        
    
            
    
            PowerParameter();
            
        };
    
        struct Power
        {
            PowerType type;
            ParameterType quantity;
            std::int32_t quantityForced;
            ParameterType resource;
            std::int32_t resourceForced;
            ParameterType buildingSource;
            PowerPrivate additionalData;        
    
            
    
            Power();
            
        };
    
        struct Action
        {
            std::int32_t id;
            Power power;
            std::int32_t actionPoint;
            std::int32_t cooldown;
            std::int32_t turnLimit;
            ActionPrivate additionalData;        
    
            
    
            Action();
            
        };
    }
}