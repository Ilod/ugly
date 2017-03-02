#include "ProcessNative.h"

namespace ugly
{
    namespace process
    {
        ProcessNative::ProcessNative(const std::string& path, const std::string& arguments)
            : commandLine(arguments.empty() ? path : (path + " " + arguments))
        {}
    }
}