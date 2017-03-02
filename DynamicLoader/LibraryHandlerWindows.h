#pragma once
#include <memory>

struct IUnknown;

#include <Windows.h>
#include <string>

namespace ugly
{
    namespace loader
    {
        class LibraryHandlerWindows
        {
        public:
            typedef void(*FunctionPtr)();

            LibraryHandlerWindows(const std::string& library);
            LibraryHandlerWindows(const LibraryHandlerWindows&) = delete;
            LibraryHandlerWindows& operator=(const LibraryHandlerWindows&) = delete;
            ~LibraryHandlerWindows();
            bool IsValid() const { return handle != NULL; }
            FunctionPtr LoadFunction(const std::string& functionName);
        private:
            HMODULE handle;
        };
    }
}