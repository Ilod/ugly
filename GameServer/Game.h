#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Result.h"
#include "../ProcessLauncher/Process.h"
#include "../DynamicLoader/Memory.h"

namespace ugly
{
    namespace server
    {

        class IGame
        {
        public:
            virtual ~IGame();
            virtual GameResult Play() = 0;
            virtual void AddPlayer(loader::unique_ptr<process::IProcess> process) = 0;
            virtual int GetPlayerCount() const = 0;
        };
        
        class GameBase : public IGame
        {
        public:
            GameResult Play() override;
            void AddPlayer(loader::unique_ptr<process::IProcess> process) override;
            int GetPlayerCount() const override { return (int)players.size(); }
        protected:
            virtual void InitGame() = 0;
            virtual std::string GetGameSetup(int player) = 0;
            virtual std::string GetGameState(int player) = 0;
            virtual void PlayTurn() = 0;
            virtual GameResult ComputeScore() = 0;
            virtual bool ShouldPlay() = 0;
            virtual bool CanPlayThisTurn(int player) = 0;
            virtual std::chrono::milliseconds GetNextTurnTimeLimit(int player) = 0;
            virtual std::chrono::milliseconds GetSetupTimeLimit(int player) = 0;
            virtual std::chrono::milliseconds GetCleanupTimeLimit(int player) = 0;
        private:
            const std::string endOfTurnMarker = "EOT";
            std::vector<loader::unique_ptr<process::IProcess>> players;
        };
    }
}