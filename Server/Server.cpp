#include "Server.h"
#include <iostream>
#include "../GameServer/GameServerEntryPoint.h"

namespace ugly
{
    namespace server
    {
        ServerArgs ServerArgs::Parse(util::CommandLine& commandLine)
        {
            ServerArgs args;
            commandLine.ConsumeOption(args.gameDll, { "--game", "-game" }, true);
            commandLine.ConsumeOption(args.client, { "--player", "-player" });
            commandLine.ConsumeOption(args.process, { "--process", "-process" });
            return args;
        }

        class ServerRegistry : public GameServerRegistry
        {
        public:
            void RegisterEntryPoint(loader::unique_ptr<GameServerEntryPoint>&& entryPoint) override
            {
                game = std::move(entryPoint);
            }

            loader::unique_ptr<GameServerEntryPoint> game;
        };

        int Server::Launch(const ServerArgs& args)
        {
            ServerRegistry registry;
            registry.RegisterLibrary(args.gameDll);
            //for (int i = 0; i < )
            return 0;
        }
    }
}

int main(int argc, const char** argv)
{
    ugly::util::CommandLine commandLine(argc, argv);
    ugly::server::ServerArgs args = ugly::server::ServerArgs::Parse(commandLine);
    commandLine.CheckAllConsummed();
    if (commandLine.HasError())
    {
        std::cerr << commandLine.GetErrorString() << std::endl;
        return 1;
    }
    return ugly::server::Server::Launch(args);
}