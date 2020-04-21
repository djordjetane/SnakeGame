#pragma once

namespace Game
{
    enum class EHeadDirection
    {
        Left = 0,
        Right,
        Up,
        Down,

        PlayerDirectionStateCount
    };

    struct HeadComponent : public Engine::Component
    {
        EHeadDirection m_Direction;

        HeadComponent() = default;
        HeadComponent(EHeadDirection dir) : m_Direction(dir) {};
    };


    struct FruitComponent : public Engine::Component
    {
        
    };

    struct SuperFruitComponent : public Engine::Component
    {

    };

    struct GridComponent : public Engine::Component
    {

    };

    struct GoalComponent : public Engine::Component
    {

    };
}