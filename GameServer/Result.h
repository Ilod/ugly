#pragma once
#include <vector>
#include "../ProcessLauncher/Process.h"

namespace ugly
{
    namespace server
    {
        struct PlayerResult
        {
            uint8_t rank;
            process::ProcessState state;
            int score;
        };

        struct GameResult
        {
            std::vector<PlayerResult> players;
        };
    }
}