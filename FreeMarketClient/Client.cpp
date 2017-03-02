#include "Client.h"
#include <string>
#include <iostream>
#include <cstdint>
#include <cctype>
#include <sstream>

namespace FreeMarket
{
    GameClient::~GameClient() {}

    namespace
    {
        template<class T> T ReadNext(const char*& buf)
        {
            std::uint64_t data = 0;
            bool negative = false;
            if (*buf == '-')
            {
                negative = true;
                ++buf;
            }
            while (std::isdigit(*buf))
            {
                data *= 10;
                data += ((*buf) - '0');
                ++buf;
            }
            if (*buf)
                ++buf;
            if (negative)
                return static_cast<T>(-static_cast<std::int64_t>(data));
            return static_cast<T>(data);
        }

        template<class T> void Deserialize(T& data, const char*& buf)
        {
            data = ReadNext<T>(buf);
        }
        template<> void Deserialize(PlayerConfig& data, const char*& buf);
        template<> void Deserialize(GameConfig& data, const char*& buf);
        template<> void Deserialize(Player& data, const char*& buf);
        template<> void Deserialize(Game& data, const char*& buf);
        template<> void Deserialize(Auction& data, const char*& buf);

        template<> void Deserialize(PlayerConfig& data, const char*& buf)
        {
            {
                auto& member = data.id;
                Deserialize(member, buf);
            }
            {
                auto& member = data.team;
                Deserialize(member, buf);
            }
        }

        template<> void Deserialize(GameConfig& data, const char*& buf)
        {
            {
                auto& member = data.turns;
                Deserialize(member, buf);
            }
            {
                auto& member = data.turnTimeLimit;
                Deserialize(member, buf);
            }
            {
                auto& member = data.setupTimeLimit;
                Deserialize(member, buf);
            }
            {
                auto& member = data.player;
                int size0 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                        Deserialize(array1, buf);
                }
            }
        }

        template<> void Deserialize(Player& data, const char*& buf)
        {
            {
                auto& member = data.id;
                Deserialize(member, buf);
            }
            {
                auto& member = data.team;
                Deserialize(member, buf);
            }
            {
                auto& member = data.money;
                Deserialize(member, buf);
            }
        }

        template<> void Deserialize(Game& data, const char*& buf)
        {
            {
                auto& member = data.turn;
                Deserialize(member, buf);
            }
            {
                auto& member = data.player;
                int size0 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                        Deserialize(array1, buf);
                }
            }
            {
                auto& member = data.activeAuction;
                int size0 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                        Deserialize(array1, buf);
                }
            }
            {
                auto& member = data.endedAuction;
                int size0 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                        Deserialize(array1, buf);
                }
            }
            {
                auto& member = data.futureAuction;
                int size0 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                        Deserialize(array1, buf);
                }
            }
        }

        template<> void Deserialize(Auction& data, const char*& buf)
        {
            {
                auto& member = data.id;
                Deserialize(member, buf);
            }
            {
                auto& member = data.turn;
                Deserialize(member, buf);
            }
            {
                auto& member = data.type;
                Deserialize(member, buf);
            }
            {
                auto& member = data.buyer;
                Deserialize(member, buf);
            }
            {
                auto& member = data.price;
                Deserialize(member, buf);
            }
        }
    }

    void GameServer::Play(GameClient& client)
    {
        std::string line;
        std::getline(std::cin, line);
        const char* buf = line.c_str();
        int playerId = ReadNext<int>(buf);
        std::getline(std::cin, line);
        buf = line.c_str();
        GameConfig data;
        Deserialize(data, buf);
        client.InitGame(data, data.player[playerId]);
        for (;;)
        {
            printf("EOT\n");
            std::getline(std::cin, line);
            if (line.compare(0, 3, "EOT") == 0)
                break;
            buf = line.c_str();
            Game turn;
            Deserialize(turn, buf);
            client.PlayTurn(turn, turn.player[playerId]);
        }
        client.Cleanup();
        printf("EOT\n");
    }

    std::vector<std::pair<int, int>> GameServer::PlayLocalServer(GameClient& client, const std::string& serverPath, const std::vector<std::string>& otherPlayers, const std::string& game, const std::string& serverArgs)
    {
        std::stringstream commandLine;
        commandLine << '"' << serverPath << "\" -game \"" << game << "\" -player parent;";
        for (const std::string& player : otherPlayers)
            commandLine << " -player \"" << player << '"';
        if (!serverArgs.empty())
            commandLine << ' ' << serverArgs;
        return PlayLocalServerCommandLine(client, commandLine.str());
    }

    std::vector<std::pair<int, int>> GameServer::PlayLocalServerCommandLine(GameClient& client, const std::string& commandLine)
    {
        if (!StartLocalServer(commandLine))
            return {};
        Play(client);
        std::string line;
        std::getline(std::cin, line);
        const char* buf = line.c_str();
        std::vector<std::pair<int, int>> results;
        for (;;)
        {
            int rank = ReadNext<int>(buf);
            if (rank == 0)
                return results;
            results.push_back({rank, ReadNext<int>(buf)});
        }
    }
}