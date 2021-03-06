#pragma once
#include "Process.h"
#include "Util.h"
#include <cstdint>
#include <atomic>

struct IUnknown;
using HANDLE = void*;

namespace ugly
{
    namespace process
    {
        class Pipe
        {
        public:
            enum class Inherit
            {
                None =  0,
                Read =  1 << 0,
                Write = 1 << 1,
            };
            Pipe();
            Pipe(Inherit inheritance);
            Pipe(const Pipe&) = delete;
            ~Pipe();
            Pipe& operator=(const Pipe&) = delete;
            bool isValid() const { return valid; }
            HANDLE getReadHandle() const { return read; }
            HANDLE getWriteHandle() const { return write; }
        private:
            HANDLE read;
            HANDLE write;
            bool valid;
            static std::atomic_uint32_t PipeId;
        };

        class ProcessWindows : public Process
        {
        public:
            ProcessWindows();
        protected:
            bool TryCreate() override;
            bool TryStart() override;
            bool TryStop() override;
            bool TryKill() override;
            bool ReadLine(std::string& line, std::chrono::high_resolution_clock::duration timeout) override;
            bool TryWrite(const std::string& data) override;
        private:
            bool ReadData(std::chrono::high_resolution_clock::duration& timeout);

            Pipe processStdInPipe;
            Pipe processStdOutPipe;
            HANDLE process;
            std::int32_t processId;

            static constexpr const int BufferSize = 16384;
            static constexpr const int BufferMoveThreshold = BufferSize * 3 / 4;

            char buffer[BufferSize];
            int bufferIdx = 0;
            int bufferEnd = 0;
        };
    }
    template<> constexpr const bool is_enum_flag<process::Pipe::Inherit> = true;
}