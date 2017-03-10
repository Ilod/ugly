#pragma once
#include <map>
#include "Interface.h"
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
            std::string SerializeState(GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            std::string SerializeSetup(GameConfig& gameSetup, PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState);
            bool ExecuteOrder(const std::string& order, GameConfig& gameSetup, GameState& gameState, int playerId);
            
            class IdMap
            {
            public:
                std::map<std::int32_t, BuildingCard*> buildingCard;
                std::map<std::int32_t, Building*> building;
                std::map<std::int32_t, Action*> action;
                std::map<std::int32_t, Auction*> auction;
                void Clear();
            };
        private:
            IdMap gameSetupId;
            IdMap gameStateId;
        };
    }
}