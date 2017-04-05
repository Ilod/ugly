#pragma once

namespace ugly
{
    namespace FreeMarket
    {
        struct Cell;

        struct PowerParameterPrivate
        {
        };
        struct PowerPrivate
        {
        };

        struct ActionSource
        {
            virtual ~ActionSource() {}
            virtual bool TryConsumeActionPoints(int actionPoints) = 0;
            virtual Cell* GetCell() = 0;
        };

        struct ActionPrivate
        {
            bool Execute                (const struct GameConfig& gameSetup, const struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, const struct Action& action, const struct PowerParameter& parameter, ActionSource& source);
            bool ExecuteProduceResource (const struct GameConfig& gameSetup, const struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, const struct Action& action, const struct PowerParameter& parameter, ActionSource& source);
            bool ExecuteSellResource    (const struct GameConfig& gameSetup, const struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, const struct Action& action, const struct PowerParameter& parameter, ActionSource& source);
        };
        namespace ActionPriority
        {
            static const std::int32_t ResourceSelling = 0;
            static const std::int32_t ResourceProduction = 1;
        }
    }
}