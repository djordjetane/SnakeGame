#pragma once

namespace Game
{
    class PauseMenu
    {
    public:
        bool Init(Engine::EntityManager* entityManager_, Engine::TextureManager* textureManager_);
        void Update(float dt, Engine::EntityManager* entityManager_, Engine::CurrentGameState* gameState, Engine::GameStates gameMode);
    };
}