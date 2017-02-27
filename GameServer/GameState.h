#pragma once
#include <string>
#include <vector>
#include <chrono>
#include "../Replication/Replicator.h"

namespace ugly
{
    namespace server
    {
        class PlayerState
        {
        private:
        public:
            int id = -1;
            int team = -1;
            virtual ~PlayerState() {}
            virtual void ParseOrders(const std::vector<std::string>& orders, std::chrono::high_resolution_clock::duration executionDuration) = 0;
        };

        class GameState
        {
        public:
            int turn = 0;
            virtual ~GameState() {}
        };
    }
}