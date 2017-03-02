#include "Library.h"
#include "LibraryHandlerPlatform.h"
#include "Memory.h"
namespace ugly
{
    namespace loader
    {
        Library::Library(const std::string& library)
            : handler(std::make_shared<LibraryHandler>(library))
        { }

        Library::operator bool() const
        {
            return handler && handler->IsValid();
        }
        
        Library::FunctionPtr Library::LoadRawFunction(const std::string& function)
        {
            if (!handler)
                return nullptr;
            return handler->LoadFunction(function);
        }
    }
}