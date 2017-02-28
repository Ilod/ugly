#include "ProcessNative.h"

namespace ugly
{
    namespace process
    {
        ProcessNative::ProcessNative(const std::string& path)
            : executablePath(path)
        {}
        
        std::string ProcessNative::empty;
    }
}