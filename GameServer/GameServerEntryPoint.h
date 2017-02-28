#pragma once
#include <string>
#include <memory>
#include <map>
#include <string>
#include "../DynamicLoader/Registry.h"
#include "../DynamicLoader/Memory.h"

namespace ugly
{
    namespace server
    {
        class Game;
        class GameServerEntryPoint
        {
        public:
            virtual ~GameServerEntryPoint();
            virtual loader::unique_ptr<Game> CreateGame(const std::map<std::string, std::string>& params) const = 0;
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