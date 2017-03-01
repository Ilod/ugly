#pragma once
#include <map>
#include "Interface.h"
#include "Auction.h"
namespace ugly
{
    namespace FreeMarket
    {
        class Serializer
        {
        public:
            std::string SerializeState(GameConfig& gameSetup, PlayerConfig& playerSetup, Game& gameState, Player& playerState);
            std::string SerializeSetup(GameConfig& gameSetup, PlayerConfig& playerSetup, Game& gameState, Player& playerState);
            bool ExecuteOrder(const std::string& order, GameConfig& gameSetup, Game& gameState, int playerId);
            
            class IdMap
            {
            public:
                std::map<std::int32_t, PlayerConfig*> playerConfig;
                std::map<std::int32_t, Player*> player;
                std::map<std::int32_t, Auction*> auction;
                void Clear();
            };
        private:
            IdMap gameSetupId;
            IdMap gameStateId;
        };
    }
}