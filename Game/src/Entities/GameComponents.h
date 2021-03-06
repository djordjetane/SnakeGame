#pragma once
#include "GameData.h"

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
        vec2 m_Positions[MAX_SNAKE_LENGTH];
        int m_CurrentLength=START_SNAKE_LENGTH;
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

    struct ResumeScreenComponent : public Engine::Component
    {
        int numInQueue = 5;
    };

    struct GameModeMenuComponent : public Engine::Component
    {

    };

    struct GameModeMenuSelectionComponent : public Engine::Component
    {

    };

    struct GameModeMenuHighlightComponent : public Engine::Component
    {
        int numOfHighlight = 1;
    };
    
    struct DeathScreenComponent : public Engine::Component {

    };

    struct DeathSelectComponent : public Engine::Component {

    };

    struct WinScreenSelectionComponent : public Engine::Component {

    };

    struct WinScreenComponent : public Engine::Component{

    };

    struct EndGameComponent : public Engine::Component {

    };

    struct EndGameSelectionComponent : public Engine::Component {

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

    struct ScoreComponent : public Engine::Component
    {
        int m_Score;
    };
   
}