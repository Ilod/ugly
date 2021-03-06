#include "Building.h"
#include "Serializer.h"
#include "Power.h"
#include <algorithm>
#include <cstdio>

namespace ugly
{
    namespace FreeMarket
    {
        BuildingType::BuildingType()
            : id()
            , actionPointMax()
            , actionPointGain()
            , resourceCapacity()
        { }
            
        BuildingCard::BuildingCard()
            : id()
            , building()
            , owner(Player::City)
        { }
            
        bool BuildingCard::Build(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, Cell& position, const std::string& orderStr)
        {
            if (owner != playerState.id || position.owner != playerState.id || position.ownership != Ownership::Own || position.building != nullptr)
                return false;
            if (position.type == CellType::Road || position.type == CellType::Work)
                return false;
            gameState.building.push_back(Building());
            gameState.building.back().id = gameState.additionalData.nextBuildingId++;
            gameState.building.back().owner = playerState.id;
            gameState.building.back().position = &position;
            gameState.building.back().type = building;
            gameState.building.back().resource.resize(gameSetup.resourceCount);

            gameState.buildingCard.erase(std::find_if(gameState.buildingCard.begin(), gameState.buildingCard.end(), [this](const BuildingCard& other) { return other.id == id; }));

            return true;
        }

        Building::Building()
            : id()
            , type()
            , position()
            , owner(Player::City)
            , actionPoint()
        { }
            
        bool Building::Execute(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, Action& action, PowerParameter& param, const std::string& orderStr)
        {
            if (!gameState.additionalData.executeDelayed)
            {
                gameState.additionalData.delayedOrders[action.priority].push_back(std::make_tuple(orderStr, playerSetup.id));
                return true;
            }
            return action.additionalData.Execute(gameSetup, playerSetup, gameState, playerState, action, param, std::unique_ptr<ActionSource>(new BuildingActionSource(*this)));
        }

        BuildingActionSource::BuildingActionSource(Building& building) : building(building) {}

        bool BuildingActionSource::TryConsumeActionPoints(int actionPoints)
        {
            if (building.actionPoint < actionPoints)
                return false;
            building.actionPoint -= actionPoints;
            return true;
        }

        Cell* BuildingActionSource::GetCell()
        {
            return building.position;
        }

        int BuildingActionSource::GetResourceCapacity()
        {
            return building.type->resourceCapacity;
        }

        int BuildingActionSource::GetResource(int resource)
        {
            return building.resource[resource];
        }

        void BuildingActionSource::SetResource(int resource, int quantity)
        {
            building.resource[resource] = quantity;
        }
    }
}