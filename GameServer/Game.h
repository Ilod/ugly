#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Result.h"
#include "GameState.h"
#include "Player.h"
#include "../ProcessLauncher/Process.h"

namespace ugly
{
    namespace server
    {

        class Game
        {
        public:
            virtual ~Game();
            void AddPlayer(std::unique_ptr<process::Process> process);
            virtual GameResult Play() = 0;
            void RunPlayers();
            virtual std::chrono::milliseconds GetNextTurnTimeLimit() = 0;
        protected:
            virtual std::unique_ptr<GameState> CreateGameState() = 0;
            virtual std::unique_ptr<PlayerState> CreatePlayerState() = 0;
        private:
            const std::string endOfTurnMarker = "EOT";
            std::unique_ptr<GameState> gameState;
            std::vector<Player> players;
        };
    }
}