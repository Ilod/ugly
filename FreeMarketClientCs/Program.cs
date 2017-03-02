using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FreeMarket
{
    class MyClient : GameClient
    {
        static void Main(string[] args)
        {
            if (args.Length > 0)
                GameServer.PlayLocalServer(new MyClient(), @"D:\ugly\x64\Debug\Server.exe");
            else
                GameServer.Play(new MyClient());
        }

        public void Cleanup()
        {
        }

        public void InitGame(GameConfig gameConfig, PlayerConfig playerConfig)
        {
        }

        public void PlayTurn(GameState gameState, PlayerState playerState)
        {
        }
    }
}
