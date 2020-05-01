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
        grid->AddComponent<Engine::TransformComponent>(0.f, 0.f, 1280.f, 720.f);
        grid->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

        entityManager_->AddEntity(std::move(grid));        

        return true;
    }

    bool Stadium::InitLvlCpp(Engine::EntityManager* entityManager_)
    {
        // C
        // Vertical
        auto wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<BumperComponent>();
        wall->AddComponent<Engine::TransformComponent>(-450.f, 0.f, 100.f, 500.f);
        wall->AddComponent<Engine::CollisionComponent>(100.f, 500.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));
        // C Up horizontal
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<BumperComponent>();
        wall->AddComponent<Engine::TransformComponent>(-300.f, -200.f, 200.f, 100.f);
        wall->AddComponent<Engine::CollisionComponent>(200.f, 100.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));
        // C Up horizontal
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<BumperComponent>();
        wall->AddComponent<Engine::TransformComponent>(-300.f, 200.f, 200.f, 100.f);
        wall->AddComponent<Engine::CollisionComponent>(200.f, 100.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));

        // First plus
        // horizontal
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<BumperComponent>();
        wall->AddComponent<Engine::TransformComponent>(0.f, 0.f, 100.f, 200.f);
        wall->AddComponent<Engine::CollisionComponent>(100.f, 200.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));
        // vertical
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<BumperComponent>();
        wall->AddComponent<Engine::TransformComponent>(0.f, 0.f, 200.f, 100.f);
        wall->AddComponent<Engine::CollisionComponent>(200.f, 100.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));

        // Second plus
        // horizontal
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<BumperComponent>();
        wall->AddComponent<Engine::TransformComponent>(300.f, 0.f, 100.f, 200.f);
        wall->AddComponent<Engine::CollisionComponent>(100.f, 200.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));
        // vertical
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<BumperComponent>();
        wall->AddComponent<Engine::TransformComponent>(300.f, 0.f, 200.f, 100.f);
        wall->AddComponent<Engine::CollisionComponent>(200.f, 100.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));

        return true;
    }

    bool Stadium::InitLvl1(Engine::EntityManager* entityManager_)
    {        
        // Central cross
        // horizontal        
        auto wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<BumperComponent>();
        wall->AddComponent<Engine::TransformComponent>(0.f, 0.f, 160.f, 240.f);
        wall->AddComponent<Engine::CollisionComponent>(160.f, 240.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));
        // vertical
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<BumperComponent>();
        wall->AddComponent<Engine::TransformComponent>(0.f, 0.f, 400.f, 160.f);
        wall->AddComponent<Engine::CollisionComponent>(400.f, 160.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));

        // LeftUp bumper
        // vertical
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<BumperComponent>();
        wall->AddComponent<Engine::TransformComponent>(-560.f, -240.f, 80.f, 160.f);
        wall->AddComponent<Engine::CollisionComponent>(80.f, 160.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));
        // horizontal
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<BumperComponent>();
        wall->AddComponent<Engine::TransformComponent>(-480.f, -280.f, 80.f, 80.f);
        wall->AddComponent<Engine::CollisionComponent>(80.f, 80.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));

        // RightDown bumper
        // vertical
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<BumperComponent>();
        wall->AddComponent<Engine::TransformComponent>(560.f, 240.f, 80.f, 160.f);
        wall->AddComponent<Engine::CollisionComponent>(80.f, 160.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));
        // horizontal
        wall = std::make_unique<Engine::Entity>();
        wall->AddComponent<BumperComponent>();
        wall->AddComponent<Engine::TransformComponent>(480.f, 280.f, 80.f, 80.f);
        wall->AddComponent<Engine::CollisionComponent>(80.f, 80.f);
        wall->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(wall));
        return true;
    }

    bool Stadium::InitLvl2(Engine::EntityManager* entityManager_)
    {
        // Bumper Down
        auto bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<Engine::TransformComponent>(0.f, 240.f, 240.f, 80.f);
        bumper->AddComponent<Engine::CollisionComponent>(240.f, 80.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(bumper));

        // Bumper Up
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<Engine::TransformComponent>(0.f, -240.f, 240.f, 80.f);
        bumper->AddComponent<Engine::CollisionComponent>(240.f, 80.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(bumper));

        // Bumper Left
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<Engine::TransformComponent>(-240.f, 0.f, 80.f, 240.f);
        bumper->AddComponent<Engine::CollisionComponent>(80.f, 240.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(bumper));

        // Bumper right
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<Engine::TransformComponent>(240.f, 0.f, 80.f, 240.f);
        bumper->AddComponent<Engine::CollisionComponent>(80.f, 240.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_textureWall;
        entityManager_->AddEntity(std::move(bumper));

        return true;
    }
}