#include "Process.h"
#include <algorithm>

namespace ugly
{
    namespace process
    {
        ProcessResultStreamer::~ProcessResultStreamer() {}
        
        ProcessStepResult Process::Run(const std::string& input, std::chrono::high_resolution_clock::duration timeout, const std::string& endStepMarker, ProcessResultStreamer* streamer /* = null */)
        {
            ProcessStepResult result;
            if (state != ProcessState::Paused)
            {
                result.result = state;
                return result;
            }
            if (!TryWrite(input))
            {
                state = ProcessState::Crash;
                result.result = state;
                return result;
            }
            std::chrono::high_resolution_clock::duration elapsed{ 0 };
            Start();
            std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
            while (elapsed < timeout || IgnoreTimeout())
            {
                std::string line = ReadLine(timeout - elapsed);
                elapsed = std::chrono::high_resolution_clock::now() - startTime;
                if (line.empty())
                    continue;
                if (streamer)
                    streamer->OnDataReceived(line, elapsed);
                if (line == endStepMarker)
                {
                    Stop();
                    result.result = ProcessState::Success;
                    result.executionDuration = elapsed;
                    return result;
                }
                result.data.push_back(ProcessData(std::move(line), elapsed));
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

        IProcess::~IProcess() {}

        bool Process::Create()
        {
            if (state != ProcessState::NotCreated)
                return false;
            if (!TryCreate())
            {
                state = ProcessState::Crash;
                return false;
            }
            state = ProcessState::Paused;
            return true;
        }

        bool Process::Start()
        {
            if (state != ProcessState::Paused)
                return false;
            if (!TryStart())
            {
                state = ProcessState::Crash;
                return false;
            }
            state = ProcessState::Running;
            return true;
        }

        bool Process::Stop()
        {
            if (state != ProcessState::Running)
                return false;
            if (!TryStop())
            {
                state = ProcessState::Crash;
                return false;
            }
            state = ProcessState::Paused;
            return true;
        }

        bool Process::Kill()
        {
            if (state != ProcessState::Paused && state != ProcessState::Running && state != ProcessState::Timeout)
                return false;
            if (!TryKill())
            {
                state = ProcessState::Crash;
                return false;
            }
            state = ProcessState::Crash;
            return true;
        }
    }
}