#include "Registry.h"

namespace ugly
{
    namespace loader
    {
        Registry::~Registry()
        { }

        bool Registry::RegisterLibrary(const std::string& libraryName)
        {
            Library lib(libraryName);
            if (!lib)
                return false;
            Function<void, void*, void*> func = lib.LoadFunction<void, void*, void*>(GetFunctionName());
            if (!func)
                return false;
            library.push_back(lib);
            func(this, &(lib.handler));
            return true;
        }
    }
}