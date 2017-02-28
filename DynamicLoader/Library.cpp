#include "Library.h"
#include "LibraryHandler.h"

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
    }
}