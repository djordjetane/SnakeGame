#pragma once

namespace Game
{
    class Stadium
    {
    public:
        bool Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_, Engine::Texture* textureWall_);
        bool InitLvlCpp(Engine::EntityManager* entityManager_);
        bool InitLvl1(Engine::EntityManager* entityManager_);
        bool InitLvl2(Engine::EntityManager* entityManager_);
        void Destroy(Engine::EntityManager* entityManager_);
    private:
        Engine::Texture* m_textureBumper;
    };
}