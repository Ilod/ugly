#pragma once
#include "Serializer.h"
#include "GameServer/Game.h"

namespace ugly
{
    namespace FreeMarket
    {
        class GameServer : public ugly::server::GameBase
        {
        protected:
            void InitGame() override;
            std::string GetGameSetup(int player) override { return Serializer::SerializeSetup(gameSetup, gameSetup.player[player], gameState, gameState.player[player]); }
            std::string GetGameState(int player) override { return Serializer::SerializeState(gameSetup, gameSetup.player[player], gameState, gameState.player[player]); }
            void PlayTurn() override;
            ugly::server::GameResult ComputeScore() override;
            bool ShouldPlay() override;
            bool CanPlayThisTurn(int player) override;
            std::chrono::milliseconds GetNextTurnTimeLimit(int player) override;
            std::chrono::milliseconds GetSetupTimeLimit(int player) override;
            std::chrono::milliseconds GetCleanupTimeLimit(int player) override;
        private:
            GameConfig gameSetup;
            GameState gameState;
            int turn = 0;
        };
    }
}