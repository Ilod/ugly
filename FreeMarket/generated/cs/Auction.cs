using System;
using System.Collections.Generic;

namespace FreeMarket
{
    
    public enum AuctionType
    {
        Building = 0,
    }

    public class Auction
    {
        
        public int Id;
        public AuctionType Type;
        public int Price;
        public int Seller;
        public int Buyer;
        public int Turn;
        public BuildingType Building;
        
        public void Bid(int money)
        {
            Console.WriteLine("3 {0} {1}", (this != null) ? (this.Id) : -1, money);
        }
    }
}