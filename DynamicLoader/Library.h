#pragma once
#include <memory>
#include <string>
#include "Function.h"

namespace ugly
{
    namespace loader
    {
        typename LibraryHandler;
        class Library
        {
        public:
            Library() {}
            Library(const std::string& library);
            template<typename R, typename... Args> Function<R, Args...> LoadFunction(const std::string& function)
            {
                return Function<R, Args...>(handler, function);
            }
            operator bool() const;
        private:
            std::shared_ptr<LibraryHandler> handler;
        };
    }
}