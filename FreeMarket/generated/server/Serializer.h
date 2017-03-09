#pragma once
#include <map>
#include "Interface.h"
#include "Map.h"
#include "Building.h"
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
                std::map<std::int32_t, Building*> building;
                void Clear();
            };
        private:
            IdMap gameSetupId;
            IdMap gameStateId;
        };
    }
}