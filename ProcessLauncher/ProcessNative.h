#pragma once
#include "ProcessPlatform.h"

namespace ugly
{
    namespace process
    {
        class ProcessNative : public ProcessPlatform
        {
        public:
            ProcessNative(const std::string& path, const std::string& arguments);

            const std::string& GetFullCommandLine() const override { return commandLine; }
        private:
            const std::string& commandLine;
        };
    }
}