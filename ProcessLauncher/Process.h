#include <string>
#include <chrono>
#include <vector>

namespace ugly
{
    namespace process
    {
        enum class ProcessState
        {
            NotCreated,
            Running,
            Success,
            Timeout,
            Crash,
        };

        struct ProcessStepResult
        {
            ProcessStepResult();

            ProcessState result = ProcessState::Running;
            std::chrono::high_resolution_clock::duration executionDuration;
            std::vector<std::string> data;
        };

        class Process
        {
        public:
            virtual void Create() = 0;
            virtual void Start() = 0;
            virtual void Stop() = 0;
            virtual void Kill() = 0;
            virtual std::string ReadLine(std::chrono::high_resolution_clock::duration timeout) = 0;
            virtual void Write(const std::string& data) = 0;
            virtual const std::string& GetExecutable() const = 0;
            virtual const std::string& GetArguments() const = 0;

            ProcessStepResult Run(std::chrono::high_resolution_clock::duration timeout, const std::string& endStepMarker);
        private:
            ProcessState state = ProcessState::NotCreated;
        };
    }
}