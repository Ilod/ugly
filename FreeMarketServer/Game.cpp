#include "Game.h"
#include <map>
#include <string>
#include <random>
#include "GameServer/GameServerEntryPoint.h"
#include "DynamicLoader/Memory.h"
#include "Utils/IteratorAdatper.h"

namespace ugly
{
    namespace FreeMarket
    {
        namespace
        {
            void InitSetupData(GameConfig& gameSetup, int players)
            {
                gameSetup.player.resize(players);
                for (int i = 0; i < players; ++i)
                {
                    gameSetup.player[i].id = i;
                    gameSetup.player[i].team = i;
                }
                gameSetup.mapSizeX = 41;
                gameSetup.mapSizeY = 40;
                gameSetup.resourceCount = 5;
                gameSetup.startMoney = 200;
                gameSetup.setupTimeLimit = 500;
                gameSetup.turnTimeLimit = 100;
                gameSetup.turns = 150;
                gameSetup.additionalData.resourceStartPrice = 20;
                gameSetup.additionalData.preemptPrice = 10;

                {
                    PriceEvolutionRange price;
                    price.type = PriceEvolution::HugeDecrease;
                    price.probability = 5;
                    price.min = -5;
                    price.max = -25;
                    gameSetup.additionalData.resourcePriceEvolution.push_back(price);
                    price.type = PriceEvolution::HugeIncrease;
                    price.probability = 5;
                    price.min = 5;
                    price.max = 25;
                    gameSetup.additionalData.resourcePriceEvolution.push_back(price);
                    price.type = PriceEvolution::SmallDecrease;
                    price.probability = 30;
                    price.min = -7;
                    price.max = 0;
                    gameSetup.additionalData.resourcePriceEvolution.push_back(price);
                    price.type = PriceEvolution::SmallIncrease;
                    price.probability = 30;
                    price.min = 0;
                    price.max = 7;
                    gameSetup.additionalData.resourcePriceEvolution.push_back(price);
                    price.type = PriceEvolution::Stable;
                    price.probability = 30;
                    price.min = -2;
                    price.max = 2;
                    gameSetup.additionalData.resourcePriceEvolution.push_back(price);
                }
            }

            void InitStateData(const GameConfig& gameSetup, GameState& gameState)
            {
                gameState.player.resize(gameSetup.player.size());
                gameState.map.resize(gameSetup.mapSizeX);
                for (int x = 0; x < gameSetup.mapSizeX; ++x)
                {
                    gameState.map[x].resize(gameSetup.mapSizeY);
                    for (int y = 0; y < gameSetup.mapSizeY; ++y)
                    {
                        Cell& c = gameState.map[x][y];
                        c.x = x;
                        c.y = y;
                        c.owner = -1;
                        c.ownership = Ownership::None;
                        c.price = gameSetup.additionalData.preemptPrice;
                        c.type =
                            (x % 4 == 0 || y % 3 == 0)
                            ? CellType::Road
                            : CellType::House;
                    }
                }
                gameState.resourcePrice.resize(gameSetup.resourceCount, gameSetup.additionalData.resourceStartPrice);
                gameState.resourceEvolution.resize(gameSetup.resourceCount);
                gameState.additionalData.resourceEvolution.resize(gameSetup.resourceCount);
            }

            void InitTurnData(const GameConfig& gameSetup, GameState& gameState)
            {
                {
                    std::random_device rdn;
                    std::default_random_engine generator(rdn());
                    auto beginRange = ugly::util::CreateSelectIteratorAdapter(gameSetup.additionalData.resourcePriceEvolution.begin(), [](const PriceEvolutionRange& range) { return range.probability; });
                    auto endRange = ugly::util::CopyWithIterator(beginRange, gameSetup.additionalData.resourcePriceEvolution.end());
                    std::discrete_distribution<> typeDistribution(beginRange, endRange);
                    for (int r = 0; r < gameSetup.resourceCount; ++r)
                    {
                        gameState.resourcePrice[r] += gameState.additionalData.resourceEvolution[r];
                        if (gameState.resourcePrice < 1)
                            gameState.resourcePrice = 1;
                        const PriceEvolutionRange& evolution = gameSetup.additionalData.resourcePriceEvolution[typeDistribution(generator)];
                        gameState.resourceEvolution[r] = evolution.type;
                        gameState.additionalData.resourceEvolution[r] = std::uniform_int_distribution<>(evolution.min, evolution.max)(generator);
                    }
                }
            }
        }

        void GameServer::InitGame()
        {
            InitSetupData(gameSetup, GetPlayerCount());
            InitStateData(gameSetup, gameState);
        }

        void GameServer::PlayTurn()
        {

        }

        ugly::server::GameResult GameServer::ComputeScore()
        {
            ugly::server::GameResult result;
            int playerCount = GetPlayerCount();
            result.players.resize(playerCount);
            for (int i = 0; i < playerCount; ++i)
            {
                result.players[i].state = GetPlayerState(i);
                int score = gameState.player[i].money;
                result.players[i].score = gameState.player[i].money;
                int rank = 1;
                for (int j = 0; j < playerCount; ++j)
                    if (result.players[j].score > score)
                        ++rank;
                result.players[i].rank = rank;
            }
            return result;
        }

        bool GameServer::ShouldPlay()
        {
            return gameState.turn < gameSetup.turns;
        }

        bool GameServer::CanPlayThisTurn(int player)
        {
            return true;
        }

        std::chrono::milliseconds GameServer::GetNextTurnTimeLimit(int player)
        {
            return std::chrono::milliseconds(gameSetup.turnTimeLimit);
        }

        std::chrono::milliseconds GameServer::GetSetupTimeLimit(int player)
        {
            return std::chrono::milliseconds(gameSetup.setupTimeLimit);
        }

        std::chrono::milliseconds GameServer::GetCleanupTimeLimit(int player)
        {
            return std::chrono::milliseconds(gameSetup.setupTimeLimit);
        }

        class GameServerEntryPoint : public ugly::server::GameServerEntryPoint
        {
        public:
            GameServerEntryPoint(std::shared_ptr<ugly::loader::LibraryHandler> library)
                : library(library)
            {}

            ugly::loader::unique_ptr<ugly::server::IGame> CreateGame(const util::CommandLine& params) const
            {
                return ugly::loader::make_unique<GameServer>(library);
            }
        private:
            std::shared_ptr<ugly::loader::LibraryHandler> library;
        };
    }
}

extern "C"
{
#ifdef _MSC_VER
    __declspec(dllexport)
#endif
    void ugly_GameServerEntryPoint(void* registry, void* library);
}

void ugly_GameServerEntryPoint(void* registry, void* library)
{
    std::shared_ptr<ugly::loader::LibraryHandler> libraryPtr = *((std::shared_ptr<ugly::loader::LibraryHandler>*)library);
    static_cast<ugly::server::GameServerRegistry*>(registry)->RegisterEntryPoint(ugly::loader::make_unique<ugly::FreeMarket::GameServerEntryPoint>(libraryPtr, libraryPtr));
}