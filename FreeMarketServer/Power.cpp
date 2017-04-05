#include "Power.h"
#include "Serializer.h"
#include <cstdio>

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
                return ExecuteSellResource(gameSetup, playerSetup, gameState, playerState, resolved);
            case PowerType::SellResource:
                return ExecuteProduceResource(gameSetup, playerSetup, gameState, playerState, resolved);
            default:
                return false;
            }
        }

        bool ActionPrivate::ExecuteProduceResource(const GameConfig& gameSetup, const PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState, const ResolvedPowerParameter& parameter)
        {
            return false;
        }

        bool ActionPrivate::ExecuteSellResource(const GameConfig& gameSetup, const PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState, const ResolvedPowerParameter& parameter)
        {
            return false;
        }
    }
}