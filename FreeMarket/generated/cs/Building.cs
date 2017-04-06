using System;
using System.Collections.Generic;

namespace FreeMarket
{

    public class BuildingType
    {
        
        public int Id;
        public int ActionPointMax;
        public int ActionPointGain;
        public int ResourceCapacity;
        public Action[] Action;
        
    }

    public class BuildingCard
    {
        
        public int Id;
        public BuildingType Building;
        public int Owner;
        
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
        public int ActionPoint;
        public int[] Resource;
        
        public void Execute(Action action, PowerParameter param)
        {
            Console.WriteLine("2 {0} {1} {2} {3}", (action != null) ? (action.Id) : -1, param.Quantity, param.Resource, (param.BuildingTarget != null) ? (param.BuildingTarget.Id) : -1);
        }
    }
}