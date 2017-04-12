using System;
using System.Collections.Generic;

namespace FreeMarket
{
    
    public enum Ownership
    {
        None = 0,
        Preempt = 1,
        Own = 2,
    }
    
    public enum CellType
    {
        Road = 0,
        House = 1,
        Park = 2,
        Building = 3,
        Ruins = 4,
        Work = 5,
    }

    public class Cell
    {
        
        public int X;
        public int Y;
        public int Owner;
        public Ownership Ownership;
        public CellType Type;
        public Building Building;
        public int Price;
        
        public void Buy()
        {
            Console.WriteLine("0 {0} {1}", (this != null) ? (this.X) : -1, (this != null) ? (this.Y) : -1);
        }
    }
}