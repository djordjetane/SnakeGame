#pragma once

namespace Game
{
    class ResumeScreen
    {
    public:
        float time_passed = 0.f;
        bool Init(Engine::EntityManager* entityManager_, Engine::TextureManager* textureManager_);
        void Update(float dt, Engine::EntityManager* entityManager_, Engine::SoundManager* soundManager_, Engine::CurrentGameState* gameState, Engine::GameStates gameMode, int level);
        void Destroy(Engine::EntityManager* entityManager_);
    };
}