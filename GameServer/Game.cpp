#include "Game.h"
#include <sstream>

namespace ugly
{
    namespace server
    {
        IGame::~IGame() {}

        GameResult IGame::Play()
        {
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
            return ComputeScore();
        }

        void IGame::AddPlayer(std::unique_ptr<process::Process> process)
        {
            players.push_back(std::move(process));
        }
    }
}