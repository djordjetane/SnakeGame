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

    struct BodyComponent : public Engine::Component {
        int m_Index;

        BodyComponent() = default;
        BodyComponent(int i) : m_Index(i) {};
    };

    struct PositionComponent : public Engine::Component {
        vec2 m_Positions[25];
        int m_CurrentLength=5;

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