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

            switch (action.power.type)
            {
            case PowerType::ProduceResource:
                return ExecuteSellResource(gameSetup, playerSetup, gameState, playerState, action, parameter, std::move(source));
            case PowerType::SellResource:
                return ExecuteProduceResource(gameSetup, playerSetup, gameState, playerState, action, parameter, std::move(source));
            default:
                return false;
            }
        }

        bool ActionPrivate::ExecuteProduceResource(const GameConfig& gameSetup, const PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState, const Action& action, const PowerParameter& parameter, std::unique_ptr<ActionSource> source)
        {
            return false;
        }

        bool ActionPrivate::ExecuteSellResource(const GameConfig& gameSetup, const PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState, const Action& action, const PowerParameter& parameter, std::unique_ptr<ActionSource> source)
        {
            return false;
        }
    }
}