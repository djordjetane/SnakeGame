#pragma once

namespace Engine
{
    class EntityManager;
    class Entity;

    bool CheckForCollision(Entity* entity1, Entity* entity2);
    bool CheckForCollisionAABoxVsCircle(Entity* entity1, Entity* entity2);

    class PhysicsSystem
    {
    public:
        bool Init();
        void Update(float dt, EntityManager* entityManager);

    private:
    };
}