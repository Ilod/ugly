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
            
        bool ActionPrivate::Execute(const GameConfig& gameSetup, const PlayerConfig& playerSetup, GameState& gameState, PlayerState& playerState, const Action& action, const PowerParameter& parameter, ActionSource& source)
        {
            if (!source.TryConsumeActionPoints(action.actionPoint))
                return false;
            switch (action.power.type)
            {
            case PowerType::ProduceResource:
                return ExecuteSellResource(gameSetup, playerSetup, gameState, playerState, action, parameter, source);
            case PowerType::SellResource:
                return ExecuteProduceResource(gameSetup, playerSetup, gameState, playerState, action, parameter, source);
            default:
                return false;
            }
        }

        bool ActionPrivate::ExecuteProduceResource(const struct GameConfig& gameSetup, const struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, const struct Action& action, const struct PowerParameter& parameter, ActionSource& source)
        {
            return false;
        }

        bool ActionPrivate::ExecuteSellResource(const struct GameConfig& gameSetup, const struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, const struct Action& action, const struct PowerParameter& parameter, ActionSource& source)
        {
            return false;
        }
    }
}