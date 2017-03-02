using System;
using System.IO;

namespace FreeMarket
{
    public static partial class GameServer
    {
        private static GameState ReadTurn()
        {
            Console.WriteLine("EOT");
            string line = Console.ReadLine();
            if (line.StartsWith("EOT"))
                return null;
            Parser parser = new Parser(line);
            GameState turn = new GameState();
            parser.Deserialize(turn);
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
            parser.Deserialize(data);
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

            public void Deserialize(PlayerConfig data)
            {
                {
                    data.Id = ReadNextInt();
                }
                {
                    data.Team = ReadNextInt();
                }           
            }

            public void Deserialize(GameConfig data)
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
                    int size0 = ReadNextInt();
                    data.Player = new PlayerConfig[size0];
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        PlayerConfig element = new PlayerConfig();
                        Deserialize(element);
                        data.Player[idx0] = element;
                    }
                }           
            }

            public void Deserialize(PlayerState data)
            {
                {
                    data.Id = ReadNextInt();
                }
                {
                    data.Team = ReadNextInt();
                }
                {
                    data.Money = ReadNextInt();
                }           
            }

            public void Deserialize(GameState data)
            {
                {
                    data.Turn = ReadNextInt();
                }
                {
                    int size0 = ReadNextInt();
                    data.Player = new PlayerState[size0];
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        PlayerState element = new PlayerState();
                        Deserialize(element);
                        data.Player[idx0] = element;
                    }
                }
                {
                    int size0 = ReadNextInt();
                    data.ActiveAuction = new Auction[size0];
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        Auction element = new Auction();
                        Deserialize(element);
                        data.ActiveAuction[idx0] = element;
                    }
                }
                {
                    int size0 = ReadNextInt();
                    data.EndedAuction = new Auction[size0];
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        Auction element = new Auction();
                        Deserialize(element);
                        data.EndedAuction[idx0] = element;
                    }
                }
                {
                    int size0 = ReadNextInt();
                    data.FutureAuction = new Auction[size0];
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        Auction element = new Auction();
                        Deserialize(element);
                        data.FutureAuction[idx0] = element;
                    }
                }           
            }

            public void Deserialize(Auction data)
            {
                {
                    data.Id = ReadNextInt();
                }
                {
                    data.Turn = ReadNextInt();
                }
                {
                    data.Type = (AuctionType)ReadNextInt();
                }
                {
                    data.Buyer = ReadNextInt();
                }
                {
                    data.Price = ReadNextInt();
                }           
            }
        }
    }
}