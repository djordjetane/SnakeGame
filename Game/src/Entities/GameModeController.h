#pragma once

namespace Game
{
    class GameModeMenu
    {
    public:
        bool m_isUpKeyReleased = true;
        bool m_isDownKeyReleased = true;
        bool m_isEnterKeyReleased = true;
        bool m_isSpaceKeyReleased = true;
        int selected = 1;
        bool Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_1,
            Engine::Texture* texture_2, Engine::Texture* texture_3, Engine::Texture* texture_4, Engine::Texture* texture_5, 
            Engine::Texture* texture_6, Engine::Texture* texture_7, Engine::Texture* texture_8, Engine::Texture* texture_9, 
            Engine::Texture* texture_10);
        void Update(float dt, Engine::EntityManager* entityManager_, Engine::GameState* gameState, Engine::GameState gameMode);
    };
}