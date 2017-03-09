using System;
using System.Collections.Generic;

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
        public int MapSizeX;
        public int MapSizeY;
        public int StartMoney;
        public BuildingType[] Building;
        public PlayerConfig[] Player;
        public Auction[] Auction;
        public Auction[] EndedAuction;
        
    }

    public class PlayerState
    {
        public int Id;
        public int Team;
        public int Money;
        public List<Building> Building = new List<Building>();
        
    }

    public class GameState
    {
        public int Turn;
        public Cell[,] Map;
        public Building[] Building;
        public PlayerState[] Player;
        
    }
}