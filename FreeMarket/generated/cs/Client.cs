using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

namespace FreeMarket
{
    public interface GameClient
    {
        void InitGame(GameConfig gameConfig, PlayerConfig playerConfig);
        void PlayTurn(GameState gameState, PlayerState playerState);
        void Cleanup();
    }

    public static partial class GameServer
    {
        public static void Play(GameClient client)
        {
            Tuple<GameConfig, PlayerConfig> setup = ReadSetup();
            int playerId = setup.Item2.Id;
            client.InitGame(setup.Item1, setup.Item2);
            GameState turn = null;
            while ((turn = ReadTurn(setup.Item1)) != null)
            {
                client.PlayTurn(turn, turn.Player[playerId]);
            }
            client.Cleanup();
            Console.WriteLine("EOT");
        }
        
        public static IList<Tuple<int, int>> PlayLocalServer(GameClient client, string serverPath, IList<string> otherPlayers = null, string game = "FreeMarket", string serverArgs = "")
        {
            return PlayLocalServerCommandLine(client, serverPath, string.Format("-game \"{0}\" -player parent; {1} {2}", game, string.Join(" ", (otherPlayers ?? Enumerable.Empty<string>()).Select(player => string.Format("-player \"{0}\"", player))), serverArgs));
        }

        public static IList<Tuple<int, int>> PlayLocalServerCommandLine(GameClient client, string serverPath, string commandLine)
        {
            List<Tuple<int, int>> results = new List<Tuple<int, int>>();
            if (!StartLocalServer(serverPath, commandLine))
                return results;
            Play(client);
            string[] tokens = Console.ReadLine().Split(new char[] { ' ' });
            for (int i = 0; i < tokens.Length / 2; ++i)
                results.Add(Tuple.Create(int.Parse(tokens[i*2]), int.Parse(tokens[i*2+1])));
            return results;
        }
    }
}