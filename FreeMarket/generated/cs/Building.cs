using System;
using System.Collections.Generic;

namespace FreeMarket
{

    public class BuildingType
    {
        public int Id;
        
    }

    public class Building
    {
        public int Id;
        public BuildingType Type;
        public int X;
        public int Y;
        public int Owner;
        
    }
}