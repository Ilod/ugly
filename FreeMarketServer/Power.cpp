#include "Power.h"
#include "Serializer.h"
#include <cstdio>
#include <algorithm>

namespace ugly
{
    namespace FreeMarket
    {
        PowerParameter::PowerParameter()
            : quantity()
            , resource()
            , buildingTarget()
        { }
            
        Power::Power()
            : type()
            , quantity()
            , quantityForced(-1)
            , resource()
            , resourceForced(-1)
            , buildingTarget()
            , buildingTargetOwner()
            , boost()
            , boostPower()
            , range(-1)
        { }
            
        Action::Action()
            : id()
            , power()
            , actionPoint()
            , priority()
        { }

        namespace
        {
            Owner GetOwnerType(int activePlayer, int otherPlayer, const GameConfig& gameSetup)
            {
                if (activePlayer == otherPlayer)
                    return Owner::Self;
                if (otherPlayer < 0)
                    return Owner::City;
                if (gameSetup.player[activePlayer].team == gameSetup.player[otherPlayer].team)
                    return Owner::Ally;
                return Owner::Opponent;
            }
        }
            
        bool ActionPrivate::Execute(const GameConfig& gameSetup, const PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState, const Action& action, const PowerParameter& parameter, std::unique_ptr<ActionSource> source)
        {
            if (!source->TryConsumeActionPoints(action.actionPoint))
                return false;

            ResolvedPowerParameter resolved;
            resolved.powerOwner = std::move(source);
            switch (action.power.buildingTarget)
            {
            case ParameterType::Self:
                resolved.target.push_back(resolved.powerOwner);
                break;
            case ParameterType::Choice:
                if (!parameter.buildingTarget)
                    return false;
                if (action.power.range >= 0 && CellPrivate::GetDistance(resolved.powerOwner->GetCell(), parameter.buildingTarget->position) > action.power.range)
                    return false;
                if (!(GetOwnerType(playerSetup.id, parameter.buildingTarget->owner, gameSetup) & action.power.buildingTargetOwner))
                    return false;
                resolved.target.push_back(std::shared_ptr<ActionSource>(new BuildingActionSource(*parameter.buildingTarget)));
                break;
            case ParameterType::All:
                for (Building& building : gameState.building)
                {
                    if ((action.power.range < 0 || CellPrivate::GetDistance(resolved.powerOwner->GetCell(), building.position) <= action.power.range) && (GetOwnerType(playerSetup.id, building.owner, gameSetup) & action.power.buildingTargetOwner))
                    {
                        resolved.target.push_back(std::shared_ptr<ActionSource>(new BuildingActionSource(building)));
                    }
                }
                break;
            }
            switch (action.power.quantity)
            {
            case ParameterType::Forced:
                resolved.quantity = action.power.quantityForced;
                break;
            case ParameterType::Choice:
                resolved.quantity = parameter.quantity;
                if (resolved.quantity < 0)
                    resolved.quantity = 0;
                if (action.power.quantityForced > 0 && resolved.quantity > action.power.quantityForced)
                    resolved.quantity = action.power.quantityForced;
                break;
            case ParameterType::All:
                resolved.quantity = ParameterConstant::All;
                break;
            }
            switch (action.power.resource)
            {
            case ParameterType::All:
                resolved.resource = ParameterConstant::All;
                break;
            case ParameterType::Choice:
                resolved.resource = parameter.resource;
                if (resolved.resource < 0 || resolved.resource > gameSetup.resourceCount)
                    resolved.resource = ParameterConstant::None;
                break;
            case ParameterType::Forced:
                resolved.resource = action.power.resourceForced;
                break;
            }

            switch (action.power.type)
            {
            case PowerType::ProduceResource:
                return ExecuteSellResource(gameSetup, playerSetup, gameState, playerState, action, resolved);
            case PowerType::SellResource:
                return ExecuteProduceResource(gameSetup, playerSetup, gameState, playerState, action, resolved);
            default:
                return false;
            }
        }

        bool ActionPrivate::ExecuteProduceResource(const GameConfig& gameSetup, const PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState, const Action& action, const ResolvedPowerParameter& parameter)
        {
            if (parameter.resource == ParameterConstant::None)
                return false;
            if (parameter.target.empty())
                return false;
            if (parameter.quantity == 0 || parameter.quantity == ParameterConstant::None)
                return false;
            bool resourceProduced = false;
            for (std::shared_ptr<ActionSource> target : parameter.target)
            {
                int resourceCapacity = target->GetResourceCapacity();
                int resources = 0;
                for (int r = 0; r < gameSetup.resourceCount; ++r)
                    resources += target->GetResource(r);
                if (resources >= resourceCapacity)
                    continue;
                if (parameter.resource == ParameterConstant::All)
                {
                    for (int r = 0; r < gameSetup.resourceCount && resources < resourceCapacity; ++r)
                    {
                        int addedResources = std::min(parameter.quantity, resourceCapacity - resources);
                        target->SetResource(r, target->GetResource(r) + addedResources);
                        resources += addedResources;
                    }
                }
                else
                {
                    resourceProduced = true;
                    int addedResources = std::min(parameter.quantity, resourceCapacity - resources);
                    target->SetResource(parameter.resource, target->GetResource(parameter.resource) + addedResources);
                }
            }
            return resourceProduced;
        }

        bool ActionPrivate::ExecuteSellResource(const GameConfig& gameSetup, const PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState, const Action& action, const ResolvedPowerParameter& parameter)
        {
            if (parameter.resource == ParameterConstant::None)
                return false;
            if (parameter.target.empty())
                return false;
            if (parameter.quantity == 0 || parameter.quantity == ParameterConstant::None)
                return false;
            bool resourceSold = false;
            for (std::shared_ptr<ActionSource> target : parameter.target)
            {
                if (parameter.resource == ParameterConstant::All)
                {
                    for (int r = 0; r < gameSetup.resourceCount; ++r)
                    {
                        int currentResource = target->GetResource(r);
                        if (currentResource > 0)
                        {
                            resourceSold = true;
                            int resourceSoldCount = (parameter.quantity == ParameterConstant::All ? currentResource : std::min(parameter.quantity, currentResource));
                            target->SetResource(r, currentResource - resourceSoldCount);
                            int resourcePrice = gameState.resourcePrice[r];
                            switch (action.power.boost)
                            {
                            case BoostType::Fixed:
                                resourcePrice = std::max(0, resourcePrice + action.power.boostPower);
                                break;
                            case BoostType::Percent:
                                resourcePrice = resourcePrice * (100 + action.power.boostPower) / 100;
                                break;
                            }
                            playerState.money += resourcePrice * resourceSoldCount;
                        }
                    }
                }
                else
                {
                    int currentResource = target->GetResource(parameter.resource);
                    if (currentResource <= 0)
                        continue;
                    resourceSold = true;
                    int resourceSoldCount = (parameter.quantity == ParameterConstant::All ? currentResource : std::min(parameter.quantity, currentResource));
                    target->SetResource(parameter.resource, currentResource - resourceSoldCount);
                    int resourcePrice = gameState.resourcePrice[parameter.resource];
                    switch (action.power.boost)
                    {
                    case BoostType::Fixed:
                        resourcePrice = std::max(0, resourcePrice + action.power.boostPower);
                        break;
                    case BoostType::Percent:
                        resourcePrice = resourcePrice * (100 + action.power.boostPower) / 100;
                        break;
                    }
                    playerState.money += resourcePrice * resourceSoldCount;
                }
            }
            return resourceSold;
        }
    }
}