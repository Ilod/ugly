#pragma once
#include <map>
#include "Interface.h"
#include "Player.h"
#include "Resource.h"
#include "Map.h"
#include "Building.h"
#include "Power.h"
#include "Auction.h"
namespace ugly
{
    namespace FreeMarket
    {
        class Serializer
        {
        public:
            static std::string SerializeState(GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            static std::string SerializeSetup(GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            static bool ExecuteOrder(const std::string& order, GameConfig& gameSetup, GameState& gameState, int playerId);
            static BuildingCard* FindBuildingCard(GameConfig& gameSetup, GameState& gameState, std::int32_t id);
            static Building* FindBuilding(GameConfig& gameSetup, GameState& gameState, std::int32_t id);
            static Action* FindAction(GameConfig& gameSetup, GameState& gameState, std::int32_t id);
            static Auction* FindAuction(GameConfig& gameSetup, GameState& gameState, std::int32_t id);
        };
    }
}