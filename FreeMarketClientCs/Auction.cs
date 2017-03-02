using System;

namespace FreeMarket
{
    
    public enum AuctionType
    {        
        Building = 0,        
        Unit = 1,        
        Location = 2,
    }

    public class Auction
    {
        public int Id;
        public int Turn;
        public AuctionType Type;
        public int Buyer;
        public int Price;
        
        public void Bid(int amount)
        {
            Console.WriteLine("0 {0}", amount);
        }
    }
}