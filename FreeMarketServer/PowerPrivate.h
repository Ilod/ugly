#pragma once
#include <memory>

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

        namespace ParameterConstant
        {
            const int None = -1;
            const int All = -2;
        }

        struct ResolvedPowerParameter
        {
            std::shared_ptr<ActionSource> powerOwner;
            std::shared_ptr<ActionSource> source;
            std::shared_ptr<ActionSource> target;
            int quantity = ParameterConstant::None;
            int resource = ParameterConstant::None;
        };

        struct ActionPrivate
        {
            bool Execute                (const struct GameConfig& gameSetup, const struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, const struct Action& action, const struct PowerParameter& parameter, std::unique_ptr<ActionSource> source);
            bool ExecuteProduceResource (const struct GameConfig& gameSetup, const struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, const ResolvedPowerParameter& parameter);
            bool ExecuteSellResource    (const struct GameConfig& gameSetup, const struct PlayerConfig& playerSetup, struct GameState& gameState, struct PlayerState& playerState, const ResolvedPowerParameter& parameter);
        };

        namespace ActionPriority
        {
            static const std::int32_t ResourceSelling = 0;
            static const std::int32_t ResourceProduction = 1;
        }
    }
}