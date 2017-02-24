#include "ProcessPlatform.h"

namespace ugly
{
    namespace process
    {
        class ProcessNative : public ProcessPlatform
        {
        public:
            public ProcessNative(const std::string executablePath);

            const std::string& GetExecutable() const override { return executablePath; }
            const std::string& GetArguments() const override { return empty; }
        private:
            const std::string& executablePath;
            static std::string empty;
        };
    }
}