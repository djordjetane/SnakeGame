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
        bool m_HasEatenFruit{false};
        bool m_HasEatenSuperFruit{false};

        HeadComponent() = default;
        HeadComponent(EHeadDirection dir) : m_Direction(dir) {};
    };

    struct BodyComponent : public Engine::Component {
        int m_Index;

        BodyComponent() = default;
        BodyComponent(int i) : m_Index(i) {};
    };

    struct PositionComponent : public Engine::Component {
        vec2 m_Positions[100];
        int m_CurrentLength=3;
    };

    struct FruitComponent : public Engine::Component
    {
        
    };

    struct SuperFruitComponent : public Engine::Component
    {
        bool m_shown = false;
    };

    struct SelectionComponent : public Engine::Component
    {

    };

    struct MainMenuComponent : public Engine::Component
    {

    };

    struct PauseMenuComponent : public Engine::Component
    {

    };

    struct PauseSelectionComponent : public Engine::Component
    {

    };

    struct GridComponent : public Engine::Component
    {

    };

    struct GoalComponent : public Engine::Component
    {

    };

    struct BumperComponent : public Engine::Component
    {

    };

    struct HelperComponent : public Engine::Component
    {

    };
}