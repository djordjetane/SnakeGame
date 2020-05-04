#pragma once

namespace Game
{
    class MainMenu
    {
    public:
        bool Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_1, 
            Engine::Texture* texture_2, Engine::Texture* texture_3, Engine::Texture* texture_4, Engine::Texture* texture_5);
        void Update(float dt, Engine::EntityManager* entityManager_, Engine::CurrentGameState* gameState);
    };
}