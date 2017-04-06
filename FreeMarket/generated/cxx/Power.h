#pragma once
#include <vector>
#include <cstdint>
#include "EnumHelper.h"
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
    
    enum class Owner
    {        
        None = 0,        
        Self = 1,        
        Ally = 2,        
        Opponent = 4,        
        City = 8,
    };
    template<> struct IsFlagEnum<Owner> : std::true_type {};

    struct PowerParameter
    {
        std::int32_t quantity;
        std::int32_t resource;
        Building* buildingTarget;        

        

        PowerParameter();
        
    };

    struct Power
    {
        PowerType type;
        ParameterType quantity;
        std::int32_t quantityForced;
        ParameterType resource;
        std::int32_t resourceForced;
        ParameterType buildingTarget;
        Owner buildingTargetOwner;
        BoostType boost;
        std::int32_t boostPower;
        std::int32_t range;        

        

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