#pragma once

namespace Game
{
    class EndGameScreen
    {
    public:
        bool Init(Engine::EntityManager* entityManager_, Engine::TextureManager* textureManager_);
        void Update(float dt, Engine::EntityManager* entityManager_, Engine::SoundManager* soundManager_, Engine::CurrentGameState* gameState);
    };
}