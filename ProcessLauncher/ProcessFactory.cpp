#include "ProcessFactory.h"
#include <algorithm>
#include <cctype>
#include "ProcessNative.h"
#include "ProcessParent.h"

namespace ugly
{
    namespace process
    {
        loader::unique_ptr<IProcess> ProcessFactory::CreateProcess(const std::string& process)
        {
            size_t separator = process.find(';');
            if (separator == std::string::npos)
                return CreateProcess(Type::Unknown, process);
            size_t argsSeparator = process.find(';', separator + 1);
            if (argsSeparator == std::string::npos)
                return CreateProcess(process.substr(0, separator), process.substr(separator + 1));
            return CreateProcess(process.substr(0, separator), process.substr(separator + 1, argsSeparator), process.substr(argsSeparator + 1));
        }

        loader::unique_ptr<IProcess> ProcessFactory::CreateProcess(const std::string& type, const std::string& executable, const std::string& arguments)
        {
            return CreateProcess(ParseType(type), executable, arguments);
        }

        loader::unique_ptr<IProcess> ProcessFactory::CreateProcess(Type type, const std::string& executable, const std::string& arguments)
        {
            if (type == Type::Unknown)
                type = GuessTypeByFileName(executable);
            switch (type)
            {
            case Type::Native:
                return loader::make_unique<ProcessNative>(nullptr, executable, arguments);
            case Type::Parent:
                return loader::make_unique<ProcessParent>(nullptr);
            default:
                return nullptr;
            }
        }

        ProcessFactory::Type ProcessFactory::ParseType(const std::string& type)
        {
            std::string typeLower;
            typeLower.resize(type.size());
            std::transform(type.begin(), type.end(), typeLower.begin(), std::tolower);
            if (typeLower == "native" || typeLower == "exe")
                return Type::Native;
            if (typeLower == "parent")
                return Type::Parent;
            return Type::Unknown;
        }

        ProcessFactory::Type ProcessFactory::GuessTypeByFileName(const std::string& path)
        {
            size_t dot = path.rfind('.');
            if (dot == std::string::npos)
                return Type::Native;
            size_t slash = path.find_last_of("/\\");
            if (slash != std::string::npos && slash > dot)
                return Type::Native;
            size_t last = path.size();
            if (path[last - 1] == '"' || path[last - 1] == '\'')
                --last;
            std::string extension;
            extension.resize(last - dot - 1);
            std::transform(&path[dot + 1], &path[last], extension.begin(), std::tolower);
            if (extension == "exe")
                return Type::Native;
            return Type::Native;
        }
    }
}