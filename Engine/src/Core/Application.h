#pragma once

#include "Render/WindowData.h"

namespace Engine {

    class RenderSystem;
    class PhysicsSystem;
    class InputManager;
    class EntityManager;
    class TextureManager;
    class SoundHandler;
    class SoundManager;

    struct GameModeSettings {
        bool areBordersDeath;
        bool areBumpersDeath;
        int difficulty;
    };

    enum class GameStates {
        MainMenu,
        PlayingLevel,
        PlayingInfiniteLevel,
        GameModeMenu,
        RestartingLevel,
        ResumingLevel,
        LevelWon,
        LevelLost,
        PauseMenu,
        EndGameScreen,
        QuitGame
    };

    struct CurrentGameState {
        Engine::GameStates m_CurrentState;
    };

    class Application
    {
    public:
        bool Init();
        int Run();
        bool Shutdown();

        virtual ~Application();
        Application() = default;

    protected:
        void SetWindowData(const WindowData& windowData_) { m_WindowData = windowData_; }

        bool m_Running{ false };

        WindowData m_WindowData{};
        std::unique_ptr<RenderSystem> m_RenderSystem{};
        std::unique_ptr<PhysicsSystem> m_PhysicsSystem{};
        std::unique_ptr<InputManager> m_InputManager{};
        std::unique_ptr<EntityManager> m_EntityManager{};
        std::unique_ptr<TextureManager> m_TextureManager{};
        std::unique_ptr<CurrentGameState> m_CurrentGameState{};
        std::unique_ptr<SoundHandler> m_SoundHandler{};
        std::unique_ptr<SoundManager> m_SoundManager{};
    private:
        // To be overridden by the game
        virtual void GameSpecificWindowData() = 0;
        virtual bool GameSpecificInit() = 0;
        virtual bool GameSpecificShutdown() = 0;
        virtual void GameSpecificUpdate(float dt) = 0;

        void Update(float dt);

        Application(const Application& other) = delete;
        Application& operator=(Application& other) = delete;
    };

    // To be defined in the game
    Application* CreateApplication();
}
