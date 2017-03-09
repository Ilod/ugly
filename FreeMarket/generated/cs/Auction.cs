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
            Console.WriteLine("2 {0}", money);
        }
    }
}