#pragma once
#include "Process.h"
#include "Util.h"
#include <cstdint>
#include <atomic>

namespace ugly
{
    namespace process
    {
        class ProcessParent : public Process
        {
        protected:
            bool TryCreate() override;
            bool TryStart() override { return true; }
            bool TryStop() override { return true; }
            bool TryKill() override { return true; }
            bool IgnoreTimeout() const override { return true; }
            std::string ReadLine(std::chrono::high_resolution_clock::duration timeout) override;
            bool TryWrite(const std::string& data) override;
            const std::string& GetFullCommandLine() const override { return empty; }
        private:
            static std::string empty;
        };
    }
}