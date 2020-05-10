#pragma once

namespace Game
{
    class Stadium
    {
    public:
        bool Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_, Engine::TextureManager* textureManager_);
        bool InitLvlCpp(Engine::EntityManager* entityManager_);
        bool InitLvl1(Engine::EntityManager* entityManager_);
        bool InitLvl2(Engine::EntityManager* entityManager_);
        void Destroy(Engine::EntityManager* entityManager_);
    private:
        Engine::TextureManager* m_TextureManager;
    };
}