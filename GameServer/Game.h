#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Result.h"
#include "../ProcessLauncher/Process.h"

namespace ugly
{
    namespace server
    {

        class Game
        {
        public:
            virtual ~Game();
            GameResult Play();
            void AddPlayer(std::unique_ptr<process::Process> process);
            int GetPlayerCount() const { return (int)players.size(); }
        protected:
            virtual void InitGame() = 0;
            virtual std::string GetGameSetup() = 0;
            virtual std::string GetGameState() = 0;
            virtual void PlayTurn() = 0;
            virtual GameResult ComputeScore() = 0;
            virtual bool ShouldPlay() = 0;
            virtual std::chrono::milliseconds GetNextTurnTimeLimit(int player) = 0;
            virtual std::chrono::milliseconds GetSetupTimeLimit(int player) = 0;
            virtual std::chrono::milliseconds GetCleanupTimeLimit(int player) = 0;
        private:
            const std::string endOfTurnMarker = "EOT";
            std::vector<std::unique_ptr<process::Process>> players;
        };
    }
}