#include "Serializer.h"
#include <cctype>
#include <sstream>

namespace ugly
{
    namespace FreeMarket
    {
        void Serializer::IdMap::Clear()
        {
                playerConfig.clear();
                player.clear();
                auction.clear();
        }

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
                }
                if (*buf)
                    ++buf;
                if (negative)
                    return static_cast<T>(-static_cast<std::int64_t>(data));
                return static_cast<T>(data);
            }

            template<typename T> void SerializeInternal(T& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, Game& gameState, Player& playerState);
            
            template<> void SerializeInternal(PlayerConfig& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, Game& gameState, Player& playerState);
            template<> void SerializeInternal(GameConfig& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, Game& gameState, Player& playerState);
            template<> void SerializeInternal(Player& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, Game& gameState, Player& playerState);
            template<> void SerializeInternal(Game& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, Game& gameState, Player& playerState);
            template<> void SerializeInternal(Auction& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, Game& gameState, Player& playerState);

            template<> void SerializeInternal(PlayerConfig& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, Game& gameState, Player& playerState)
            {
                ids.playerConfig[data.id] = &data;
                {                
                    buffer << data.id << " ";
                }
                {                
                    buffer << data.team << " ";
                }
            }

            template<> void SerializeInternal(GameConfig& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, Game& gameState, Player& playerState)
            {
                {                
                    buffer << data.turns << " ";
                }
                {                
                    buffer << data.turnTimeLimit << " ";
                }
                {                
                    buffer << data.setupTimeLimit << " ";
                }
                {
                    int size0 = (int)(data.player.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.player[idx0], buffer, ids, gameSetup, playerSetup, gameState, playerState);
                    }
                }
            }

            template<> void SerializeInternal(Player& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, Game& gameState, Player& playerState)
            {
                ids.player[data.id] = &data;
                {                
                    buffer << data.id << " ";
                }
                {                
                    buffer << data.team << " ";
                }
                {                
                    buffer << data.money << " ";
                }
            }

            template<> void SerializeInternal(Game& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, Game& gameState, Player& playerState)
            {
                {                
                    buffer << data.turn << " ";
                }
                {
                    int size0 = (int)(data.player.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.player[idx0], buffer, ids, gameSetup, playerSetup, gameState, playerState);
                    }
                }
                {
                    int size0 = (int)(data.activeAuction.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.activeAuction[idx0], buffer, ids, gameSetup, playerSetup, gameState, playerState);
                    }
                }
                {
                    int size0 = (int)(data.endedAuction.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.endedAuction[idx0], buffer, ids, gameSetup, playerSetup, gameState, playerState);
                    }
                }
                {
                    int size0 = (int)(data.futureAuction.size());
                    buffer << size0 << " ";                    bool executeLoop = true;
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {                    
                        if ((executeLoop = (executeLoop && data.futureAuction[idx0].CanSee(gameSetup, playerSetup, gameState, playerState))))
                        {
                            SerializeInternal(data.futureAuction[idx0], buffer, ids, gameSetup, playerSetup, gameState, playerState);
                        }
                    }
                }
            }

            template<> void SerializeInternal(Auction& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, Game& gameState, Player& playerState)
            {
                ids.auction[data.id] = &data;
                {                
                    buffer << data.id << " ";
                }
                {                
                    buffer << data.turn << " ";
                }
                {                
                    buffer << (int)data.type << " ";
                }
                {                
                    buffer << data.buyer << " ";
                }
                {                
                    buffer << data.price << " ";
                }
            }
        }

        std::string Serializer::SerializeSetup(GameConfig& gameSetup, PlayerConfig& playerSetup, Game& gameState, Player& playerState)
        {
            std::stringstream buffer;
            gameSetupId.Clear();
            buffer << playerSetup.id << '\n';
            SerializeInternal(gameSetup, buffer, gameSetupId, gameSetup, playerSetup, gameState, playerState);
            buffer << '\n';
            return buffer.str();
        }

        std::string Serializer::SerializeState(GameConfig& gameSetup, PlayerConfig& playerSetup, Game& gameState, Player& playerState)
        {
            std::stringstream buffer;
            gameStateId.Clear();
            SerializeInternal(gameState, buffer, gameStateId, gameSetup, playerSetup, gameState, playerState);
            buffer << '\n';
            return buffer.str();
        }

        bool Serializer::ExecuteOrder(const std::string& order, GameConfig& gameSetup, Game& gameState, int currentPlayerId)
        {
            const char* buf = order.c_str();
            int _methodId = ReadNext<int>(buf);
            switch (_methodId)
            {
                case 0:
                {
                    std::int32_t argThisId = ReadNext<std::int32_t>(buf);
                    auto argThisIt = gameStateId.auction.find(argThisId);
                    if (argThisIt == gameStateId.auction.end())
                    {
                        argThisIt = gameSetupId.auction.find(argThisId);
                        if (argThisIt == gameSetupId.auction.end())
                            return false;
                    }
                    Auction& argThis = *(argThisIt->second);
                    std::int32_t amount = ReadNext<std::int32_t>(buf);
                    return argThis.Bid(gameSetup, gameSetup.player[currentPlayerId], gameState, gameState.player[currentPlayerId], amount);
                }
                default:
                    return false;
            }
        }
    }
}