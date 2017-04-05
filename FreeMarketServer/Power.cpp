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
            , buildingSource()
        { }
            
        Power::Power()
            : type()
            , quantity()
            , quantityForced()
            , resource()
            , resourceForced()
            , buildingSource()
        { }
            
        Action::Action()
            : id()
            , power()
            , actionPoint()
            , priority()
        { }
            
        bool ActionPrivate::Execute(const GameConfig& gameSetup, const PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState, const Action& action, const PowerParameter& parameter, std::unique_ptr<ActionSource> source)
        {
            if (!source->TryConsumeActionPoints(action.actionPoint))
                return false;

            ResolvedPowerParameter resolved;
            resolved.powerOwner = std::move(source);
            switch (action.power.buildingSource)
            {
            case ParameterType::Self:
                resolved.source = resolved.powerOwner;
                break;
            case ParameterType::Choice:
                resolved.source = std::shared_ptr<ActionSource>(new BuildingActionSource(*parameter.buildingSource));
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
            if (!parameter.source)
                return false;
            if (parameter.quantity == 0 || parameter.quantity == ParameterConstant::None)
                return false;
            int resourceCapacity = parameter.source->GetResourceCapacity();
            int resources = 0;
            for (int r = 0; r < gameSetup.resourceCount; ++r)
                resources += parameter.source->GetResource(r);
            if (resources >= resourceCapacity)
                return false;
            if (parameter.resource == ParameterConstant::All)
            {
                for (int r = 0; r < gameSetup.resourceCount && resources < resourceCapacity; ++r)
                {
                    int addedResources = std::min(parameter.quantity, resourceCapacity - resources);
                    parameter.source->SetResource(r, parameter.source->GetResource(r) + addedResources);
                    resources += addedResources;
                }
            }
            else
            {
                int addedResources = std::min(parameter.quantity, resourceCapacity - resources);
                parameter.source->SetResource(parameter.resource, parameter.source->GetResource(parameter.resource) + addedResources);
            }
            return true;
        }

        bool ActionPrivate::ExecuteSellResource(const GameConfig& gameSetup, const PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState, const Action& action, const ResolvedPowerParameter& parameter)
        {
            if (parameter.resource == ParameterConstant::None)
                return false;
            if (!parameter.source)
                return false;
            if (parameter.quantity == 0 || parameter.quantity == ParameterConstant::None)
                return false;
            if (parameter.resource == ParameterConstant::All)
            {
                bool resourceSold = false;
                for (int r = 0; r < gameSetup.resourceCount; ++r)
                {
                    int currentResource = parameter.source->GetResource(r);
                    if (currentResource > 0)
                    {
                        resourceSold = true;
                        int resourceSoldCount = (parameter.quantity == ParameterConstant::All ? currentResource : std::min(parameter.quantity, currentResource));
                        parameter.source->SetResource(r, currentResource - resourceSoldCount);
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
                return resourceSold;
            }
            else
            {
                int currentResource = parameter.source->GetResource(parameter.resource);
                if (currentResource <= 0)
                    return false;
                int resourceSoldCount = (parameter.quantity == ParameterConstant::All ? currentResource : std::min(parameter.quantity, currentResource));
                parameter.source->SetResource(parameter.resource, currentResource - resourceSoldCount);
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
                return true;
            }
        }
    }
}