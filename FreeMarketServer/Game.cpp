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
                gameSetup.resourceCount = 3;
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

                {
                    BuildingType building;
                    building.id = -1;
                    Action action;
                    
                    {
                        building.action.clear();
                        ++building.id;
                        building.actionPointMax = 3;
                        building.actionPointGain = 3;
                        building.additionalData.probability = 0;

                        action.id = -1;

                        ++action.id;
                        action.actionPoint = 1;
                        action.priority = ActionPriority::ResourceSelling;
                        action.power.buildingSource = ParameterType::Choice;
                        action.power.quantity = ParameterType::Choice;
                        action.power.quantityForced = -1;
                        action.power.resource = ParameterType::Choice;
                        action.power.resourceForced = -1;
                        action.power.type = FreeMarket::PowerType::SellResource;
                        building.action.push_back(action);

                        gameSetup.building.push_back(building);
                    }

                    for (int r = 0; r < gameSetup.resourceCount; ++r)
                    {
                        building.action.clear();
                        ++building.id;
                        building.actionPointMax = 1;
                        building.actionPointGain = 1;
                        building.additionalData.probability = 100;

                        action.id = -1;

                        ++action.id;
                        action.actionPoint = 1;
                        action.priority = ActionPriority::ResourceProduction;
                        action.power.buildingSource = ParameterType::Self;
                        action.power.quantity = ParameterType::Forced;
                        action.power.quantityForced = 2;
                        action.power.resource = ParameterType::Forced;
                        action.power.resourceForced = r;
                        action.power.type = FreeMarket::PowerType::ProduceResource;
                        building.action.push_back(action);

                        gameSetup.building.push_back(building);
                    }

                    for (int r = 0; r < gameSetup.resourceCount; ++r)
                    {
                        building.action.clear();
                        ++building.id;
                        building.actionPointMax = 1;
                        building.actionPointGain = 1;
                        building.additionalData.probability = 10;

                        action.id = -1;

                        ++action.id;
                        action.actionPoint = 1;
                        action.priority = ActionPriority::ResourceProduction;
                        action.power.buildingSource = ParameterType::Self;
                        action.power.quantity = ParameterType::Forced;
                        action.power.quantityForced = 5;
                        action.power.resource = ParameterType::Forced;
                        action.power.resourceForced = r;
                        action.power.type = FreeMarket::PowerType::ProduceResource;
                        building.action.push_back(action);

                        gameSetup.building.push_back(building);
                    }

                    {
                        building.action.clear();
                        ++building.id;
                        building.actionPointMax = 1;
                        building.actionPointGain = 1;
                        building.additionalData.probability = 15;

                        action.id = -1;

                        ++action.id;
                        action.actionPoint = 1;
                        action.priority = ActionPriority::ResourceProduction;
                        action.power.buildingSource = ParameterType::Self;
                        action.power.quantity = ParameterType::Forced;
                        action.power.quantityForced = 1;
                        action.power.resource = ParameterType::All;
                        action.power.resourceForced = -1;
                        action.power.type = FreeMarket::PowerType::ProduceResource;
                        building.action.push_back(action);

                        gameSetup.building.push_back(building);
                    }

                    {
                        building.action.clear();
                        ++building.id;
                        building.actionPointMax = 1;
                        building.actionPointGain = 1;
                        building.additionalData.probability = 15;

                        action.id = -1;

                        ++action.id;
                        action.actionPoint = 1;
                        action.priority = ActionPriority::ResourceProduction;
                        action.power.buildingSource = ParameterType::Self;
                        action.power.quantity = ParameterType::Forced;
                        action.power.quantityForced = 2;
                        action.power.resource = ParameterType::Choice;
                        action.power.resourceForced = -1;
                        action.power.type = FreeMarket::PowerType::ProduceResource;
                        building.action.push_back(action);

                        gameSetup.building.push_back(building);
                    }

                    {
                        int proba = 100;
                        for (int p = 0; p <= players; ++p)
                        {
                            gameSetup.additionalData.auctionProbability.push_back(proba);
                            proba = proba * 2 / 3;
                        }
                    }
                }
            }

            void InitStateData(GameConfig& gameSetup, GameState& gameState)
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
                for (int p = 0; p < (int)gameSetup.player.size(); ++p)
                {
                    Building building;
                    building.owner = p;
                    building.id = p;
                    building.type = &gameSetup.building[0];
                    building.position = &gameState.map[((p % 2) == 0) ? 11 : (gameSetup.mapSizeX - 11)][((p / 2) == 0) ? 12 : (gameSetup.mapSizeY - 12)];
                    gameState.building.push_back(building);
                }
                {
                    std::random_device rdn;
                    std::default_random_engine generator(rdn());
                    std::discrete_distribution<> auctionCount(gameSetup.additionalData.auctionProbability.begin(), gameSetup.additionalData.auctionProbability.end());
                    auto beginRange = ugly::util::CreateSelectIteratorAdapter(gameSetup.building.begin(), [](const BuildingType& type) { return type.additionalData.probability; });
                    auto endRange = ugly::util::CopyWithIterator(beginRange, gameSetup.building.end());
                    std::discrete_distribution<> auctionBuildingType(beginRange, endRange);
                    int auctionId = 0;
                    for (int t = 0; t <= gameSetup.turns; ++t)
                    {
                        for (int iAuction = 0, iAuctionEnd = auctionCount(generator); iAuction < iAuctionEnd; ++iAuction)
                        {
                            Auction auction;
                            auction.id = auctionId++;
                            auction.seller = Player::City;
                            auction.buyer = Player::None;
                            auction.price = 0;
                            auction.turn = t;
                            auction.type = AuctionType::Building;
                            auction.building = &gameSetup.building[auctionBuildingType(generator)];
                            gameState.auction.push_back(auction);
                        }
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
                        if (gameState.resourcePrice[r] < 1)
                            gameState.resourcePrice[r] = 1;
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