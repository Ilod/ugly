#include "CommandLine.h"
#include <algorithm>
#include <cctype>
#include <limits>
#include <sstream>

namespace ugly
{
    namespace util
    {
        CommandLine::CommandLine(int argn, const char** argv)
        {
            std::vector<std::string> commandLine;
            commandLine.reserve(argn - 1);
            for (int i = 1; i < argn; ++i)
                commandLine.push_back(argv[i]);
            ParseOptions(commandLine);
        }

        CommandLine::CommandLine(const std::vector<std::string>& options)
        {
            ParseOptions(options);
        }

        void CommandLine::ParseOptions(const std::vector<std::string>& options)
        {
            for (int i = 0; i < options.size(); ++i)
            {
                if (options[i].empty())
                    continue;
                else if (options[i][0] != '-')
                    data.push_back(std::make_pair(std::string(), options[i]));
                else if (options[i].find('=') != std::string::npos)
                    data.push_back(std::make_pair(options[i].substr(0, options[i].find('=')), options[i].substr(options[i].find('=') + 1)));
                else if (i == options.size() - 1 || options[i + 1].empty() || options[i + 1][0] == '-')
                    data.push_back(std::make_pair(options[i], std::string()));
                else
                {
                    data.push_back(std::make_pair(options[i], options[i + 1]));
                    ++i;
                }
            }
        }

        bool CommandLine::CheckAllConsummed()
        {
            if (data.empty())
                return true;
            for (int i = 0; i < data.size(); ++i)
            {
                error.push_back(CommandLineError());
                error.back().error = CommandLineError::Type::NotConsummed;
                error.back().option = data[i].first;
                error.back().value = data[i].second;
            }
            data.clear();
            return false;
        }

        bool CommandLine::TryParse(bool& value, const std::string& str)
        {
            if (str.empty() || str == "1")
            {
                value = true;
                return true;
            }
            if (str == "0")
            {
                value = false;
                return true;
            }
            std::string strLower = str;
            std::transform(strLower.begin(), strLower.end(), strLower.begin(), std::tolower);
            if (strLower == "true")
            {
                value = true;
                return true;
            }
            if (strLower == "false")
            {
                value = false;
                return true;
            }
            return false;
        }

        template<class T> bool CommandLine::TryParseInt(T& value, const std::string& str)
        {
            static_assert(std::is_integral_v<T> && !std::is_unsigned_v<T>, "need signed int");
            size_t size = 0;
            long long val = std::stoll(str, &size);
            if (size != str.size())
                return false;
            if (val > std::numeric_limits<T>::max())
                return false;
            if (val < std::numeric_limits<T>::min())
                return false;
            value = static_cast<T>(val);
            return true;
        }

        template<class T> bool CommandLine::TryParseUInt(T& value, const std::string& str)
        {
            static_assert(std::is_integral_v<T> && std::is_unsigned_v<T>, "need unsigned int");
            size_t size = 0;
            unsigned long long val = std::stoull(str, &size);
            if (size != str.size())
                return false;
            if (val > std::numeric_limits<T>::max())
                return false;
            value = static_cast<T>(val);
            return true;
        }

        bool CommandLine::TryParse(std::uint8_t& value, const std::string& str)
        {
            return TryParseUInt(value, str);
        }

        bool CommandLine::TryParse(std::uint16_t& value, const std::string& str)
        {
            return TryParseUInt(value, str);
        }

        bool CommandLine::TryParse(std::uint32_t& value, const std::string& str)
        {
            return TryParseUInt(value, str);
        }

        bool CommandLine::TryParse(std::uint64_t& value, const std::string& str)
        {
            return TryParseUInt(value, str);
        }

        bool CommandLine::TryParse(std::int8_t& value, const std::string& str)
        {
            return TryParseInt(value, str);
        }

        bool CommandLine::TryParse(std::int16_t& value, const std::string& str)
        {
            return TryParseInt(value, str);
        }

        bool CommandLine::TryParse(std::int32_t& value, const std::string& str)
        {
            return TryParseInt(value, str);
        }

        bool CommandLine::TryParse(std::int64_t& value, const std::string& str)
        {
            return TryParseInt(value, str);
        }

        bool CommandLine::TryParse(double& value, const std::string& str)
        {
            size_t size = 0;
            double val = std::stod(str, &size);
            if (size != str.size())
                return false;
            value = val;
            return true;
        }

        bool CommandLine::TryParse(float& value, const std::string& str)
        {
            size_t size = 0;
            float val = std::stof(str, &size);
            if (size != str.size())
                return false;
            value = val;
            return true;
        }

        bool CommandLine::TryParse(std::string& value, const std::string& str)
        {
            value = str;
            return true;
        }

        std::string CommandLine::GetErrorString() const
        {
            std::stringstream str;
            for (const CommandLineError& err : error)
            {
                switch (err.error)
                {
                case CommandLineError::Type::BadValue:
                    str << "Error on option " << err.option << ": expecting " << err.expected << ", got " << err.value << std::endl;
                    break;
                case CommandLineError::Type::NotConsummed:
                    str << "Unknown option " << err.option << " " << err.value << std::endl;
                    break;
                case CommandLineError::Type::NoValue:
                    str << "Option " << err.option << " requires a " << err.expected << " value, none provided" << std::endl;
                    break;
                case CommandLineError::Type::MissingArg:
                    str << "Mandatory option " << err.option << " (" << err.expected << ") not foud" << std::endl;
                    break;
                default:
                    str << "Unknown error " << (int)err.error << " on option " << err.option << " " << err.value << std::endl;
                    break;
                }
            }
            return str.str();
        }
    }
}