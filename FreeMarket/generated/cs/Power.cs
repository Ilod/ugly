using System;
using System.Collections.Generic;

namespace FreeMarket
{
    
    public enum ParameterType
    {
        None = 0,
        Choice = 1,
        Forced = 2,
        Random = 3,
        Self = 4,
        All = 5,
    }
    
    public enum PowerType
    {
        ProduceResource = 0,
        SellResource = 1,
    }
    
    public enum BoostType
    {
        None = 0,
        Fixed = 1,
        Percent = 2,
    }
    
    [Flags]
    public enum Owner
    {
        None = 0,
        Self = 1,
        Ally = 2,
        Opponent = 4,
        City = 8,
    }

    public class PowerParameter
    {
        
        public int Quantity;
        public int Resource;
        public Building BuildingTarget;
        
    }

    public class Power
    {
        
        public PowerType Type;
        public ParameterType Quantity;
        public int QuantityForced;
        public ParameterType Resource;
        public int ResourceForced;
        public ParameterType BuildingTarget;
        public Owner BuildingTargetOwner;
        public BoostType Boost;
        public int BoostPower;
        public int Range;
        
    }

    public class Action
    {
        
        public int Id;
        public Power Power = new Power();
        public int ActionPoint;
        public int Priority;
        
    }
}