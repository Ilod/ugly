#include "Serializer.h"
#include <cctype>
#include <sstream>

namespace ugly
{
    namespace FreeMarket
    {
        void Serializer::IdMap::Clear()
        {
            buildingCard.clear();
            building.clear();
            auction.clear();
        }

        namespace
        {
            template<typename T> void SerializeInternal(T& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            
            template<> void SerializeInternal(PlayerConfig& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(GameConfig& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(PlayerState& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(GameState& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(Cell& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(BuildingType& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(BuildingCard& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(Building& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(Auction& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);

            template<> void SerializeInternal(PlayerConfig& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
                {
                    buffer << data.team << " ";
                }
            }

            template<> void SerializeInternal(GameConfig& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
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
                    buffer << data.mapSizeX << " ";
                }
                {
                    buffer << data.mapSizeY << " ";
                }
                {
                    buffer << data.startMoney << " ";
                }
                {
                    int size0 = (int)(data.building.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.building[idx0], buffer, ids, gameSetup, playerSetup, gameState, playerState);
                    }
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
                    int size0 = (int)(data.auction.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.auction[idx0], buffer, ids, gameSetup, playerSetup, gameState, playerState);
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
            }

            template<> void SerializeInternal(PlayerState& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
                {
                    buffer << data.team << " ";
                }
                {
                    buffer << data.money << " ";
                }
            }

            template<> void SerializeInternal(GameState& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
                {
                    buffer << data.turn << " ";
                }
                {
                    int size0 = (int)(data.map.size());
                    buffer << size0 << " ";
                    int size1 = (int)(size0 == 0 ? 0 : data.map[0].size());
                    buffer << size1 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        for (int idx1 = 0; idx1 < size1; ++idx1)
                        {
                            SerializeInternal(data.map[idx0][idx1], buffer, ids, gameSetup, playerSetup, gameState, playerState);
                        }
                    }
                }
                {
                    int size0 = (int)(data.building.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.building[idx0], buffer, ids, gameSetup, playerSetup, gameState, playerState);
                    }
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

            template<> void SerializeInternal(Cell& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
                {
                    buffer << data.owner << " ";
                }
                {                
                    buffer << (int)data.ownership << " ";
                }
                {                
                    buffer << (int)data.type << " ";
                }
                {
                    buffer << data.price << " ";
                }
            }

            template<> void SerializeInternal(BuildingType& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
            }

            template<> void SerializeInternal(BuildingCard& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
                ids.buildingCard[data.id] = &data;
                {
                    buffer << data.id << " ";
                }
                {
                    if (data.building == nullptr)
                    {
                        buffer << -1 << " ";
                    }
                    else
                    {                
                        buffer << data.building->id << " ";
                    }
                }
            }

            template<> void SerializeInternal(Building& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
                ids.building[data.id] = &data;
                {
                    buffer << data.id << " ";
                }
                {
                    if (data.type == nullptr)
                    {
                        buffer << -1 << " ";
                    }
                    else
                    {                
                        buffer << data.type->id << " ";
                    }
                }
                {
                    if (data.position == nullptr)
                    {
                        buffer << -1 << " ";
                    }
                    else
                    {                
                        buffer << data.position->x << " ";
                    }
                    if (data.position == nullptr)
                    {
                        buffer << -1 << " ";
                    }
                    else
                    {                
                        buffer << data.position->y << " ";
                    }
                }
                {
                    buffer << data.owner << " ";
                }
            }

            template<> void SerializeInternal(Auction& data, std::stringstream& buffer, Serializer::IdMap& ids, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
                ids.auction[data.id] = &data;
                {
                    buffer << data.id << " ";
                }
                {                
                    buffer << (int)data.type << " ";
                }
                {
                    buffer << data.price << " ";
                }
                {
                    buffer << data.seller << " ";
                }
                {
                    buffer << data.buyer << " ";
                }
                {
                    buffer << data.turn << " ";
                }
                {
                    if (data.building == nullptr)
                    {
                        buffer << -1 << " ";
                    }
                    else
                    {                
                        buffer << data.building->id << " ";
                    }
                }
            }
            
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
            
            template<class T> void Deserialize(T& data, const char*& buf, GameConfig* gameSetup, GameState* gameState, Serializer::IdMap* idSetup, Serializer::IdMap* idState)
            {
                data = ReadNext<T>(buf);
            }
        }
        
        std::string Serializer::SerializeSetup(GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
        {
            std::stringstream buffer;
            gameSetupId.Clear();
            buffer << playerSetup.id << '\n';
            SerializeInternal(gameSetup, buffer, gameSetupId, gameSetup, playerSetup, gameState, playerState);
            buffer << '\n';
            return buffer.str();
        }

        std::string Serializer::SerializeState(GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
        {
            std::stringstream buffer;
            gameStateId.Clear();
            SerializeInternal(gameState, buffer, gameStateId, gameSetup, playerSetup, gameState, playerState);
            buffer << '\n';
            return buffer.str();
        }

        bool Serializer::ExecuteOrder(const std::string& order, GameConfig& gameSetup, GameState& gameState, int currentPlayerId)
        {
            const char* buf = order.c_str();
            int _methodId = ReadNext<int>(buf);
            switch (_methodId)
            {
                case 0: // Cell::Buy
                {
                    int argThis_idx0 = ReadNext<int>(buf);
                    int argThis_idx1 = ReadNext<int>(buf);
                    if (!(argThis_idx0 >= 0 && argThis_idx1 >= 0 && gameState.map.size() > argThis_idx0 && gameState.map[argThis_idx0].size() > argThis_idx1))
                        return false;
                    Cell& argThis = gameState.map[argThis_idx0][argThis_idx1];
                    return argThis.Buy(gameSetup, gameSetup.player[currentPlayerId], gameState, gameState.player[currentPlayerId]);
                }
                case 1: // BuildingCard::Build
                {                    
                    std::int32_t argThisId = ReadNext<std::int32_t>(buf);
                    auto argThisIt = gameStateId.buildingCard.find(argThisId);
                    if (argThisIt == gameStateId.buildingCard.end())
                    {
                        argThisIt = gameSetupId.buildingCard.find(argThisId);
                        if (argThisIt == gameSetupId.buildingCard.end())
                            return false;
                    }
                    BuildingCard& argThis = *(argThisIt->second);
                            int position_idx0 = ReadNext<int>(buf);
                            int position_idx1 = ReadNext<int>(buf);
                            if (!(position_idx0 >= 0 && position_idx1 >= 0 && gameState.map.size() > position_idx0 && gameState.map[position_idx0].size() > position_idx1))
                                return false;
                            Cell& position = gameState.map[position_idx0][position_idx1];
                    return argThis.Build(gameSetup, gameSetup.player[currentPlayerId], gameState, gameState.player[currentPlayerId], position);
                }
                case 2: // Auction::Bid
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
                    std::int32_t money = ReadNext<std::int32_t>(buf);
                    return argThis.Bid(gameSetup, gameSetup.player[currentPlayerId], gameState, gameState.player[currentPlayerId], money);
                }
                default:
                    return false;
            }
        }
    }
}