#include "Game.h"
#include <algorithm>
#include <sstream>
#include <tuple>

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
                std::vector<std::tuple<process::ProcessData, int>> orders;
                for (int i = 0; i < players.size(); ++i)
                {
                    if (CanPlayThisTurn(i) && players[i]->GetState() == process::ProcessState::Paused)
                    {
                        process::ProcessStepResult result = players[i]->Run(GetGameState(i), GetNextTurnTimeLimit(i), endOfTurnMarker);
                        orders.reserve(result.data.size());
                        for (process::ProcessData& data : result.data)
                            orders.push_back(std::make_tuple(std::move(data), i));
                    }
                }
                std::sort(orders.begin(), orders.end(), [=](const auto& o1, const auto& o2) { return std::get<0>(o1).time < std::get<0>(o2).time; });
                for (const auto& order : orders)
                    ExecuteOrder(std::get<0>(order).data, std::get<1>(order));
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