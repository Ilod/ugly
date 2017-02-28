#include "ProcessFactory.h"
#include <algorithm>
#include <cctype>
#include "ProcessNative.h"

namespace ugly
{
    namespace process
    {
        loader::unique_ptr<IProcess> ProcessFactory::CreateProcess(const std::string& process)
        {
            size_t separator = process.find(';');
            if (separator == std::string::npos)
                return CreateProcess(Type::Native, process);
            return CreateProcess(process.substr(0, separator), process.substr(separator + 1));
        }

        loader::unique_ptr<IProcess> ProcessFactory::CreateProcess(const std::string& type, const std::string& executable)
        {
            return CreateProcess(ParseType(type), executable);
        }

        loader::unique_ptr<IProcess> ProcessFactory::CreateProcess(Type type, const std::string& executable)
        {
            switch (type)
            {
            case Type::Native:
                return loader::make_unique<ProcessNative>(nullptr, executable);
            default:
                return nullptr;
            }
        }

        loader::unique_ptr<IProcess> ProcessFactory::AttachProcess(std::uint32_t id)
        {
            return nullptr;
        }

        ProcessFactory::Type ProcessFactory::ParseType(const std::string& type)
        {
            std::string typeLower;
            typeLower.resize(type.size());
            std::transform(type.begin(), type.end(), typeLower.begin(), std::tolower);
            if (typeLower.empty())
                return Type::Native;
            if (typeLower == "native" || typeLower == "exe")
                return Type::Native;
            return Type::Unknown;
        }
    }
}