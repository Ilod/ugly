#pragma once
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
            Paused,
            Success,
            Timeout,
            Crash,
        };

        struct ProcessData
        {
            ProcessData() {}
            ProcessData(const ProcessData&) = delete;
            ProcessData(ProcessData&&) = default;
            ProcessData(std::string&& data, std::chrono::high_resolution_clock::duration time)
                : data(std::move(data))
                , time(time)
            {}

            std::string data;
            std::chrono::high_resolution_clock::duration time;
        };

        class ProcessResultStreamer
        {
        public:
            virtual ~ProcessResultStreamer();
            virtual void OnDataReceived(const std::string& data, std::chrono::high_resolution_clock::duration time) = 0;
        };

        struct ProcessStepResult
        {
            ProcessStepResult();

            ProcessState result = ProcessState::Running;
            std::chrono::high_resolution_clock::duration executionDuration;
            std::vector<ProcessData> data;
        };

        class Process
        {
        public:
            bool Create();
            bool Start();
            bool Stop();
            bool Kill();
            virtual const std::string& GetExecutable() const = 0;
            virtual const std::string& GetArguments() const = 0;

            ProcessStepResult Run(const std::string& input, std::chrono::high_resolution_clock::duration timeout, const std::string& endStepMarker, ProcessResultStreamer* streamer = nullptr);
        protected:
            virtual std::string ReadLine(std::chrono::high_resolution_clock::duration timeout) = 0;
            virtual bool TryWrite(const std::string& data) = 0;
            virtual bool TryCreate() = 0;
            virtual bool TryStart() = 0;
            virtual bool TryStop() = 0;
            virtual bool TryKill() = 0;
            virtual bool IgnoreTimeout() const { return false; }
            ProcessState state = ProcessState::NotCreated;
        };
    }
}