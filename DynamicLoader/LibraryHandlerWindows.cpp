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

        void* LibraryHandlerWindows::LoadFunction(const std::string& function)
        {
            if (handle == NULL)
                return nullptr;
            return GetProcAddress(handle, function.c_str());
        }
    }
}