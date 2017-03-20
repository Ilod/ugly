using System;
using System.IO;

namespace FreeMarket
{
    public static partial class GameServer
    {
        private static GameState ReadTurn(GameConfig gameSetup)
        {
            Console.WriteLine("EOT");
            string line = Console.ReadLine();
            if (line.StartsWith("EOT"))
                return null;
            Parser parser = new Parser(line);
            GameState turn = new GameState();
            parser.Deserialize(turn, gameSetup, turn);
            return turn;
        }
        
        private static Tuple<GameConfig, PlayerConfig> ReadSetup()
        {
            string line = Console.ReadLine();
            Parser parser = new Parser(line);
            int playerId = parser.ReadNextInt();
            line = Console.ReadLine();
            parser = new Parser(line);
            GameConfig data = new GameConfig();
            parser.Deserialize(data, data, null);
            return Tuple.Create(data, data.Player[playerId]);
        }

        private class Parser
        {
            private string Line;
            private int Index = 0;

            public Parser(string line)
            {
                Line = line;
            }

            public long ReadNextLong()
            {
                long data = 0;
                bool negative = false;
                if (Index < Line.Length && Line[Index] == '-')
                {
                    negative = true;
                    ++Index;
                }

                while (Index < Line.Length && Line[Index] >= '0' && Line[Index] <= '9')
                {
                    data *= 10;
                    data += (long)(Line[Index] - '0');
                    ++Index;
                }
                ++Index;
                return negative ? -data : data;
            }
            
            public ulong ReadNextUlong()
            {
                ulong data = 0;

                while (Index < Line.Length && Line[Index] >= '0' && Line[Index] <= '9')
                {
                    data *= 10;
                    data += (ulong)(Line[Index] - '0');
                    ++Index;
                }
                ++Index;
                return data;
            }
            
            public int ReadNextInt()
            {
                return (int)ReadNextLong();
            }
            
            public short ReadNextShort()
            {
                return (short)ReadNextLong();
            }
            
            public sbyte ReadNextSbyte()
            {
                return (sbyte)ReadNextLong();
            }
            
            public uint ReadNextUint()
            {
                return (uint)ReadNextUlong();
            }
            
            public ushort ReadNextUshort()
            {
                return (ushort)ReadNextUlong();
            }
            
            public byte ReadNextByte()
            {
                return (byte)ReadNextUlong();
            }
            
            public char ReadNextChar()
            {
                return (char)ReadNextUlong();
            }
            
            public bool ReadNextBool()
            {
                return ReadNextLong() != 0;
            }

            public void Deserialize(PlayerConfig data, GameConfig gameSetup, GameState gameState)
            {
                {
                    data.Team = ReadNextInt();
                }           
            }

            public void Deserialize(GameConfig data, GameConfig gameSetup, GameState gameState)
            {
                {
                    data.Turns = ReadNextInt();
                }
                {
                    data.TurnTimeLimit = ReadNextInt();
                }
                {
                    data.SetupTimeLimit = ReadNextInt();
                }
                {
                    data.MapSizeX = ReadNextInt();
                }
                {
                    data.MapSizeY = ReadNextInt();
                }
                {
                    data.StartMoney = ReadNextInt();
                }
                {
                    data.ResourceCount = ReadNextInt();
                }
                {
                    int size0 = ReadNextInt();
                    data.Building = new BuildingType[size0];
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        BuildingType element = new BuildingType();
                        Deserialize(element, gameSetup, gameState);
                        element.Id = idx0;
                        data.Building[idx0] = element;
                    }
                }
                {
                    int size0 = ReadNextInt();
                    data.Player = new PlayerConfig[size0];
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        PlayerConfig element = new PlayerConfig();
                        Deserialize(element, gameSetup, gameState);
                        element.Id = idx0;
                        data.Player[idx0] = element;
                    }
                }           
            }

            public void Deserialize(PlayerState data, GameConfig gameSetup, GameState gameState)
            {
                {
                    data.Team = ReadNextInt();
                }
                {
                    data.Money = ReadNextInt();
                }           
            }

            public void Deserialize(GameState data, GameConfig gameSetup, GameState gameState)
            {
                {
                    data.Turn = ReadNextInt();
                }
                {
                    int size0 = ReadNextInt();
                    int size1 = ReadNextInt();
                    data.Map = new Cell[size0, size1];
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        for (int idx1 = 0; idx1 < size1; ++idx1)
                        {
                            Cell element = new Cell();
                            Deserialize(element, gameSetup, gameState);
                            element.X = idx0;
                            element.Y = idx1;
                            data.Map[idx0, idx1] = element;
                        }
                    }
                }
                {
                    int size0 = ReadNextInt();
                    data.ResourcePrice = new int[size0];
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        data.ResourcePrice[idx0] = ReadNextInt();
                    }
                }
                {
                    int size0 = ReadNextInt();
                    data.ResourceEvolution = new PriceEvolution[size0];
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        data.ResourceEvolution[idx0] = (PriceEvolution)ReadNextInt();
                    }
                }
                {
                    int size0 = ReadNextInt();
                    data.Building = new Building[size0];
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        Building element = new Building();
                        Deserialize(element, gameSetup, gameState);
                        if (element.Position.X >= 0 && element.Position.Y >= 0)
                        {
                            gameState.Map[element.Position.X, element.Position.Y].Building = element;
                        }
                        if (element.Owner >= 0)
                        {
                            gameState.Player[element.Owner].Building.Add(element);
                        }
                        data.Building[idx0] = element;
                    }
                }
                {
                    int size0 = ReadNextInt();
                    data.Player = new PlayerState[size0];
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        PlayerState element = new PlayerState();
                        Deserialize(element, gameSetup, gameState);
                        element.Id = idx0;
                        data.Player[idx0] = element;
                    }
                }
                {
                    int size0 = ReadNextInt();
                    data.Auction = new Auction[size0];
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        Auction element = new Auction();
                        Deserialize(element, gameSetup, gameState);
                        data.Auction[idx0] = element;
                    }
                }
                {
                    int size0 = ReadNextInt();
                    data.EndedAuction = new Auction[size0];
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        Auction element = new Auction();
                        Deserialize(element, gameSetup, gameState);
                        data.EndedAuction[idx0] = element;
                    }
                }           
            }

            public void Deserialize(Cell data, GameConfig gameSetup, GameState gameState)
            {
                {
                    data.Owner = ReadNextInt();
                }
                {
                    data.Ownership = (Ownership)ReadNextInt();
                }
                {
                    data.Type = (CellType)ReadNextInt();
                }
                {
                    data.Price = ReadNextInt();
                }           
            }

            public void Deserialize(BuildingType data, GameConfig gameSetup, GameState gameState)
            {
                {
                    data.ActionPoint = ReadNextInt();
                }
                {
                    int size0 = ReadNextInt();
                    data.Action = new Action[size0];
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        Action element = new Action();
                        Deserialize(element, gameSetup, gameState);
                        data.Action[idx0] = element;
                    }
                }           
            }

            public void Deserialize(Building data, GameConfig gameSetup, GameState gameState)
            {
                {
                    data.Id = ReadNextInt();
                }
                {
                    int classIdx0 = ReadNextInt();                            
                    if (classIdx0 != -1)
                    {
                        data.Type = gameSetup.Building[classIdx0];
                    }
                }
                {
                    int classIdx0 = ReadNextInt();
                    int classIdx1 = ReadNextInt();                            
                    if (classIdx0 != -1)
                    {
                        data.Position = gameState.Map[classIdx0, classIdx1];
                    }
                }
                {
                    data.Owner = ReadNextInt();
                }           
            }

            public void Deserialize(Power data, GameConfig gameSetup, GameState gameState)
            {
                {
                    data.Type = (PowerType)ReadNextInt();
                }
                {
                    data.Quantity = (ParameterType)ReadNextInt();
                }
                {
                    data.QuantityForced = ReadNextInt();
                }
                {
                    data.Resource = (ParameterType)ReadNextInt();
                }
                {
                    data.ResourceForced = ReadNextInt();
                }
                {
                    data.BuildingSource = (ParameterType)ReadNextInt();
                }           
            }

            public void Deserialize(Action data, GameConfig gameSetup, GameState gameState)
            {
                {
                    data.Id = ReadNextInt();
                }
                {
                    Deserialize(data.Power, gameSetup, gameState);
                }
                {
                    data.ActionPoint = ReadNextInt();
                }
                {
                    data.Cooldown = ReadNextInt();
                }
                {
                    data.TurnLimit = ReadNextInt();
                }           
            }

            public void Deserialize(Auction data, GameConfig gameSetup, GameState gameState)
            {
                {
                    data.Id = ReadNextInt();
                }
                {
                    data.Type = (AuctionType)ReadNextInt();
                }
                {
                    data.Price = ReadNextInt();
                }
                {
                    data.Seller = ReadNextInt();
                }
                {
                    data.Buyer = ReadNextInt();
                }
                {
                    data.Turn = ReadNextInt();
                }
                {
                    int classIdx0 = ReadNextInt();                            
                    if (classIdx0 != -1)
                    {
                        data.Building = gameSetup.Building[classIdx0];
                    }
                }           
            }
        }
    }
}