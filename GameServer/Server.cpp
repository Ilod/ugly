#include "Process.h"
#include <algorithm>

namespace ugly
{
    namespace process
    {
        ProcessStepResult Process::Run(std::chrono::high_resolution_clock::duration timeout, const std::string& endStepMarker)
        {
            ProcessStepResult result;
            if (state != ProcessState::Running)
            {
                result.result = state;
                return result;
            }
            std::chrono::high_resolution_clock::duration remaining = timeout;
            std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
            Start();
            while (remaining.count() > 0)
            {
                std::string line = ReadLine(remaining);
                remaining = (std::chrono::high_resolution_clock::now() - time);
                if (line.empty())
                    continue;
                result.data.push_back(std::move(line));
                if (result.data.back() == endStepMarker)
                {
                    Stop();
                    result.result = ProcessState::Success;
                    result.executionDuration = std::min(timeout - remaining, timeout);
                    return result;
                }
            }
            result.result = ProcessState::Timeout;
            result.executionDuration = timeout;
            Kill();
            return result;
        }

        ProcessStepResult::ProcessStepResult()
        {
            data.reserve(100);
        }
    }
}