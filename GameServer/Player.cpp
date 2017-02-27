#include "Player.h"

namespace ugly
{
    namespace server
    {
        void Player::Run(std::chrono::milliseconds timeout, const std::string& endOfTurnMarker)
        {
            if (processState != process::ProcessState::Running)
                return;
            process::ProcessStepResult result = process->Run(timeout, endOfTurnMarker);
            gameState->ParseOrders(result.data, result.executionDuration);
            if (result.result != process::ProcessState::Success)
                processState = result.result;
        }
    }
}