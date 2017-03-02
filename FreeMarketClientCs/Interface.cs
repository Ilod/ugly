using System;

namespace FreeMarket
{

    public class PlayerConfig
    {
        public int Id;
        public int Team;
        
    }

    public class GameConfig
    {
        public int Turns;
        public int TurnTimeLimit;
        public int SetupTimeLimit;
        public PlayerConfig[] Player;
        
    }

    public class PlayerState
    {
        public int Id;
        public int Team;
        public int Money;
        
    }

    public class GameState
    {
        public int Turn;
        public PlayerState[] Player;
        public Auction[] ActiveAuction;
        public Auction[] EndedAuction;
        public Auction[] FutureAuction;
        
    }
}