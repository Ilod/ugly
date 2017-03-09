#pragma once
#include "Interface.h"
#include "Map.h"
#include "Building.h"
#include "Auction.h"
namespace FreeMarket
{
    class GameClient
    {
    public:
        virtual ~GameClient();
        virtual void InitGame(GameConfig& gameConfig, PlayerConfig& playerConfig) = 0;
        virtual void PlayTurn(GameState& gameState, PlayerState& playerState) = 0;
        virtual void Cleanup() {};
    };

    class GameServer
    {
    public:
        static void Play(GameClient& client);
        static std::vector<std::pair<int, int>> PlayLocalServer(GameClient& client, const std::string& serverPath, const std::vector<std::string>& otherPlayers = {}, const std::string& game = "FreeMarket", const std::string& serverArgs = "");
        static std::vector<std::pair<int, int>> PlayLocalServerCommandLine(GameClient& client, const std::string& commandLine);
    private:
        static bool StartLocalServer(const std::string& commandLine);
    };
}