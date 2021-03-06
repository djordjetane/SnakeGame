#pragma once

#include <Core\Application.h>

namespace Game
{
    
    class GameApp final : public Engine::Application
    {
    private:
        bool m_firstLoad;
        bool m_firstResumeLoad = true;
        bool m_firstPauseLoad = true;
        int m_level = 1;

        Engine::GameStates m_GameMode;

        void GameSpecificWindowData() override;
        bool GameSpecificInit() override;
        void GameSpecificUpdate(float dt) override;
        bool GameSpecificShutdown() override;

        std::unique_ptr<Engine::GameModeSettings> m_GameModeSettings{};

        std::unique_ptr<PlayerController> m_PlayerController{};
        std::unique_ptr<CameraController> m_CameraController{};
        std::unique_ptr<FruitController> m_FruitController{};
        std::unique_ptr<Stadium> m_Stadium{};    
        std::unique_ptr<MainMenu> m_MainMenu{};
        std::unique_ptr<PauseMenu> m_PauseMenu{};
        std::unique_ptr<ResumeScreen> m_ResumeScreen{};
        std::unique_ptr<GameModeMenu> m_GameModeMenu{};
        std::unique_ptr<DeathScreen> m_DeathScreen{};
        std::unique_ptr<VictoryScreen> m_VictoryScreen{};
        std::unique_ptr<ScoreController> m_ScoreController{};
        std::unique_ptr<EndGameScreen> m_EndGameScreen{};
    };

}

Engine::Application* Engine::CreateApplication()
{
    return new Game::GameApp();
}
