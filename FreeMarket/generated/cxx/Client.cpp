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
        
        template<class T> void Deserialize(T& data, const char*& buf, GameConfig* gameSetup, GameState* gameState)
        {
            data = ReadNext<T>(buf);
        }    
        template<> void Deserialize(PlayerConfig& data, const char*& buf, GameConfig* gameSetup, GameState* gameState);    
        template<> void Deserialize(GameConfig& data, const char*& buf, GameConfig* gameSetup, GameState* gameState);    
        template<> void Deserialize(PlayerState& data, const char*& buf, GameConfig* gameSetup, GameState* gameState);    
        template<> void Deserialize(GameState& data, const char*& buf, GameConfig* gameSetup, GameState* gameState);    
        template<> void Deserialize(Cell& data, const char*& buf, GameConfig* gameSetup, GameState* gameState);    
        template<> void Deserialize(BuildingType& data, const char*& buf, GameConfig* gameSetup, GameState* gameState);    
        template<> void Deserialize(BuildingCard& data, const char*& buf, GameConfig* gameSetup, GameState* gameState);    
        template<> void Deserialize(Building& data, const char*& buf, GameConfig* gameSetup, GameState* gameState);    
        template<> void Deserialize(Power& data, const char*& buf, GameConfig* gameSetup, GameState* gameState);    
        template<> void Deserialize(Action& data, const char*& buf, GameConfig* gameSetup, GameState* gameState);    
        template<> void Deserialize(Auction& data, const char*& buf, GameConfig* gameSetup, GameState* gameState);
        
        template<> void Deserialize(PlayerConfig& data, const char*& buf, GameConfig* gameSetup, GameState* gameState)
        {
            {
                auto& member = data.team;
                Deserialize(member, buf, gameSetup, gameState);
            }
        }
        
        template<> void Deserialize(GameConfig& data, const char*& buf, GameConfig* gameSetup, GameState* gameState)
        {
            {
                auto& member = data.turns;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.turnTimeLimit;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.setupTimeLimit;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.mapSizeX;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.mapSizeY;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.startMoney;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.resourceCount;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.building;
                int size0 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                    Deserialize(array1, buf, gameSetup, gameState);
                    array1.id = idx0;
                }
            }
            {
                auto& member = data.player;
                int size0 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                    Deserialize(array1, buf, gameSetup, gameState);
                    array1.id = idx0;
                }
            }
        }
        
        template<> void Deserialize(PlayerState& data, const char*& buf, GameConfig* gameSetup, GameState* gameState)
        {
            {
                auto& member = data.team;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.money;
                Deserialize(member, buf, gameSetup, gameState);
            }
        }
        
        template<> void Deserialize(GameState& data, const char*& buf, GameConfig* gameSetup, GameState* gameState)
        {
            {
                auto& member = data.turn;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.map;
                int size0 = ReadNext<int>(buf);
                int size1 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                    array1.resize(size1);
                }
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                    for (int idx1 = 0; idx1 < size1; ++idx1)
                    {
                        auto& array2 = array1[idx1];
                        Deserialize(array2, buf, gameSetup, gameState);
                        array2.x = idx0;
                        array2.y = idx1;
                    }
                }
            }
            {
                auto& member = data.resourcePrice;
                int size0 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                    Deserialize(array1, buf, gameSetup, gameState);
                }
            }
            {
                auto& member = data.resourceEvolution;
                int size0 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                    Deserialize(array1, buf, gameSetup, gameState);
                }
            }
            {
                auto& member = data.building;
                int size0 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                    Deserialize(array1, buf, gameSetup, gameState);
                    if (array1.position->x >= 0 && array1.position->y >= 0)
                    {
                        (*gameState).map[array1.position->x][array1.position->y].building = &array1;
                    }
                    if (array1.owner >= 0)
                    {
                        (*gameState).player[array1.owner].building.push_back(&array1);
                    }
                }
            }
            {
                auto& member = data.buildingCard;
                int size0 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                    Deserialize(array1, buf, gameSetup, gameState);
                    if (array1.owner >= 0)
                    {
                        (*gameState).player[array1.owner].buildingCard.push_back(&array1);
                    }
                }
            }
            {
                auto& member = data.player;
                int size0 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                    Deserialize(array1, buf, gameSetup, gameState);
                    array1.id = idx0;
                }
            }
            {
                auto& member = data.auction;
                int size0 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                    Deserialize(array1, buf, gameSetup, gameState);
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
                    Deserialize(array1, buf, gameSetup, gameState);
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
                    Deserialize(array1, buf, gameSetup, gameState);
                }
            }
        }
        
        template<> void Deserialize(Cell& data, const char*& buf, GameConfig* gameSetup, GameState* gameState)
        {
            {
                auto& member = data.owner;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.ownership;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.type;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.price;
                Deserialize(member, buf, gameSetup, gameState);
            }
        }
        
        template<> void Deserialize(BuildingType& data, const char*& buf, GameConfig* gameSetup, GameState* gameState)
        {
            {
                auto& member = data.actionPointMax;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.actionPointGain;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.resourceCapacity;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.action;
                int size0 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                    Deserialize(array1, buf, gameSetup, gameState);
                }
            }
        }
        
        template<> void Deserialize(BuildingCard& data, const char*& buf, GameConfig* gameSetup, GameState* gameState)
        {
            {
                auto& member = data.id;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.building;
                int member_idx0 = ReadNext<int>(buf);
                if (member_idx0 != -1)
                {
                    member = &(*gameSetup).building[member_idx0];
                }
            }
            {
                auto& member = data.owner;
                Deserialize(member, buf, gameSetup, gameState);
            }
        }
        
        template<> void Deserialize(Building& data, const char*& buf, GameConfig* gameSetup, GameState* gameState)
        {
            {
                auto& member = data.id;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.type;
                int member_idx0 = ReadNext<int>(buf);
                if (member_idx0 != -1)
                {
                    member = &(*gameSetup).building[member_idx0];
                }
            }
            {
                auto& member = data.position;
                int member_idx0 = ReadNext<int>(buf);
                int member_idx1 = ReadNext<int>(buf);
                if (member_idx0 != -1)
                {
                    member = &(*gameState).map[member_idx0][member_idx1];
                }
            }
            {
                auto& member = data.owner;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.actionPoint;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.resource;
                int size0 = ReadNext<int>(buf);
                auto& array0 = member;
                array0.resize(size0);
                for (int idx0 = 0; idx0 < size0; ++idx0)
                {
                    auto& array1 = array0[idx0];
                    Deserialize(array1, buf, gameSetup, gameState);
                }
            }
        }
        
        template<> void Deserialize(Power& data, const char*& buf, GameConfig* gameSetup, GameState* gameState)
        {
            {
                auto& member = data.type;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.quantity;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.quantityForced;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.resource;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.resourceForced;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.buildingTarget;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.buildingTargetOwner;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.boost;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.boostPower;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.range;
                Deserialize(member, buf, gameSetup, gameState);
            }
        }
        
        template<> void Deserialize(Action& data, const char*& buf, GameConfig* gameSetup, GameState* gameState)
        {
            {
                auto& member = data.id;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.power;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.actionPoint;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.priority;
                Deserialize(member, buf, gameSetup, gameState);
            }
        }
        
        template<> void Deserialize(Auction& data, const char*& buf, GameConfig* gameSetup, GameState* gameState)
        {
            {
                auto& member = data.id;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.type;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.price;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.seller;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.buyer;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.turn;
                Deserialize(member, buf, gameSetup, gameState);
            }
            {
                auto& member = data.building;
                int member_idx0 = ReadNext<int>(buf);
                if (member_idx0 != -1)
                {
                    member = &(*gameSetup).building[member_idx0];
                }
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
        Deserialize(data, buf, &data, nullptr);
        client.InitGame(data, data.player[playerId]);
        for (;;)
        {
            printf("EOT\n");
            std::getline(std::cin, line);
            if (line.compare(0, 3, "EOT") == 0)
                break;
            buf = line.c_str();
            GameState turn;
            Deserialize(turn, buf, &data, &turn);
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