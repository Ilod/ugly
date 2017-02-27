#pragma once
#include <string>
#include <memory>
#include <chrono>
#include "GameState.h"
#include "../ProcessLauncher/Process.h"

namespace ugly
{
    namespace server
    {
        class Player
        {
        public:
            Player(std::unique_ptr<process::Process> process, std::unique_ptr<PlayerState> state, int id)
                : process(std::move(process))
                , gameState(std::move(state))
                , processState(process::ProcessState::NotCreated)
            {
                gameState->id = id;
            }
            void Run(std::chrono::milliseconds timeout, const std::string& endOfTurnMarker);
        private:
            std::unique_ptr<process::Process> process;
            std::unique_ptr<PlayerState> gameState;
            process::ProcessState processState;
        };
    }
}