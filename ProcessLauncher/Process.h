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
            ProcessData& operator=(const ProcessData&) = delete;
            ProcessData& operator=(ProcessData&&) = default;
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

        class IProcess
        {
        public:
            virtual ~IProcess();
            virtual bool Create() = 0;
            virtual bool Start() = 0;
            virtual bool Stop() = 0;
            virtual bool Kill() = 0;
            virtual ProcessState GetState() const = 0;

            virtual ProcessStepResult Run(const std::string& input, std::chrono::high_resolution_clock::duration timeout, const std::string& endStepMarker, ProcessResultStreamer* streamer = nullptr) = 0;
        };

        class Process : public IProcess
        {
        public:
            bool Create() override;
            bool Start() override;
            bool Stop() override;
            bool Kill() override;
            ProcessState GetState() const override;

            ProcessStepResult Run(const std::string& input, std::chrono::high_resolution_clock::duration timeout, const std::string& endStepMarker, ProcessResultStreamer* streamer = nullptr) override;
        protected:
            virtual const std::string& GetFullCommandLine() const = 0;
            virtual bool ReadLine(std::string& line, std::chrono::high_resolution_clock::duration timeout) = 0;
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