#include "precomp.h"
#include "StadiumController.h"

#include "Entities/GameComponents.h"

namespace Game
{
    bool Stadium::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_, Engine::TextureManager* textureManager_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to StadiumController::Init()");

        m_TextureManager = textureManager_;

        auto grid = std::make_unique<Engine::Entity>(); 
        grid->AddComponent<Engine::TransformComponent>(0.f, 0.f, 1280.f, 720.f);
        grid->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

        entityManager_->AddEntity(std::move(grid));        

        return true;
    }

    // ***************
    // *  LEVEL C++  *
    // ***************
    bool Stadium::InitLvlCpp(Engine::EntityManager* entityManager_)
    {
        // C
        // Vertical
        auto bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(-440.f, 0.f, 80.f, 400.f);
        bumper->AddComponent<Engine::CollisionComponent>(80.f, 400.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_80x400");
        entityManager_->AddEntity(std::move(bumper));
        // C Up horizontal
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(-300.f, -150.f, 200.f, 100.f);
        bumper->AddComponent<Engine::CollisionComponent>(200.f, 100.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_200x100");
        entityManager_->AddEntity(std::move(bumper));
        // C Down horizontal
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(-300.f, 150.f, 200.f, 100.f);
        bumper->AddComponent<Engine::CollisionComponent>(200.f, 100.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_200x100");
        entityManager_->AddEntity(std::move(bumper));

        // First plus
        // horizontal
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(0.f, 0.f, 80.f, 200.f);
        bumper->AddComponent<Engine::CollisionComponent>(80.f, 200.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_80x200");
        entityManager_->AddEntity(std::move(bumper));
        // vertical
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(0.f, 0.f, 200.f, 80.f);
        bumper->AddComponent<Engine::CollisionComponent>(200.f, 80.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_200x80");
        entityManager_->AddEntity(std::move(bumper));

        // Second plus
        // horizontal
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(300.f, 0.f, 80.f, 200.f);
        bumper->AddComponent<Engine::CollisionComponent>(80.f, 200.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_80x200");
        entityManager_->AddEntity(std::move(bumper));
        // vertical
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(300.f, 0.f, 200.f, 80.f);
        bumper->AddComponent<Engine::CollisionComponent>(200.f, 80.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_200x80");
        entityManager_->AddEntity(std::move(bumper));

        return true;
    }

    // ************
    // *  LEVEL1  *
    // ************
    bool Stadium::InitLvl1(Engine::EntityManager* entityManager_)
    {
        // Bumper Down
        auto bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(0.f, 240.f, 240.f, 80.f);
        bumper->AddComponent<Engine::CollisionComponent>(240.f, 80.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_240x80");
        entityManager_->AddEntity(std::move(bumper));

        // Bumper Up
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(0.f, -240.f, 240.f, 80.f);
        bumper->AddComponent<Engine::CollisionComponent>(240.f, 80.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_240x80");
        entityManager_->AddEntity(std::move(bumper));

        // Bumper Left
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(-240.f, 0.f, 80.f, 240.f);
        bumper->AddComponent<Engine::CollisionComponent>(80.f, 240.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_80x240");
        entityManager_->AddEntity(std::move(bumper));

        // Bumper right
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(240.f, 0.f, 80.f, 240.f);
        bumper->AddComponent<Engine::CollisionComponent>(80.f, 240.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_80x240");
        entityManager_->AddEntity(std::move(bumper));

        return true;
    }


    // ***********
    // * LEVEL 2 *
    // ***********
    bool Stadium::InitLvl2(Engine::EntityManager* entityManager_)
    {        
        // Central cross
        // horizontal        
        auto bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(0.f, 0.f, 160.f, 240.f);
        bumper->AddComponent<Engine::CollisionComponent>(160.f, 240.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_160x240");
        entityManager_->AddEntity(std::move(bumper));
        // vertical
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(0.f, 0.f, 400.f, 160.f);
        bumper->AddComponent<Engine::CollisionComponent>(400.f, 160.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_400x160");
        entityManager_->AddEntity(std::move(bumper));

        // LeftUp bumper
        // vertical
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(-560.f, -240.f, 80.f, 160.f);
        bumper->AddComponent<Engine::CollisionComponent>(80.f, 160.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_80x160");
        entityManager_->AddEntity(std::move(bumper));
        // horizontal
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(-480.f, -280.f, 80.f, 80.f);
        bumper->AddComponent<Engine::CollisionComponent>(80.f, 80.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_80x80");
        entityManager_->AddEntity(std::move(bumper));

        // RightDown bumper
        // vertical
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(560.f, 240.f, 80.f, 160.f);
        bumper->AddComponent<Engine::CollisionComponent>(80.f, 160.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_80x160");
        entityManager_->AddEntity(std::move(bumper));
        // horizontal
        bumper = std::make_unique<Engine::Entity>();
        bumper->AddComponent<BumperComponent>();
        bumper->AddComponent<Engine::TransformComponent>(480.f, 280.f, 80.f, 80.f);
        bumper->AddComponent<Engine::CollisionComponent>(80.f, 80.f);
        bumper->AddComponent<Engine::SpriteComponent>().m_Image = m_TextureManager->GetTexture("wall_80x80");
        entityManager_->AddEntity(std::move(bumper));
        return true;
    }

    void Stadium::Destroy(Engine::EntityManager* entityManager_) {
        auto bumerEntities = entityManager_->GetAllEntitiesWithComponent<BumperComponent>();
        for (auto entity : bumerEntities) {
            entity->RemoveAllComponents();
        }
    }

} // Game