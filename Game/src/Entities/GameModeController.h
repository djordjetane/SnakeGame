#pragma once

namespace Game
{
    struct GameModeSettings;

    class GameModeMenu
    {
    public:
        int selected = 1;
        bool Init(Engine::EntityManager* entityManager_, Engine::TextureManager* textureManager_);
        void Update(float dt, Engine::EntityManager* entityManager_, Engine::CurrentGameState* gameState, Engine::GameStates gameMode, Engine::GameModeSettings* gameModeSettings);
    };
}