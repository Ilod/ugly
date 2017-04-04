#include "Building.h"
#include "Serializer.h"
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
            , action()
        { }
            
        BuildingCard::BuildingCard()
            : id()
            , building()
            , owner()
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

            gameState.buildingCard.erase(std::find_if(gameState.buildingCard.begin(), gameState.buildingCard.end(), [this](const BuildingCard& other) { return other.id == id; }));

            return true;
        }

        Building::Building()
            : id()
            , type()
            , position()
            , owner()
            , actionPoint()
        { }
            
        bool Building::Execute(struct GameConfig& gameSetup, struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, Action& action, PowerParameter& param, const std::string& orderStr)
        {
            return false;
        }
    }
}