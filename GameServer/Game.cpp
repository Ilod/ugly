#include "Game.h"
#include <sstream>

namespace ugly
{
    namespace server
    {
        IGame::~IGame() {}

        GameResult GameBase::Play()
        {
            InitGame();
            for (int i = 0; i < players.size(); ++i)
                players[i]->Create();
            for (int i = 0; i < players.size(); ++i)
                players[i]->Run(GetGameSetup(i), GetSetupTimeLimit(i), endOfTurnMarker);
            while (ShouldPlay())
            {
                for (int i = 0; i < players.size(); ++i)
                {
                    if (CanPlayThisTurn(i))
                    {
                        players[i]->Run(GetGameState(i), GetNextTurnTimeLimit(i), endOfTurnMarker);
                    }
                }
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

        ugly::process::ProcessState GameBase::GetPlayerState(int player)
        {
            return players[player]->GetState();
        }
    }
}