#pragma once

namespace Engine
{
    class EntityManager;
    class TextureManager;
}

namespace Game
{
    class PlayerController
    {
    public:
        int m_framerate=0;
        float m_passedTime=0.f;
        int m_inputDelay = 0;

        bool Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_);
        void Update(float dt, Engine::EntityManager* entityManager_, Engine::GameModeSettings* gameModeSettings, Engine::CurrentGameState* gameState, Engine::GameStates gameMode, Engine::SoundManager* soundManager_);
        void ActivateBodyPart(Engine::EntityManager* entityManager_, int index, vec2 position);
        void AppendSnake(Engine::EntityManager* entityManager_, int length);
        void ResetSnake(Engine::EntityManager* entityManager_);
        bool CheckWinCondition(Engine::EntityManager* entityManager_, Engine::GameModeSettings* gameModeSettings);
    };
}