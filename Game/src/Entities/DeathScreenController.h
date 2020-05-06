#pragma once

namespace Game
{
    class DeathScreen
    {
    public:
        float time_passed = 0.f;
        bool Init(Engine::EntityManager* entityManager_, Engine::TextureManager* textureManager_);
        void Update(float dt, Engine::EntityManager* entityManager_, Engine::CurrentGameState* gameState, Engine::GameStates gameMode);
    };
}