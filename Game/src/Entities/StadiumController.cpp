#include "precomp.h"
#include "StadiumController.h"

#include "Entities/GameComponents.h"

namespace Game
{
    bool Stadium::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_, Engine::Texture* textureWall_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to BallController::Init()");

        m_textureWall = textureWall_;

        auto grid = std::make_unique<Engine::Entity>(); 
        grid->AddComponent<Engine::TransformComponent>(0.f, 0.f, 1280.f, 736.f);
        grid->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

        entityManager_->AddEntity(std::move(grid));        

        return true;
    }

    bool Stadium::InitLvlCpp(Engine::EntityManager* entityManager_)
    {
        // C
        // Vertical
        auto wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<Engine::TransformComponent>(-450.f, 0.f, 100.f, 500.f);
        wall->AddComponent<Engine::CollisionComponent>(100.f, 500.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));
        // C Up horizontal
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<Engine::TransformComponent>(-300.f, -200.f, 200.f, 100.f);
        wall->AddComponent<Engine::CollisionComponent>(200.f, 100.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));
        // C Up horizontal
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<Engine::TransformComponent>(-300.f, 200.f, 200.f, 100.f);
        wall->AddComponent<Engine::CollisionComponent>(200.f, 100.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));

        // First plus
        // horizontal
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<Engine::TransformComponent>(0.f, 0.f, 100.f, 200.f);
        wall->AddComponent<Engine::CollisionComponent>(100.f, 200.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));
        // vertical
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<Engine::TransformComponent>(0.f, 0.f, 200.f, 100.f);
        wall->AddComponent<Engine::CollisionComponent>(200.f, 100.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));

        // Second plus
        // horizontal
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<Engine::TransformComponent>(300.f, 0.f, 100.f, 200.f);
        wall->AddComponent<Engine::CollisionComponent>(100.f, 200.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));
        // vertical
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<Engine::TransformComponent>(300.f, 0.f, 200.f, 100.f);
        wall->AddComponent<Engine::CollisionComponent>(200.f, 100.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));
    }
}