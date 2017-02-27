#include "Game.h"

namespace ugly
{
    namespace server
    {
        Game::~Game() {}

        void Game::AddPlayer(std::unique_ptr<process::Process> process)
        {
            players.push_back(Player(std::move(process), CreatePlayerState(), (int)players.size()));
        }

        void Game::RunPlayers()
        {
            for (Player& player : players)
            {
                player.Run(GetNextTurnTimeLimit(), endOfTurnMarker);
            }
        }
    }
}