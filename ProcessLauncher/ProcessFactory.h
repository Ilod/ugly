#pragma once
#include <string>
#include "../DynamicLoader/Memory.h"
#include "Process.h"

namespace ugly
{
    namespace process
    {
        class ProcessFactory
        {
        public:
            enum class Type
            {
                Unknown,
                Native,
            };

            static loader::unique_ptr<IProcess> CreateProcess(const std::string& process);
            static loader::unique_ptr<IProcess> CreateProcess(const std::string& type, const std::string& executable);
            static loader::unique_ptr<IProcess> CreateProcess(Type type, const std::string& executable);
            static loader::unique_ptr<IProcess> AttachProcess(std::uint32_t id);
            static Type ParseType(const std::string& type);
        };
    }
}