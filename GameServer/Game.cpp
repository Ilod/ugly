#include "Game.h"
#include <sstream>

namespace ugly
{
    namespace server
    {
        IGame::~IGame() {}

        GameResult GameBase::Play()
        {
            for (int i = 0; i < players.size(); ++i)
                players[i]->Create();
            std::string gameSetup = GetGameSetup();
            for (int i = 0; i < players.size(); ++i)
            {
                std::stringstream buffer;
                buffer << i << '\n' << gameSetup << '\n';
                players[i]->Run(buffer.str(), GetSetupTimeLimit(i), endOfTurnMarker);
            }
            while (ShouldPlay())
            {
                std::string gameState = GetGameState() + "\n";
                for (int i = 0; i < players.size(); ++i)
                    players[i]->Run(gameState, GetNextTurnTimeLimit(i), endOfTurnMarker);
                PlayTurn();
            }
            std::string end = "EOT\n";
            for (int i = 0; i < players.size(); ++i)
                players[i]->Run(end, GetCleanupTimeLimit(i), endOfTurnMarker);
            for (int i = 0; i < players.size(); ++i)
                players[i]->Kill();
            return ComputeScore();
        }

        void GameBase::AddPlayer(loader::unique_ptr<process::IProcess> process)
        {
            players.push_back(std::move(process));
        }
    }
}