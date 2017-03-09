using System;
using System.Collections.Generic;

namespace FreeMarket
{

    public class BuildingType
    {
        public int Id;
        
    }

    public class BuildingCard
    {
        public int Id;
        public BuildingType Building;
        
        public void Build(Cell position)
        {
            Console.WriteLine("1 {0} {1}", (position != null) ? (position.X) : -1, (position != null) ? (position.Y) : -1);
        }
    }

    public class Building
    {
        public int Id;
        public BuildingType Type;
        public Cell Position;
        public int Owner;
        
    }
}