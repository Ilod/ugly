#pragma once
#include <memory>
#include <string>
#include "LibraryHandler.h"

namespace ugly
{
    namespace loader
    {
        template<typename R, typename... Args> class Function
        {
        public:
            typedef R(*FunctionPtr)(Args...);
            typedef void(*FunctionRawPtr)();

            Function() {}
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
            Function(std::shared_ptr<LibraryHandler> handler, FunctionRawPtr function)
                : handler(handler)
                , function(reinterpret_cast<FunctionPtr>(function))
            {}
            FunctionPtr function;
            std::shared_ptr<LibraryHandler> handler;
        };
    }
}