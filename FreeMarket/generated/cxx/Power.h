#pragma once
#include <vector>
#include <cstdint>
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
    
    enum class BoostType
    {        
        None = 0,        
        Fixed = 1,        
        Percent = 2,
    };

    struct PowerParameter
    {
        std::int32_t quantity;
        std::int32_t resource;
        Building* buildingSource;        

        

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
        BoostType boost;
        std::int32_t boostPower;        

        

        Power();
        
    };

    struct Action
    {
        std::int32_t id;
        Power power;
        std::int32_t actionPoint;
        std::int32_t priority;        

        

        Action();
        
    };
}