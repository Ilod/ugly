#pragma once
#include <memory>
#include <Windows.h>
#include <string>

namespace ugly
{
    namespace loader
    {
        class LibraryHandlerWindows
        {
        public:
            LibraryHandlerWindows(const std::string& library);
            LibraryHandlerWindows(const LibraryHandlerWindows&) = delete;
            LibraryHandlerWindows& operator=(const LibraryHandlerWindows&) = delete;
            ~LibraryHandlerWindows();
            bool IsValid() const { return handle != NULL; }
            void* LoadFunction(const std::string& functionName);
        private:
            HMODULE handle;
        };
    }
}