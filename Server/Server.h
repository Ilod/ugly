#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../GameServer/GameServerEntryPoint.h"
#include "../CommandLine/CommandLine.h"

namespace ugly
{
    namespace server
    {
        struct ServerArgs
        {
            std::string gameDll;
            std::vector<std::string> client;
            std::vector<std::uint32_t> process;

            static ServerArgs Parse(util::CommandLine& commandLine);
        };

        class Server
        {
        public:
            static int Launch(util::CommandLine& commandLine);
        };
    }
}