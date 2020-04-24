#pragma once

namespace Game
{
    class PauseMenu
    {
    public:
        bool Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_1,
            Engine::Texture* texture_2, Engine::Texture* texture_3, Engine::Texture* texture_4);
        void Update(float dt, Engine::EntityManager* entityManager_, Engine::GameState* gameState);
    };
}