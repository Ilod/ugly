#pragma once
#include "Interface.h"
#include "Auction.h"
namespace FreeMarket
{
    class GameClient
    {
    public:
        virtual ~GameClient();
        virtual void InitGame(GameConfig& gameConfig, PlayerConfig& playerConfig) = 0;
        virtual void PlayTurn(Game& game, Player& player) = 0;
        virtual void Cleanup() {};
    };

    class GameServer
    {
    public:
        static void Play(GameClient& client);
    };
}