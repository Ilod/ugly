#include "Process.h"
#include <windows.h>

namespace ugly
{
    namespace process
    {
        class ProcessWindows : public Process
        {
        public:
            ProcessWindows();

            void Create() override;
            void Start() override;
            void Stop() override;
            std::string ReadLine(std::chrono::high_resolution_clock::duration timeout) override;
            void Write(const std::string& data) override;
        private:
            PROCESS_INFORMATION processInfo;
        };
    }
}