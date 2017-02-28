#pragma once
#include <string>
#include <memory>
#include <map>
#include <string>
#include "../DynamicLoader/Registry.h"

namespace ugly
{
    namespace server
    {
        class Game;
        class GameServerEntryPoint
        {
        public:
            virtual ~GameServerEntryPoint();
            virtual std::unique_ptr<Game> CreateGame(std::map<std::string, std::string> params) const = 0;
        };

        class GameServerRegistry : ugly::loader::Registry
        {
        public:
            virtual ~GameServerRegistry();
            const char* GetFunctionName() const override { return "ugly_GameServerEntryPoint";  }
            virtual void RegisterEntryPoint(const GameServerEntryPoint& entryPoint) = 0;
        };
    }
}