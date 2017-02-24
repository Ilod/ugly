#include "ProcessNative.h"

namespace ugly
{
    namespace process
    {
        ProcessNative::ProcessNative(const std::string executablePath)
            : executablePath(executablePath)
        {}
        
        static std::string ProcessNative::empty;
    }
}