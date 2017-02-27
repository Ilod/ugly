#pragma once
#include "Process.h"
#include <windows.h>
#include "Util.h"

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
        };

        class ProcessWindows : public Process
        {
        public:
            ProcessWindows();
        protected:
            void Create() override;
            void Start() override;
            void Stop() override;
            std::string ReadLine(std::chrono::high_resolution_clock::duration timeout) override;
            void Write(const std::string& data) override;
        private:
            Pipe processStdInPipe;
            Pipe processStdOutPipe;
            PROCESS_INFORMATION processInfo;
            bool TryCreate();
        };
    }
    template<> constexpr const bool is_enum_flag<process::Pipe::Inherit> = true;
}