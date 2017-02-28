#pragma once
#include <memory>
#include <string>

namespace ugly
{
    namespace loader
    {
        typename LibraryHandler;
        template<typename R, typename... Args> class Function
        {
        public:
            typedef R(*functionType)(Args...);
            Function() {}
            Function(const std::string& library, const std::string& functionName)
                : handler(std::make_shared<LibraryHandler>(library))
                , function(nullptr)
            {
                if (handler)
                    function = (functionType)handler->LoadFunction(functionName);
            }
            operator bool() const
            {
                return function != nullptr;
            }
            bool IsValid() const
            {
                return function != nullptr;
            }
            R operator()(Args... args)
            {
                return function(args...);
            }
            template<typename R, typename... Args> Function<R, Args...> LoadFunction(const std::string& function)
            {
                return Function<R, Args...>(handler, function);
            }
        private:
            friend class Library;
            Function(std::shared_ptr<LibraryHandler> handler, void* function)
                : handler(handler)
                , function(function)
            {}
            functionType function;
            std::shared_ptr<LibraryHandler> handler;
        };
    }
}