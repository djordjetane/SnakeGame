#pragma once

namespace Game
{
    struct GameModeSettings;

    class GameModeMenu
    {
    public:
        int selected = 1;
        bool Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_1,
            Engine::Texture* texture_2, Engine::Texture* texture_3, Engine::Texture* texture_4, Engine::Texture* texture_5, 
            Engine::Texture* texture_6, Engine::Texture* texture_7, Engine::Texture* texture_8, Engine::Texture* texture_9, 
            Engine::Texture* texture_10, Engine::Texture* texture_11, Engine::Texture* texture_12, Engine::Texture* texture_13, 
            Engine::Texture* texture_14);
        void Update(float dt, Engine::EntityManager* entityManager_, Engine::CurrentGameState* gameState, Engine::GameStates gameMode, Engine::GameModeSettings* gameModeSettings);
    };
}