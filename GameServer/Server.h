#pragma once
#include <vector>
#include <memory>
#include "../ProcessLauncher/Process.h"

namespace ugly
{
    namespace server
    {
        class Client;
        class Game;
        class Server
        {
        public:
            void PlayMatch(const Game& game);
            void AddClient(Client* client);
        private:
            std::vector<Client*> clients;
        };
    }
}