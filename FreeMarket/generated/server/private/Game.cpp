#include "Game.h"
#include <map>
#include <string>
#include "GameServer/GameServerEntryPoint.h"
#include "DynamicLoader/Memory.h"

namespace ugly
{
    namespace FreeMarket
    {
        void GameServer::InitGame()
        {
            int players = GetPlayerCount();
            gameSetup.player.resize(players);
            gameState.player.resize(players);
            for (int i = 0; i < players; ++i)
            {
                gameSetup.player[i].id = i;
                gameState.player[i].id = i;
            }
        }

        void GameServer::PlayTurn()
        {

        }

        ugly::server::GameResult GameServer::ComputeScore()
        {
            return ugly::server::GameResult();
        }

        bool GameServer::ShouldPlay()
        {
            return false;
        }

        bool GameServer::CanPlayThisTurn(int player)
        {
            return true;
        }

        std::chrono::milliseconds GameServer::GetNextTurnTimeLimit(int player)
        {
            return std::chrono::milliseconds(100);
        }

        std::chrono::milliseconds GameServer::GetSetupTimeLimit(int player)
        {
            return std::chrono::milliseconds(500);
        }

        std::chrono::milliseconds GameServer::GetCleanupTimeLimit(int player)
        {
            return std::chrono::milliseconds(1000);
        }

        class GameServerEntryPoint : public ugly::server::GameServerEntryPoint
        {
        public:
            GameServerEntryPoint(std::shared_ptr<ugly::loader::LibraryHandler> library)
                : library(library)
            {}

            ugly::loader::unique_ptr<ugly::server::IGame> CreateGame(const util::CommandLine& params) const
            {
                return ugly::loader::make_unique<GameServer>(library);
            }
        private:
            std::shared_ptr<ugly::loader::LibraryHandler> library;
        };
    }
}

extern "C"
{
#ifdef _MSC_VER
    __declspec(dllexport)
#endif
    void ugly_GameServerEntryPoint(void* registry, void* library);
}

void ugly_GameServerEntryPoint(void* registry, void* library)
{
    std::shared_ptr<ugly::loader::LibraryHandler> libraryPtr = *((std::shared_ptr<ugly::loader::LibraryHandler>*)library);
    static_cast<ugly::server::GameServerRegistry*>(registry)->RegisterEntryPoint(ugly::loader::make_unique<ugly::FreeMarket::GameServerEntryPoint>(libraryPtr, libraryPtr));
}