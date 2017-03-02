#pragma once
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdint>

namespace ugly
{
    namespace util
    {
        enum class CommandLineResult
        {
            Success,
            NotFound,
            ParseError,
        };

        struct CommandLineError
        {
            enum class Type
            {
                NoError,
                NotConsummed,
                NoValue,
                BadValue,
                MissingArg,
            };

            Type error = Type::NoError;
            std::string option;
            std::string value;
            std::string expected;
        };

        class CommandLine
        {
        public:
            CommandLine(int argn, const char** argv);
            CommandLine(const std::vector<std::string>& options);
            CommandLineResult ConsumeOption(bool& value, const std::vector<std::string>& options, const std::vector<std::string>& negativeOptions, bool mandatory = false)
            {
                std::vector<bool> val;
                CommandLineResult res = ConsumeOption(val, options, negativeOptions, mandatory);
                if (!val.empty())
                    value = val.back();
                else if (res != CommandLineResult::NotFound)
                    value = false;
                return res;
            }
            template<typename T> CommandLineResult ConsumeOption(T& value, const std::vector<std::string>& options, bool mandatory = false)
            {
                std::vector<T> val;
                CommandLineResult res = ConsumeOption(val, options, {}, mandatory);
                if (!val.empty())
                    value = std::move(val.back());
                return res;
            }
            template<typename T> CommandLineResult ConsumeOption(std::vector<T>& value, const std::vector<std::string>& options, bool mandatory = false)
            {
                return ConsumeOption(value, options, {}, mandatory);
            }
            template<typename T> CommandLineResult ConsumeOption(std::vector<T>& value, const std::vector<std::string>& options, const std::vector<std::string>& negativeOptions, bool mandatory = false)
            {
                std::vector<T> negativeValue;
                return ConsumeOption(value, negativeValue, options, negativeOptions, mandatory);
            }
            template<typename T> CommandLineResult ConsumeOption(std::vector<T>& value, std::vector<T>& negativeValue, const std::vector<std::string>& options, const std::vector<std::string>& negativeOptions, bool mandatory = false);

            bool CheckAllConsummed();
            bool HasError() const { return !error.empty(); }
            std::string GetErrorString() const;
            bool HasRemainingData() const { return !data.empty(); }
            const std::vector<CommandLineError>& GetErrors() const { return error; }
        private:
            static bool TryParse(bool& value, const std::string& str);
            static bool TryParse(std::uint8_t& value, const std::string& str);
            static bool TryParse(std::uint16_t& value, const std::string& str);
            static bool TryParse(std::uint32_t& value, const std::string& str);
            static bool TryParse(std::uint64_t& value, const std::string& str);
            static bool TryParse(std::int8_t& value, const std::string& str);
            static bool TryParse(std::int16_t& value, const std::string& str);
            static bool TryParse(std::int32_t& value, const std::string& str);
            static bool TryParse(std::int64_t& value, const std::string& str);
            static bool TryParse(double& value, const std::string& str);
            static bool TryParse(float& value, const std::string& str);
            static bool TryParse(std::string& value, const std::string& str);
            template<typename T> static bool TryParseInt(T& value, const std::string& str);
            template<typename T> static bool TryParseUInt(T& value, const std::string& str);
            template<typename T> static typename std::enable_if_t<std::is_enum_v<T>> TryParse(T& value, const std::string& str)
            {
                std::underlying_type_t<T> val;
                bool b = TryParse(val);
                value = static_cast<T>(val);
                return b;
            }
            void ParseOptions(const std::vector<std::string>& options);
            std::vector<std::pair<std::string, std::string>> data;
            std::vector<CommandLineError> error;
        };

        template<typename T> CommandLineResult CommandLine::ConsumeOption(std::vector<T>& value, std::vector<T>& negativeValue, const std::vector<std::string>& options, const std::vector<std::string>& negativeOptions, bool mandatory)
        {
            CommandLineResult res = CommandLineResult::NotFound;
            bool foundAnyValid = false;
            auto it = data.begin();
            while (it != data.end())
            {
                bool negative = (std::find(negativeOptions.begin(), negativeOptions.end(), it->first) != negativeOptions.end());
                bool found = negative || (std::find(options.begin(), options.end(), it->first) != options.end());
                if (!found)
                {
                    ++it;
                    continue;
                }
                T val;
                if (TryParse(val, it->second))
                {
                    foundAnyValid = true;
                    std::vector<T>& toAdd = negative ? negativeValue : value;
                    std::vector<T>& toRemove = negative ? value : negativeValue;
                    size_t sizeBefore = toRemove.size();
                    std::remove(toRemove.begin(), toRemove.end(), val);
                    if (toRemove.size() == sizeBefore)
                    {
                        toAdd.push_back(val);
                    }
                }
                else
                {
                    res = CommandLineResult::ParseError;
                    error.push_back(CommandLineError());
                    error.back().error = it->second.empty() ? CommandLineError::Type::NoValue : CommandLineError::Type::BadValue;
                    error.back().option = it->first;
                    error.back().value = it->second;
                    error.back().expected
                        = std::is_same_v<bool, T> ? "bool"
                        : std::is_integral_v<T> ? "int"
                        : std::is_floating_point_v<T> ? "float"
                        : std::is_same_v<std::string, T> ? "string" : "unknown";
                }
                it = data.erase(it);
            }
            if (res != CommandLineResult::ParseError && foundAnyValid)
                res = CommandLineResult::Success;
            if (!foundAnyValid && mandatory)
            {
                error.push_back(CommandLineError());
                error.back().error = CommandLineError::Type::MissingArg;
                error.back().option = options[0];
                error.back().expected
                    = std::is_same_v<bool, T> ? "bool"
                    : std::is_integral_v<T> ? "int"
                    : std::is_floating_point_v<T> ? "float"
                    : std::is_same_v<std::string, T> ? "string" : "unknown";
            }
            return res;
        }
    }
}