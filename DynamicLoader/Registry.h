#pragma once
#include <string>
#include <vector>
#include "Library.h"

namespace ugly
{
    namespace loader
    {
        class Registry
        {
        public:
            virtual ~Registry();
            virtual const char* GetFunctionName() const = 0;
            bool RegisterLibrary(const std::string& library);
        private:
            std::vector<Library> library;
        };
    }
}