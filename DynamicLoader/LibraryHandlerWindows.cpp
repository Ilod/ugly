#include "LibraryHandlerWindows.h"

namespace ugly
{
    namespace loader
    {
        LibraryHandlerWindows::LibraryHandlerWindows(const std::string& library)
        {
            handle = LoadLibraryA(library.c_str());
        }

        LibraryHandlerWindows::~LibraryHandlerWindows()
        {
            if (handle != NULL)
                FreeLibrary(handle);
        }

        LibraryHandlerWindows::FunctionPtr LibraryHandlerWindows::LoadFunction(const std::string& function)
        {
            if (handle == NULL)
                return nullptr;
            return reinterpret_cast<FunctionPtr>(GetProcAddress(handle, function.c_str()));
        }
    }
}