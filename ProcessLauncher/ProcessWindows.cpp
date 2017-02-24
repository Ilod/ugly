#include "ProcessWindows.h"

namespace ugly
{
    namespace process
    {
        ProcessWindows::ProcessWindows()
        {
            ZeroMemory(&processInfo, sizeof(processInfo));
        }

        void ProcessWindows::Create()
        {
            // TODO: redirect stdin/stdout
            STARTUPINFOA si;
            ZeroMemory(&si, sizeof(si));
            if (!CreateProcessA(GetExecutable().c_str(), const_cast<char*>(GetArguments().c_str()), NULL, NULL, FALSE, DEBUG_ONLY_THIS_PROCESS, NULL, NULL, &si, &processInfo))
                state = ProcessState::Crash;
            state = ProcessState::Running;
        }

        void ProcessWindows::Start()
        {
            if (!DebugActiveProcessStop(processInfo.dwProcessId))
                state = ProcessState::Crash;
        }

        void ProcessWindows::Stop()
        {
            if (!DebugActiveProcess(processInfo.dwProcessId))
                state = ProcessState::Crash;
        }

        std::string ProcessWindows::ReadLine(std::chrono::high_resolution_clock::duration timeout)
        {
            return "";
        }

        void ProcessWindows::Write(const std::string& data)
        {
        }
    }
}