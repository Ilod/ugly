#include "Serializer.h"
#include <cctype>
#include <sstream>

namespace ugly
{
    namespace FreeMarket
    {
        namespace
        {
            template<typename T> void SerializeInternal(T& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            
            template<> void SerializeInternal(PlayerConfig& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(GameConfig& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(PlayerState& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(GameState& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(Cell& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(BuildingType& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(BuildingCard& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(Building& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(PowerParameter& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(Power& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(Action& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            template<> void SerializeInternal(Auction& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);

            template<typename T> BuildingCard* FindBuildingCardInternal(T& data, std::int32_t id);
    
            template<> BuildingCard* FindBuildingCardInternal(PlayerConfig& data, std::int32_t id);
            template<> BuildingCard* FindBuildingCardInternal(GameConfig& data, std::int32_t id);
            template<> BuildingCard* FindBuildingCardInternal(PlayerState& data, std::int32_t id);
            template<> BuildingCard* FindBuildingCardInternal(GameState& data, std::int32_t id);
            template<> BuildingCard* FindBuildingCardInternal(Cell& data, std::int32_t id);
            template<> BuildingCard* FindBuildingCardInternal(BuildingType& data, std::int32_t id);
            template<> BuildingCard* FindBuildingCardInternal(BuildingCard& data, std::int32_t id);
            template<> BuildingCard* FindBuildingCardInternal(Building& data, std::int32_t id);
            template<> BuildingCard* FindBuildingCardInternal(PowerParameter& data, std::int32_t id);
            template<> BuildingCard* FindBuildingCardInternal(Power& data, std::int32_t id);
            template<> BuildingCard* FindBuildingCardInternal(Action& data, std::int32_t id);
            template<> BuildingCard* FindBuildingCardInternal(Auction& data, std::int32_t id);

            template<typename T> Building* FindBuildingInternal(T& data, std::int32_t id);
    
            template<> Building* FindBuildingInternal(PlayerConfig& data, std::int32_t id);
            template<> Building* FindBuildingInternal(GameConfig& data, std::int32_t id);
            template<> Building* FindBuildingInternal(PlayerState& data, std::int32_t id);
            template<> Building* FindBuildingInternal(GameState& data, std::int32_t id);
            template<> Building* FindBuildingInternal(Cell& data, std::int32_t id);
            template<> Building* FindBuildingInternal(BuildingType& data, std::int32_t id);
            template<> Building* FindBuildingInternal(BuildingCard& data, std::int32_t id);
            template<> Building* FindBuildingInternal(Building& data, std::int32_t id);
            template<> Building* FindBuildingInternal(PowerParameter& data, std::int32_t id);
            template<> Building* FindBuildingInternal(Power& data, std::int32_t id);
            template<> Building* FindBuildingInternal(Action& data, std::int32_t id);
            template<> Building* FindBuildingInternal(Auction& data, std::int32_t id);

            template<typename T> Action* FindActionInternal(T& data, std::int32_t id);
    
            template<> Action* FindActionInternal(PlayerConfig& data, std::int32_t id);
            template<> Action* FindActionInternal(GameConfig& data, std::int32_t id);
            template<> Action* FindActionInternal(PlayerState& data, std::int32_t id);
            template<> Action* FindActionInternal(GameState& data, std::int32_t id);
            template<> Action* FindActionInternal(Cell& data, std::int32_t id);
            template<> Action* FindActionInternal(BuildingType& data, std::int32_t id);
            template<> Action* FindActionInternal(BuildingCard& data, std::int32_t id);
            template<> Action* FindActionInternal(Building& data, std::int32_t id);
            template<> Action* FindActionInternal(PowerParameter& data, std::int32_t id);
            template<> Action* FindActionInternal(Power& data, std::int32_t id);
            template<> Action* FindActionInternal(Action& data, std::int32_t id);
            template<> Action* FindActionInternal(Auction& data, std::int32_t id);

            template<typename T> Auction* FindAuctionInternal(T& data, std::int32_t id);
    
            template<> Auction* FindAuctionInternal(PlayerConfig& data, std::int32_t id);
            template<> Auction* FindAuctionInternal(GameConfig& data, std::int32_t id);
            template<> Auction* FindAuctionInternal(PlayerState& data, std::int32_t id);
            template<> Auction* FindAuctionInternal(GameState& data, std::int32_t id);
            template<> Auction* FindAuctionInternal(Cell& data, std::int32_t id);
            template<> Auction* FindAuctionInternal(BuildingType& data, std::int32_t id);
            template<> Auction* FindAuctionInternal(BuildingCard& data, std::int32_t id);
            template<> Auction* FindAuctionInternal(Building& data, std::int32_t id);
            template<> Auction* FindAuctionInternal(PowerParameter& data, std::int32_t id);
            template<> Auction* FindAuctionInternal(Power& data, std::int32_t id);
            template<> Auction* FindAuctionInternal(Action& data, std::int32_t id);
            template<> Auction* FindAuctionInternal(Auction& data, std::int32_t id);

            template<> void SerializeInternal(PlayerConfig& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
                {
                    buffer << data.team << " ";
                }
            }

            template<> void SerializeInternal(GameConfig& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
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
                    buffer << data.resourceCount << " ";
                }
                {
                    int size0 = (int)(data.building.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.building[idx0], buffer, gameSetup, playerSetup, gameState, playerState);
                    }
                }
                {
                    int size0 = (int)(data.player.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.player[idx0], buffer, gameSetup, playerSetup, gameState, playerState);
                    }
                }
            }

            template<> void SerializeInternal(PlayerState& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
                {
                    buffer << data.team << " ";
                }
                {
                    buffer << data.money << " ";
                }
            }

            template<> void SerializeInternal(GameState& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
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
                            SerializeInternal(data.map[idx0][idx1], buffer, gameSetup, playerSetup, gameState, playerState);
                        }
                    }
                }
                {
                    int size0 = (int)(data.resourcePrice.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        buffer << data.resourcePrice[idx0] << " ";
                    }
                }
                {
                    int size0 = (int)(data.resourceEvolution.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        if (data.KnowResourceEvolution(gameSetup, playerSetup, gameState, playerState, idx0))
                        {                
                            buffer << (int)data.resourceEvolution[idx0] << " ";
                        }
                        else
                        {
                            buffer << (int)PriceEvolution::Unknown << " ";
                        }
                    }
                }
                {
                    int size0 = (int)(data.building.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.building[idx0], buffer, gameSetup, playerSetup, gameState, playerState);
                    }
                }
                {
                    int size0 = (int)(data.buildingCard.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.buildingCard[idx0], buffer, gameSetup, playerSetup, gameState, playerState);
                    }
                }
                {
                    int size0 = (int)(data.player.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.player[idx0], buffer, gameSetup, playerSetup, gameState, playerState);
                    }
                }
                {
                    int size0 = (int)(data.auction.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.auction[idx0], buffer, gameSetup, playerSetup, gameState, playerState);
                    }
                }
                {
                    int size0 = (int)(data.endedAuction.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.endedAuction[idx0], buffer, gameSetup, playerSetup, gameState, playerState);
                    }
                }
                {
                    int size0 = (int)(data.futureAuction.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.futureAuction[idx0], buffer, gameSetup, playerSetup, gameState, playerState);
                    }
                }
            }

            template<> void SerializeInternal(Cell& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
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

            template<> void SerializeInternal(BuildingType& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
                {
                    buffer << data.actionPointMax << " ";
                }
                {
                    buffer << data.actionPointGain << " ";
                }
                {
                    int size0 = (int)(data.action.size());
                    buffer << size0 << " ";
                    for (int idx0 = 0; idx0 < size0; ++idx0)
                    {
                        SerializeInternal(data.action[idx0], buffer, gameSetup, playerSetup, gameState, playerState);
                    }
                }
            }

            template<> void SerializeInternal(BuildingCard& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
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
                {
                    buffer << data.owner << " ";
                }
            }

            template<> void SerializeInternal(Building& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
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
                {
                    buffer << data.actionPoint << " ";
                }
            }

            template<> void SerializeInternal(PowerParameter& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
                {
                    buffer << data.quantity << " ";
                }
                {
                    buffer << data.resource << " ";
                }
                {
                    if (data.buildingSource == nullptr)
                    {
                        buffer << -1 << " ";
                    }
                    else
                    {                
                        buffer << data.buildingSource->id << " ";
                    }
                }
            }

            template<> void SerializeInternal(Power& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
                {                
                    buffer << (int)data.type << " ";
                }
                {                
                    buffer << (int)data.quantity << " ";
                }
                {
                    buffer << data.quantityForced << " ";
                }
                {                
                    buffer << (int)data.resource << " ";
                }
                {
                    buffer << data.resourceForced << " ";
                }
                {                
                    buffer << (int)data.buildingSource << " ";
                }
            }

            template<> void SerializeInternal(Action& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
                {
                    buffer << data.id << " ";
                }
                {
                    SerializeInternal(data.power, buffer, gameSetup, playerSetup, gameState, playerState);
                }
                {
                    buffer << data.actionPoint << " ";
                }
                {
                    buffer << data.priority << " ";
                }
            }

            template<> void SerializeInternal(Auction& data, std::stringstream& buffer, GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
            {
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
            template<> BuildingCard* FindBuildingCardInternal(PlayerConfig& data, std::int32_t id)
            {                return nullptr;
            }

            template<> BuildingCard* FindBuildingCardInternal(GameConfig& data, std::int32_t id)
            {
                {
                    auto& memberArray0 = data.building;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (BuildingCard* res = FindBuildingCardInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.player;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (BuildingCard* res = FindBuildingCardInternal(memberArray1, id))
                            return res;
                    }
                }                return nullptr;
            }

            template<> BuildingCard* FindBuildingCardInternal(PlayerState& data, std::int32_t id)
            {                return nullptr;
            }

            template<> BuildingCard* FindBuildingCardInternal(GameState& data, std::int32_t id)
            {
                {
                    auto& memberArray0 = data.map;
                    for (auto& memberArray1 : memberArray0)
                    {
                        for (auto& memberArray2 : memberArray1)
                        {
                            if (BuildingCard* res = FindBuildingCardInternal(memberArray2, id))
                                return res;
                        }
                    }
                }
                {
                    auto& memberArray0 = data.building;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (BuildingCard* res = FindBuildingCardInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.buildingCard;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (BuildingCard* res = FindBuildingCardInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.player;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (BuildingCard* res = FindBuildingCardInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.auction;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (BuildingCard* res = FindBuildingCardInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.endedAuction;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (BuildingCard* res = FindBuildingCardInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.futureAuction;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (BuildingCard* res = FindBuildingCardInternal(memberArray1, id))
                            return res;
                    }
                }                return nullptr;
            }

            template<> BuildingCard* FindBuildingCardInternal(Cell& data, std::int32_t id)
            {                return nullptr;
            }

            template<> BuildingCard* FindBuildingCardInternal(BuildingType& data, std::int32_t id)
            {
                {
                    auto& memberArray0 = data.action;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (BuildingCard* res = FindBuildingCardInternal(memberArray1, id))
                            return res;
                    }
                }                return nullptr;
            }

            template<> BuildingCard* FindBuildingCardInternal(BuildingCard& data, std::int32_t id)
            {
                if (data.id == id)
                    return &data;                return nullptr;
            }

            template<> BuildingCard* FindBuildingCardInternal(Building& data, std::int32_t id)
            {                return nullptr;
            }

            template<> BuildingCard* FindBuildingCardInternal(PowerParameter& data, std::int32_t id)
            {                return nullptr;
            }

            template<> BuildingCard* FindBuildingCardInternal(Power& data, std::int32_t id)
            {                return nullptr;
            }

            template<> BuildingCard* FindBuildingCardInternal(Action& data, std::int32_t id)
            {
                if (BuildingCard* res = FindBuildingCardInternal(data.power, id))
                    return res;                return nullptr;
            }

            template<> BuildingCard* FindBuildingCardInternal(Auction& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Building* FindBuildingInternal(PlayerConfig& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Building* FindBuildingInternal(GameConfig& data, std::int32_t id)
            {
                {
                    auto& memberArray0 = data.building;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Building* res = FindBuildingInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.player;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Building* res = FindBuildingInternal(memberArray1, id))
                            return res;
                    }
                }                return nullptr;
            }

            template<> Building* FindBuildingInternal(PlayerState& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Building* FindBuildingInternal(GameState& data, std::int32_t id)
            {
                {
                    auto& memberArray0 = data.map;
                    for (auto& memberArray1 : memberArray0)
                    {
                        for (auto& memberArray2 : memberArray1)
                        {
                            if (Building* res = FindBuildingInternal(memberArray2, id))
                                return res;
                        }
                    }
                }
                {
                    auto& memberArray0 = data.building;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Building* res = FindBuildingInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.buildingCard;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Building* res = FindBuildingInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.player;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Building* res = FindBuildingInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.auction;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Building* res = FindBuildingInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.endedAuction;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Building* res = FindBuildingInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.futureAuction;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Building* res = FindBuildingInternal(memberArray1, id))
                            return res;
                    }
                }                return nullptr;
            }

            template<> Building* FindBuildingInternal(Cell& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Building* FindBuildingInternal(BuildingType& data, std::int32_t id)
            {
                {
                    auto& memberArray0 = data.action;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Building* res = FindBuildingInternal(memberArray1, id))
                            return res;
                    }
                }                return nullptr;
            }

            template<> Building* FindBuildingInternal(BuildingCard& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Building* FindBuildingInternal(Building& data, std::int32_t id)
            {
                if (data.id == id)
                    return &data;                return nullptr;
            }

            template<> Building* FindBuildingInternal(PowerParameter& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Building* FindBuildingInternal(Power& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Building* FindBuildingInternal(Action& data, std::int32_t id)
            {
                if (Building* res = FindBuildingInternal(data.power, id))
                    return res;                return nullptr;
            }

            template<> Building* FindBuildingInternal(Auction& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Action* FindActionInternal(PlayerConfig& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Action* FindActionInternal(GameConfig& data, std::int32_t id)
            {
                {
                    auto& memberArray0 = data.building;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Action* res = FindActionInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.player;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Action* res = FindActionInternal(memberArray1, id))
                            return res;
                    }
                }                return nullptr;
            }

            template<> Action* FindActionInternal(PlayerState& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Action* FindActionInternal(GameState& data, std::int32_t id)
            {
                {
                    auto& memberArray0 = data.map;
                    for (auto& memberArray1 : memberArray0)
                    {
                        for (auto& memberArray2 : memberArray1)
                        {
                            if (Action* res = FindActionInternal(memberArray2, id))
                                return res;
                        }
                    }
                }
                {
                    auto& memberArray0 = data.building;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Action* res = FindActionInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.buildingCard;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Action* res = FindActionInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.player;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Action* res = FindActionInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.auction;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Action* res = FindActionInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.endedAuction;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Action* res = FindActionInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.futureAuction;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Action* res = FindActionInternal(memberArray1, id))
                            return res;
                    }
                }                return nullptr;
            }

            template<> Action* FindActionInternal(Cell& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Action* FindActionInternal(BuildingType& data, std::int32_t id)
            {
                {
                    auto& memberArray0 = data.action;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Action* res = FindActionInternal(memberArray1, id))
                            return res;
                    }
                }                return nullptr;
            }

            template<> Action* FindActionInternal(BuildingCard& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Action* FindActionInternal(Building& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Action* FindActionInternal(PowerParameter& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Action* FindActionInternal(Power& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Action* FindActionInternal(Action& data, std::int32_t id)
            {
                if (data.id == id)
                    return &data;
                if (Action* res = FindActionInternal(data.power, id))
                    return res;                return nullptr;
            }

            template<> Action* FindActionInternal(Auction& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Auction* FindAuctionInternal(PlayerConfig& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Auction* FindAuctionInternal(GameConfig& data, std::int32_t id)
            {
                {
                    auto& memberArray0 = data.building;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Auction* res = FindAuctionInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.player;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Auction* res = FindAuctionInternal(memberArray1, id))
                            return res;
                    }
                }                return nullptr;
            }

            template<> Auction* FindAuctionInternal(PlayerState& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Auction* FindAuctionInternal(GameState& data, std::int32_t id)
            {
                {
                    auto& memberArray0 = data.map;
                    for (auto& memberArray1 : memberArray0)
                    {
                        for (auto& memberArray2 : memberArray1)
                        {
                            if (Auction* res = FindAuctionInternal(memberArray2, id))
                                return res;
                        }
                    }
                }
                {
                    auto& memberArray0 = data.building;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Auction* res = FindAuctionInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.buildingCard;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Auction* res = FindAuctionInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.player;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Auction* res = FindAuctionInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.auction;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Auction* res = FindAuctionInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.endedAuction;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Auction* res = FindAuctionInternal(memberArray1, id))
                            return res;
                    }
                }
                {
                    auto& memberArray0 = data.futureAuction;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Auction* res = FindAuctionInternal(memberArray1, id))
                            return res;
                    }
                }                return nullptr;
            }

            template<> Auction* FindAuctionInternal(Cell& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Auction* FindAuctionInternal(BuildingType& data, std::int32_t id)
            {
                {
                    auto& memberArray0 = data.action;
                    for (auto& memberArray1 : memberArray0)
                    {
                        if (Auction* res = FindAuctionInternal(memberArray1, id))
                            return res;
                    }
                }                return nullptr;
            }

            template<> Auction* FindAuctionInternal(BuildingCard& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Auction* FindAuctionInternal(Building& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Auction* FindAuctionInternal(PowerParameter& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Auction* FindAuctionInternal(Power& data, std::int32_t id)
            {                return nullptr;
            }

            template<> Auction* FindAuctionInternal(Action& data, std::int32_t id)
            {
                if (Auction* res = FindAuctionInternal(data.power, id))
                    return res;                return nullptr;
            }

            template<> Auction* FindAuctionInternal(Auction& data, std::int32_t id)
            {
                if (data.id == id)
                    return &data;                return nullptr;
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
            
            template<class T> void Deserialize(T& data, const char*& buf, GameConfig* gameSetup, GameState* gameState)
            {
                data = ReadNext<T>(buf);
            }    
            template<> void Deserialize(PowerParameter& data, const char*& buf, GameConfig* gameSetup, GameState* gameState);
            
            template<> void Deserialize(PowerParameter& data, const char*& buf, GameConfig* gameSetup, GameState* gameState)
            {
                {
                    auto& member = data.quantity;
                    Deserialize(member, buf, gameSetup, gameState);
                }
                {
                    auto& member = data.resource;
                    Deserialize(member, buf, gameSetup, gameState);
                }
                {
                    auto& member = data.buildingSource;
                    {
                        std::int32_t classIdx0 = ReadNext<std::int32_t>(buf);
                        member = Serializer::FindBuilding(*gameSetup, *gameState, classIdx0);
                    }
                }
            }
        }
        
        std::string Serializer::SerializeSetup(GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
        {
            std::stringstream buffer;
            buffer << playerSetup.id << '\n';
            SerializeInternal(gameSetup, buffer, gameSetup, playerSetup, gameState, playerState);
            buffer << '\n';
            return buffer.str();
        }

        std::string Serializer::SerializeState(GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState)
        {
            std::stringstream buffer;
            SerializeInternal(gameState, buffer, gameSetup, playerSetup, gameState, playerState);
            buffer << '\n';
            return buffer.str();
        }

        BuildingCard* Serializer::FindBuildingCard(GameConfig& gameSetup, GameState& gameState, std::int32_t id)
        {
            if (BuildingCard* res = FindBuildingCardInternal(gameState, id))
                return res;
            return FindBuildingCardInternal(gameSetup, id);
        }

        Building* Serializer::FindBuilding(GameConfig& gameSetup, GameState& gameState, std::int32_t id)
        {
            if (Building* res = FindBuildingInternal(gameState, id))
                return res;
            return FindBuildingInternal(gameSetup, id);
        }

        Action* Serializer::FindAction(GameConfig& gameSetup, GameState& gameState, std::int32_t id)
        {
            if (Action* res = FindActionInternal(gameState, id))
                return res;
            return FindActionInternal(gameSetup, id);
        }

        Auction* Serializer::FindAuction(GameConfig& gameSetup, GameState& gameState, std::int32_t id)
        {
            if (Auction* res = FindAuctionInternal(gameState, id))
                return res;
            return FindAuctionInternal(gameSetup, id);
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
                    return argThis.Buy(gameSetup, gameSetup.player[currentPlayerId], gameState, gameState.player[currentPlayerId], order);
                }
                case 1: // BuildingCard::Build
                {
                    std::int32_t argThisId0 = ReadNext<std::int32_t>(buf);
                    BuildingCard* argThisPtr = FindBuildingCard(gameSetup, gameState, argThisId0);

                    if (!argThisPtr)
                        return false;
                    BuildingCard& argThis = *argThisPtr;
                            int position_idx0 = ReadNext<int>(buf);
                            int position_idx1 = ReadNext<int>(buf);
                            if (!(position_idx0 >= 0 && position_idx1 >= 0 && gameState.map.size() > position_idx0 && gameState.map[position_idx0].size() > position_idx1))
                                return false;
                            Cell& position = gameState.map[position_idx0][position_idx1];
                    return argThis.Build(gameSetup, gameSetup.player[currentPlayerId], gameState, gameState.player[currentPlayerId], position, order);
                }
                case 2: // Building::Execute
                {
                    std::int32_t argThisId0 = ReadNext<std::int32_t>(buf);
                    Building* argThisPtr = FindBuilding(gameSetup, gameState, argThisId0);

                    if (!argThisPtr)
                        return false;
                    Building& argThis = *argThisPtr;
                    std::int32_t action_id0 = ReadNext<std::int32_t>(buf);
                    auto action_ptr = FindAction(gameSetup, gameState, action_id0);
                    if (!action_ptr)
                        return false;
                    Action& action = *(action_ptr);                            
                    PowerParameter param;
                    Deserialize(param, buf, &gameSetup, &gameState);
                    return argThis.Execute(gameSetup, gameSetup.player[currentPlayerId], gameState, gameState.player[currentPlayerId], action, param, order);
                }
                case 3: // Auction::Bid
                {
                    std::int32_t argThisId0 = ReadNext<std::int32_t>(buf);
                    Auction* argThisPtr = FindAuction(gameSetup, gameState, argThisId0);

                    if (!argThisPtr)
                        return false;
                    Auction& argThis = *argThisPtr;
                    std::int32_t money = ReadNext<std::int32_t>(buf);
                    return argThis.Bid(gameSetup, gameSetup.player[currentPlayerId], gameState, gameState.player[currentPlayerId], money, order);
                }
                default:
                    return false;
            }
        }
    }
}