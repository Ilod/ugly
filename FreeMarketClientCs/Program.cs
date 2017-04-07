using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FreeMarket
{
    public static class RandomHelper
    {
        public static T Next<T>(this Random rnd, IEnumerable<T> list)
        {
            return list.ElementAt(rnd.Next(list.Count()));
        }
    }

    class MyClient : GameClient
    {
        static void Main(string[] args)
        {
            if (args.Length > 0)
                GameServer.PlayLocalServer(new MyClient(), @"D:\ugly\x64\Debug\Server.exe");
            else
                GameServer.Play(new MyClient());
        }

        private GameConfig gameSetup;

        public void Cleanup()
        {
        }

        public void InitGame(GameConfig gameConfig, PlayerConfig playerConfig)
        {
            gameSetup = gameConfig;
        }

        public void PlayTurn(GameState gameState, PlayerState playerState)
        {
            if (gameState.Auction.Length != 0)
            {
                int moneyByAuction = playerState.Money / (2 * gameState.Auction.Length);
                if (moneyByAuction > 0)
                {
                    foreach (Auction auction in gameState.Auction)
                    {
                        auction.Bid(moneyByAuction);
                    }
                }
            }
            foreach (Building building in playerState.Building)
            {
                int actionPoints = building.ActionPoint;
                foreach (Action action in building.Type.Action)
                {
                    if (action.Power.Type == PowerType.ProduceResource && action.Power.BuildingTarget == ParameterType.Self)
                    {
                        while (building.ActionPoint >= action.ActionPoint)
                        {
                            PowerParameter pp = new PowerParameter();
                            if (action.Power.Resource == ParameterType.Choice)
                                pp.Resource = 0;
                            building.Execute(action, pp);
                            building.ActionPoint -= action.ActionPoint;
                        }
                    }
                }
                foreach (Action action in building.Type.Action)
                {
                    if (action.Power.Type == PowerType.SellResource)
                    {
                        while (building.ActionPoint >= action.ActionPoint)
                        {
                            PowerParameter pp = new PowerParameter();
                            if (action.Power.Quantity == ParameterType.Choice)
                                pp.Quantity = (action.Power.QuantityForced > 0 ? action.Power.QuantityForced : 100);
                            if (action.Power.Resource == ParameterType.Choice)
                                pp.Resource = new Random().Next(0, gameSetup.ResourceCount);
                            if (action.Power.BuildingTarget == ParameterType.Choice)
                            {
                                if (action.Power.Range < 0)
                                    pp.BuildingTarget = new Random().Next(playerState.Building);
                                else
                                    pp.BuildingTarget = new Random().Next(playerState.Building.Where(b => (Math.Abs(b.Position.X - building.Position.X) + Math.Abs(b.Position.Y - building.Position.Y)) <= action.Power.Range));
                            }
                            building.Execute(action, pp);
                            building.ActionPoint -= action.ActionPoint;
                        }
                    }
                }
            }
        }
    }
}
