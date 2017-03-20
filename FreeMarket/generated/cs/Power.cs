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

    public class PowerParameter
    {
        
        public int Quantity;
        public int Resource;
        public Building BuildingSource;
        
    }

    public class Power
    {
        
        public PowerType Type;
        public ParameterType Quantity;
        public int QuantityForced;
        public ParameterType Resource;
        public int ResourceForced;
        public ParameterType BuildingSource;
        
    }

    public class Action
    {
        
        public int Id;
        public Power Power = new Power();
        public int ActionPoint;
        public int Cooldown;
        public int TurnLimit;
        
    }
}