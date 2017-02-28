#pragma once
#include <string>
#include <memory>
#include <map>
#include <string>
#include "../CommandLine/CommandLine.h"
#include "../DynamicLoader/Registry.h"
#include "../DynamicLoader/Memory.h"

namespace ugly
{
    namespace server
    {
        class IGame;
        class GameServerEntryPoint
        {
        public:
            virtual ~GameServerEntryPoint();
            virtual loader::unique_ptr<IGame> CreateGame(const util::CommandLine& params) const = 0;
        };

        class GameServerRegistry : public ugly::loader::Registry
        {
        public:
            virtual ~GameServerRegistry();
            const char* GetFunctionName() const override { return "ugly_GameServerEntryPoint";  }
            virtual void RegisterEntryPoint(loader::unique_ptr<GameServerEntryPoint>&& entryPoint) = 0;
        };
    }
}