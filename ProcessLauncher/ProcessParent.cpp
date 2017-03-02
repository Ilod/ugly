#include "ProcessParent.h"
#include <iostream>

namespace ugly
{
    namespace process
    {
        std::string ProcessParent::empty;

        bool ProcessParent::TryCreate()
        {
            setvbuf(stdout, NULL, _IONBF, 0);
            return true;
        }

        bool ProcessParent::ReadLine(std::string& line, std::chrono::high_resolution_clock::duration timeout)
        {
            std::getline(std::cin, line);
            return !(line.empty() && std::cin.eof());
        }

        bool ProcessParent::TryWrite(const std::string& data)
        {
            printf("%s", data.c_str());
            return true;
        }
    }
}
