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
                UnknownArg,
                NotConsummed,
                NoValue,
                BadValue,
            };

            Type error;
            std::string option;
            std::string value;
            std::string expected;
        };

        class CommandLine
        {
        public:
            CommandLine(int argn, const char** argv);
            CommandLine(const std::vector<std::string>& options);
            template<typename T> CommandLineResult ConsumeOption(T& value, const std::string& option) const
            {
                return ConsumeOption(value, { option });
            }
            CommandLineResult ConsumeOption(bool& value, const std::vector<std::string>& options, const std::vector<std::string>& negativeOptions)
            {
                std::vector<bool> val;
                CommandLineResult res = ConsumeOption(value, options, negativeOptions);
                if (!val.empty())
                    value = val.back();
                else if (res != CommandLineResult::NotFound)
                    value = false;
                return res;
            }
            template<typename T> CommandLineResult ConsumeOption(T& value, const std::vector<std::string>& options) const
            {
                std::vector<T> val;
                CommandLineResult res = ConsumeOption(value, options, {});
                if (!val.empty())
                    value = std::move(val.back());
                return res;
            }
            template<typename T> CommandLineResult ConsumeOption(std::vector<T>& value, const std::vector<std::string>& options) const
            {
                return ConsumeOption(value, options, {});
            }
            template<typename T> CommandLineResult ConsumeOption(std::vector<T>& value, const std::vector<std::string>& options, const std::vector<std::string>& negativeOptions) const
            {
                std::vector<T> negativeValue;
                return ConsumeOption(value, negativeValue, options, negativeOptions);
            }
            template<typename T> CommandLineResult ConsumeOption(std::vector<T>& value, std::vector<T>& negativeValue, const std::vector<std::string>& options, const std::vector<std::string>& negativeOptions) const;

            bool CheckAllConsummed();
            bool HasError() const { return !error.empty(); }
            std::string GetErrorString() const;
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
                std::underlying_type_t val;
                bool b = TryParse(val);
                value = static_cast<T>(val);
                return b;
            }
            void ParseOptions(const std::vector<std::string>& options);
            std::vector<std::pair<std::string, std::string>> data;
            std::vector<CommandLineError> error;
        };

        template<typename T> CommandLineResult CommandLine::ConsumeOption(std::vector<T>& value, std::vector<T>& negativeValue, const std::vector<std::string>& options, const std::vector<std::string>& negativeOptions) const
        {
            CommandLineResult res = CommandLineResult::NotFound;
            for (auto it = data.begin(); it != data.end(); ++it)
            {
                bool negative = std::find(negativeOptions.begin(), negativeOptions.end(), it->first);
                bool found = negative || std::find(options.begin(), options.end(), it->first);
                if (found)
                {
                    if (res == CommandLineResult::NotFound)
                        res = CommandLineResult::Success;
                    T value;
                    if (TryParse(value, it->second))
                    {
                        std::vector<T>& toAdd = negative ? negativeValue : value;
                        std::vector<T>& toRemove = negative ? value : negativeValue;
                        size_t sizeBefore = toRemove.size();
                        std::remove(toRemove.begin(), toRemove.end(), value);
                        if (toRemove.size() == sizeBefore)
                        {
                            toAdd.push_back(value);
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
                    if (std::find())
                        it = data.erase(it);
                }
                else if ()
                {
                    it = data.erase(it);
                }
            }
            return res;
        }
    }
}