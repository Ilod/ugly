#pragma once
#include <memory>
#include <string>
#include "Function.h"
#include "LibraryHandler.h"

namespace ugly
{
    namespace loader
    {
        class Library
        {
        public:
            Library() {}
            Library(const std::string& library);
            template<typename R, typename... Args> Function<R, Args...> LoadFunction(const std::string& function)
            {
                return Function<R, Args...>(handler, LoadRawFunction(function));
            }
            operator bool() const;
        private:
            void* LoadRawFunction(const std::string& function);
            std::shared_ptr<LibraryHandler> handler;
            friend class Registry;
        };
    }
}